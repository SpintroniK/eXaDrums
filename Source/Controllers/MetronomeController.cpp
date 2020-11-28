/*
 * MetronomeController.cpp
 *
 *  Created on: 2 Oct 2016
 *      Author: jeremy
 */

#include "MetronomeController.h"

#include <algorithm>
#include <iterator>

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
			this->builder->get_widget("ClickVolumeScale", clickVolumeScale);
			this->builder->get_widget("EnableClickButton", enableClickButton);
			this->builder->get_widget("RhythmList", rhythmList);
			this->builder->get_widget("BpmeasList", bpmeasList);
		}

		// Connect all signals
		{
			metronomeConfigSave->signal_clicked().connect([&] { SaveMetronomeConfig(); });
			clickTempoScale->signal_value_changed().connect([&] { ChangeTempo(); });
			clickVolumeScale->signal_value_changed().connect([&] { ChangeClickVolume(); });
			enableClickButton->signal_clicked().connect([&] { EnableClick(); });
		}

		// Set tempo value
		clickTempoScale->set_value(drumKit->GetTempo());
		// Metronome not running by defautl
		clickVolumeScale->property_sensitive() = false;

		// Configure Metronome Window
		{
			// Append clicks to list
			std::vector<std::string> clicks = drumKit->GetClicksTypes();
			std::for_each(clicks.cbegin(), clicks.cend(), [this](const std::string& s){ clickTypes->append(s); });

			// Get current click type
			int clickTypeId = drumKit->GetClickTypeId();

			// Select current click type
			clickTypes->set_active(clickTypeId);
		}

		// Populate rhythm list
		this->rhythms = drumKit->GetRhythms();
		{
			// Append rhythms to list
			std::for_each(rhythms.cbegin(), rhythms.cend(), [this](int x) { rhythmList->append(std::to_string(x)); });

			// Get current rhythm index in vector
			auto it = std::find(rhythms.cbegin(), rhythms.cend(), this->drumKit->GetRhythm());
			int index = std::distance(rhythms.cbegin(), it);

			// Select current rhythm
			rhythmList->set_active(index);
		}

		// Populate beats per measure list
		this->bpmeasValues = drumKit->GetBpms();
		{
			// Append values to list
			std::for_each(bpmeasValues.cbegin(), bpmeasValues.cend(), [this](int x) { bpmeasList->append(std::to_string(x));});

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



	void MetronomeController::EnableClick() const
	{

		bool enable =  enableClickButton->get_active();

		drumKit->EnableMetronome(enable);

		clickVolumeScale->property_sensitive() = enable;
		clickVolumeScale->set_value(drumKit->GetClickVolume());

		return;
	}

	void MetronomeController::ChangeTempo() const
	{

		int tempo = (int) this->clickTempoScale->get_value();
		drumKit->ChangeTempo(tempo);

		return;
	}

	void MetronomeController::ChangeClickVolume() const
	{

		int volume = (int) this->clickVolumeScale->get_value();
		drumKit->ChangeClickVolume(volume);
		clickVolumeScale->property_sensitive() = true;

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
