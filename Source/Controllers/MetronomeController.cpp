/*
 * MetronomeController.cpp
 *
 *  Created on: 2 Oct 2016
 *      Author: jeremy
 */

#include "MetronomeController.h"

using namespace eXaDrumsApi;

namespace Controllers
{

	MetronomeController::MetronomeController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrums> drumKit)
	: builder(builder), drumKit(drumKit)
	{

		// Get all widgets
		{
			this->builder->get_widget("MetronomeConfig", metronomeWindow);
			this->builder->get_widget("MetronomeConfigSave", metronomeConfigSave);
			this->builder->get_widget("MetronomeSoundType", clickTypes);
			this->builder->get_widget("ClickTempoScale", clickTempoScale);
			this->builder->get_widget("EnableClickButton", enableClickButton);
			this->builder->get_widget("RhythmList", rhythmList);
			this->builder->get_widget("BpmeasList", bpmeasList);
		}

		// Connect all signals
		{
			metronomeConfigSave->signal_clicked().connect(sigc::mem_fun(this, &MetronomeController::SaveMetronomeConfig));
			clickTempoScale->signal_value_changed().connect(sigc::mem_fun(this, &MetronomeController::ChangeTempo));
			enableClickButton->signal_clicked().connect(sigc::mem_fun(this, &MetronomeController::EnableClick));
		}

		// Set tempo value
		clickTempoScale->set_value(drumKit->GetTempo());

		// Configure Metronome Window
		{
			// Append clicks to list
			std::vector<std::string> clicks = RetrieveClickTypes();
			std::for_each(clicks.cbegin(), clicks.cend(), [this](const std::string& s){ clickTypes->append(s); });

			// Get current click type
			int clickTypeId = drumKit->GetClickTypeId();

			// Select current click type
			clickTypes->set_active(clickTypeId);
		}

		// Populate rhythm list
		this->rhythms = RetrieveRhythmList();
		{
			// Append rhythms to list
			std::for_each(rhythms.cbegin(), rhythms.cend(), [this](const int& x) { rhythmList->append(std::to_string(x)); });

			// Get current rhythm index in vector
			auto it = std::find(rhythms.cbegin(), rhythms.cend(), this->drumKit->GetRhythm());
			int index = std::distance(rhythms.cbegin(), it);

			// Select current rhythm
			rhythmList->set_active(index);
		}

		// Populate beats per measure list
		this->bpmeasValues = RetrieveBpmeasList();
		{
			// Append values to list
			std::for_each(bpmeasValues.cbegin(), bpmeasValues.cend(), [this](const int& x) { bpmeasList->append(std::to_string(x));});

			// Get current nb of beats per measure's index in vector
			auto it = std::find(bpmeasValues.cbegin(), bpmeasValues.cend(), this->drumKit->GetBpmeas());
			int index = std::distance(bpmeasValues.cbegin(), it);

			// Select current number of beats per measure
			bpmeasList->set_active(index);
		}

		return;
	}

	MetronomeController::~MetronomeController()
	{

		// Delete all windows and dialogs
		delete metronomeWindow;

		return;
	}


	// Private methods


	std::vector<std::string> MetronomeController::RetrieveClickTypes() const
	{

		int numClickTypes = drumKit->GetNumClickTypes();

		std::vector<std::string> clickTypes(numClickTypes);
		{

			for(int i = 0; i < numClickTypes; i++)
			{

				// Create local array to store string given by libeXaDrums
				char clickName[128];
				int nameLength;

				// Get characters and string's length
				drumKit->GetClickTypeById(i, clickName, nameLength);

				// Convert to string
				std::string name(clickName, nameLength);

				clickTypes[i] = name;
			}

		}

		return clickTypes;
	}

	std::vector<int> MetronomeController::RetrieveRhythmList() const
	{

		const int size = drumKit->GetNumRhythms();

		int data[size];

		drumKit->GetRhythmList(data);

		std::vector<int> list;
		std::copy_n(data, size, std::back_inserter(list));

		return list;
	}

	std::vector<int> MetronomeController::RetrieveBpmeasList() const
	{

		const int size = drumKit->GetNumBpmeas();

		int data[size];

		drumKit->GetBpmeasList(data);

		std::vector<int> list;
		std::copy_n(data, size, std::back_inserter(list));

		return list;
	}



	void MetronomeController::EnableClick() const
	{

		bool enable =  enableClickButton->get_active();

		drumKit->EnableMetronome(enable);

		return;
	}

	void MetronomeController::ChangeTempo() const
	{

		int tempo = (int) this->clickTempoScale->get_value();
		drumKit->ChangeTempo(tempo);

		return;
	}

	void MetronomeController::ShowMetronomePrefs()
	{

		metronomeWindow->show();

		return;
	}

	void MetronomeController::SaveMetronomeConfig()
	{

		// Set new parameters values
		drumKit->SetClickType(clickTypes->get_active_row_number());
		drumKit->SetRhythm(rhythms[rhythmList->get_active_row_number()]);
		drumKit->SetBpmeas(bpmeasValues[bpmeasList->get_active_row_number()]);

		drumKit->RestartMetronome();

		drumKit->SaveMetronomeConfig();

		metronomeWindow->hide();

		return;
	}


} /* namespace Gui */
