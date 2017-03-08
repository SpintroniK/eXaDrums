/*
 * ConfigController.cpp
 *
 *  Created on: 9 Feb 2017
 *      Author: jeremy
 */

#include "ConfigController.h"

#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>


using namespace eXaDrumsApi;

namespace Controllers
{

	ConfigController::ConfigController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrums> drumKit)
	: builder(builder), drumKit(drumKit), config(*drumKit.get())
	{

		Gtk::Button* mixerConfigButton = nullptr;
		Gtk::Button* soundLibraryButton = nullptr;
		Gtk::Button* triggersConfigButton = nullptr;
		Gtk::Button* soundEffectsButton = nullptr;
		Gtk::Button* sensorsConfigButton = nullptr;
		Gtk::Button* sensorsConfigOkayButton = nullptr;
		Gtk::Button* sensorsConfigCancelButton = nullptr;

		// Get all widgets
		{

			// Buttons
			builder->get_widget("MixerConfigButton", mixerConfigButton);
			builder->get_widget("SoundLibraryButton", soundLibraryButton);
			builder->get_widget("TriggersConfigButton", triggersConfigButton);
			builder->get_widget("SoundEffectsButton", soundEffectsButton);
			builder->get_widget("SensorsConfigButton", sensorsConfigButton);
			builder->get_widget("SensorsConfigCancelButton", sensorsConfigCancelButton);

			// Sensors config
			builder->get_widget("SensorsConfigOkayButton", sensorsConfigOkayButton);

			// Windows
			builder->get_widget("SensorsConfigWindow", sensorsConfigWindow);

		}

		// Connect signals
		{

			mixerConfigButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowMixerConfigWindow));
			soundLibraryButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowSoundLibConfigWindow));
			triggersConfigButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowTriggersConfigWindow));
			soundEffectsButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowSoundEffectsWindow));
			sensorsConfigButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowSensorsConfigWindow));
			sensorsConfigCancelButton->signal_clicked().connect(sigc::mem_fun(sensorsConfigWindow, &Gtk::Window::hide));

			// Sensors config
			sensorsConfigOkayButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::SaveSensorsConfig));

		}

		// Configure sensors window
		{

			// Sampling rate
			Gtk::Entry* samplingRate = nullptr;
			builder->get_widget("SensorsSamplingRate", samplingRate);

			int sRate = config.GetSensorsSamplingRate();
			samplingRate->set_text(std::to_string(sRate));

			// Resolution
			Gtk::Entry* resolution = nullptr;
			builder->get_widget("SensorsResolution", resolution);

			int res = config.GetSensorsResolution();
			resolution->set_text(std::to_string(res));

			// Sensor type
			Gtk::ComboBoxText* sensorsTypesList = nullptr;
			builder->get_widget("SensorsTypes", sensorsTypesList);

			std::vector<std::string> sensorsTypes = config.GetSensorsTypes();

			// Append values to combobox
			std::for_each(sensorsTypes.cbegin(), sensorsTypes.cend(), [&](const std::string& s) { sensorsTypesList->append(s); });

			const std::string selectedType = config.GetSensorsType();
			sensorsTypesList->set_active_text(selectedType);

			Gtk::Entry* hddDataFolder = nullptr;
			builder->get_widget("SensorsDataFolder", hddDataFolder);
			std::string dataFolder = config.GetSensorsDataFolder();
			hddDataFolder->set_text(dataFolder);

		}

		return;
	}


	ConfigController::~ConfigController()
	{

		delete sensorsConfigWindow;

		return;
	}

	// Private Methods

	void ConfigController::ShowMixerConfigWindow()
	{


		return;
	}

	void ConfigController::ShowSoundLibConfigWindow()
	{

		return;
	}

	void ConfigController::ShowTriggersConfigWindow()
	{

		return;
	}

	void ConfigController::ShowSoundEffectsWindow()
	{

		return;
	}

	void ConfigController::ShowSensorsConfigWindow()
	{

		sensorsConfigWindow->show();

		return;
	}

	void ConfigController::SaveSensorsConfig()
	{


		Gtk::Entry* samplingRate = nullptr;
		Gtk::Entry* resolution = nullptr;
		Gtk::ComboBoxText* sensorsTypesList = nullptr;
		Gtk::Entry* hddDataFolder = nullptr;

		builder->get_widget("SensorsSamplingRate", samplingRate);
		builder->get_widget("SensorsResolution", resolution);
		builder->get_widget("SensorsTypes", sensorsTypesList);
		builder->get_widget("SensorsDataFolder", hddDataFolder);

		int sRate = std::stoi(samplingRate->get_text());
		int res = std::stoi(resolution->get_text());
		std::string type = sensorsTypesList->get_active_text();
		std::string dataFolder = hddDataFolder->get_text();


		config.SetSensorsSamplingRate(sRate);
		config.SetSensorsResolution(res);
		config.SetSensorsType(type);
		config.SetSensorsDataFolder(dataFolder);

		config.SaveSensorsConfig();

		sensorsConfigWindow->hide();

		return;
	}

} /* namespace Controllers */
