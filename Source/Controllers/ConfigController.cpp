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
#include <gtkmm/box.h>


using namespace eXaDrumsApi;
using namespace Widgets;

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
			builder->get_widget("TriggerSeclectWindow", triggersConfigWindow);
			builder->get_widget("TriggerConfigurationWindow", triggerConfigWindow);

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

		// Configure triggers window
		{
			// Triggers types
			Gtk::ComboBoxText* types = nullptr;
			builder->get_widget("TCTypes", types);

			std::vector<std::string> typesVec = config.GetTriggersTypes();
			std::for_each(typesVec.cbegin(), typesVec.cend(), [&](const std::string& s) { types->append(s); });

			// Triggers responses
			Gtk::ComboBoxText* responses = nullptr;
			builder->get_widget("TCResponses", responses);

			std::vector<std::string> responsesVec = config.GetTriggersResponses();
			std::for_each(responsesVec.cbegin(), responsesVec.cend(), [&](const std::string& s) { responses->append(s); });


		}

		return;
	}


	ConfigController::~ConfigController()
	{

		delete sensorsConfigWindow;
		delete triggersConfigWindow;

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

		Gtk::Box* triggersBox = nullptr;
		builder->get_widget("TSListBox", triggersBox);

		const std::vector<TriggerParameters>& triggersParameters = config.GetTriggersParameters();

		std::for_each(triggersSelectors.begin(), triggersSelectors.end(), [](TriggerSelectorPtr& t) { t.reset(); });
		triggersSelectors.clear();

		for(const auto& t : triggersParameters)
		{
			triggersSelectors.push_back(std::make_shared<TriggerSelector>(t.sensorId));
		}

		std::for_each(triggersSelectors.cbegin(), triggersSelectors.cend(), [&](const TriggerSelectorPtr& t){ triggersBox->add(*t); });

		// Connect signals
		for(const auto& ts : triggersSelectors)
		{
			ts->GetPreferencesButton().signal_clicked().connect(std::bind(sigc::mem_fun(this, &ConfigController::ModifyTrigger), ts->GetSensorId()));
		}

		triggersConfigWindow->show();

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


	void ConfigController::ModifyTrigger(int sensorId)
	{

		// Create pointers
		Gtk::Entry* sensorNb = nullptr;
		Gtk::Entry* threshold = nullptr;
		Gtk::Entry* scanTime = nullptr;
		Gtk::Entry* maskTime = nullptr;
		Gtk::ComboBoxText* types = nullptr;
		Gtk::ComboBoxText* responses = nullptr;

		// Get widgets
		{
			builder->get_widget("TCSensorNb", sensorNb);
			builder->get_widget("TCThreshold", threshold);
			builder->get_widget("TCScanTime", scanTime);
			builder->get_widget("TCMaskTime", maskTime);
			builder->get_widget("TCTypes", types);
			builder->get_widget("TCResponses", responses);
		}

		const std::vector<TriggerParameters>& triggers = config.GetTriggersParameters();
		const TriggerParameters& trigger = triggers[sensorId];

		const std::string type(trigger.type);
		const std::string response(trigger.response);

		// Set fields values
		{
			sensorNb->set_text(std::to_string(trigger.sensorId));
			threshold->set_text(std::to_string(trigger.threshold));
			scanTime->set_text(std::to_string(trigger.scanTime));
			maskTime->set_text(std::to_string(trigger.maskTime));
			types->set_active_text(type);
			responses->set_active_text(response);
		}


		triggerConfigWindow->show();

		return;
	}



} /* namespace Controllers */
