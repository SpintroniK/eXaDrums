/*
 * MetronomeController.cpp
 *
 *  Created on: 2 Oct 2016
 *      Author: jeremy
 */

#include "MetronomeController.h"

namespace Gui
{

	MetronomeController::MetronomeController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrums> drumKit)
	: builder(builder), drumKit(drumKit)
	{

		// Get all widgets
		{
			this->builder->get_widget("MetronomeConfig", metronomeWindow);
			this->builder->get_widget("MetronomeConfigSave", metronomeConfigSave);
			this->builder->get_widget("MetronomeSoundType", clickTypes);
			this->builder->get_widget("ClickVolumeScale", clickVolumeScale);
			this->builder->get_widget("EnableClickButton", enableClickButton);
		}

		// Connect all signals
		{
			metronomeConfigSave->signal_clicked().connect(sigc::mem_fun(this, &MetronomeController::SaveMetronomeConfig));
			clickVolumeScale->signal_value_changed().connect(sigc::mem_fun(this, &MetronomeController::ChangeTempo));
			enableClickButton->signal_clicked().connect(sigc::mem_fun(this, &MetronomeController::EnableClick));
		}

		// Configure Metronome Window
		{
			std::vector<std::string> clicks = RetrieveClickTypes();

			for(const std::string& clickType : clicks)
			{
				clickTypes->append(clickType);
			}
			clickTypes->set_active(0);
		}

		return;
	}

	MetronomeController::~MetronomeController()
	{

		// Delete all windows and dialogs
		delete metronomeWindow;

		return;
	}

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


	void MetronomeController::EnableClick() const
	{

		bool enable =  enableClickButton->get_active();

		drumKit->EnableMetronome(enable);

		return;
	}

	void MetronomeController::ChangeTempo() const
	{

		int tempo = (int) this->clickVolumeScale->get_value();
		drumKit->ChangeTempo(tempo);

		return;
	}


	// Private methods

	void MetronomeController::ShowMetronomePrefs()
	{

		metronomeWindow->show();

		return;
	}

	void MetronomeController::SaveMetronomeConfig()
	{

		metronomeWindow->hide();

		return;
	}


} /* namespace Gui */
