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

#include <cstring>

using namespace eXaDrumsApi;
using namespace Widgets;

namespace Controllers
{

	ConfigController::ConfigController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrums> drumKit)
	: builder(builder), drumKit(drumKit), config(*drumKit.get())
	{

		Gtk::Button* mixerConfigButton = nullptr;
		Gtk::Button* soundLibraryButton = nullptr;

		// Triggers
		Gtk::Button* triggersConfigButton = nullptr;
		Gtk::Button* triggersSelectCloseButton = nullptr;
		Gtk::Button* triggerConfigCancelButton = nullptr;
		Gtk::Button* triggerConfigApplyButton = nullptr;
		Gtk::Button* triggerConfigSaveButton = nullptr;

		Gtk::Button* soundEffectsButton = nullptr;

		// Sensors
		Gtk::Button* sensorsConfigButton = nullptr;
		Gtk::Button* sensorsConfigOkayButton = nullptr;
		Gtk::Button* sensorsConfigCancelButton = nullptr;

		// Get all widgets
		{

			// Buttons
			builder->get_widget("MixerConfigButton", mixerConfigButton);
			builder->get_widget("SoundLibraryButton", soundLibraryButton);

			// Triggers
			builder->get_widget("TriggersConfigButton", triggersConfigButton);
			builder->get_widget("TriggerSelectCloseButton", triggersSelectCloseButton);
			builder->get_widget("TriggerConfigCancel", triggerConfigCancelButton);
			builder->get_widget("TriggerConfigApply", triggerConfigApplyButton);
			builder->get_widget("TriggerConfigSave", triggerConfigSaveButton);


			builder->get_widget("SoundEffectsButton", soundEffectsButton);

			// Sensors
			builder->get_widget("SensorsConfigButton", sensorsConfigButton);
			builder->get_widget("SensorsConfigCancelButton", sensorsConfigCancelButton);
			builder->get_widget("SensorsConfigOkayButton", sensorsConfigOkayButton);

			// Windows
			builder->get_widget("SensorsConfigWindow", sensorsConfigWindow);
			builder->get_widget("TriggerSeclectWindow", triggerSelectWindow);
			builder->get_widget("TriggerConfigurationWindow", triggerConfigWindow);

		}

		// Connect signals
		{

			mixerConfigButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowMixerConfigWindow));
			soundLibraryButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowSoundLibConfigWindow));
			soundEffectsButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowSoundEffectsWindow));
			sensorsConfigCancelButton->signal_clicked().connect(sigc::mem_fun(sensorsConfigWindow, &Gtk::Window::hide));

			// Triggers config
			triggersConfigButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowTriggersConfigWindow));
			triggersSelectCloseButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::CloseTriggerSelectWindow));
			triggerConfigCancelButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::CloseTriggerConfigWindow));
			triggerConfigApplyButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ApplyTriggerConfig));
			triggerConfigSaveButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::SaveTriggerConfig));

			// Sensors config
			sensorsConfigButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowSensorsConfigWindow));
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
		delete triggerSelectWindow;
		delete triggerConfigWindow;

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

		//std::for_each(triggersSelectors.begin(), triggersSelectors.end(), [](TriggerSelectorPtr& t) { t.reset(); });
		triggersSelectors.clear();

		for(const auto& t : triggersParameters)
		{
			triggersSelectors.push_back(std::make_shared<TriggerSelector>(t.sensorId));
		}

		std::for_each(triggersSelectors.cbegin(), triggersSelectors.cend(), [&](const TriggerSelectorPtr& t){ triggersBox->add(*t); });

		// Connect signals
		for(const auto& ts : triggersSelectors)
		{
			ts->GetPreferencesButton().signal_clicked().connect(std::bind(sigc::mem_fun(this, &ConfigController::TriggerConfiguration), ts->GetSensorId()));
		}


		triggerSelectWindow->show();

		return;
	}

	void ConfigController::ApplyTriggerConfig()
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

		int sensorIdValue = std::stoi(sensorNb->get_text());
		int thresholdValue = std::stoi(threshold->get_text());

		return;
	}

	void ConfigController::CloseTriggerSelectWindow()
	{

		triggerSelectWindow->hide();

		return;
	}

	void ConfigController::CloseTriggerConfigWindow()
	{

		config.LoadTriggersConfig();
		config.SaveTriggersConfig();

		triggerConfigWindow->hide();

		return;
	}

	void ConfigController::SaveTriggerConfig()
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

		TriggerParameters tp;
		tp.sensorId = std::stoi(sensorNb->get_text());
		tp.threshold = std::stoi(threshold->get_text());
		tp.scanTime = std::stoi(scanTime->get_text());
		tp.maskTime = std::stoi(maskTime->get_text());

		std::strcpy(tp.type, types->get_active_text().c_str());
		std::strcpy(tp.response, responses->get_active_text().c_str());

		// Get triggers parameters
		config.LoadTriggersConfig();
		std::vector<TriggerParameters> triggersParameters = config.GetTriggersParameters();

		// Find the trigger we want to modify
		auto triggerIt = std::find_if(triggersParameters.begin(), triggersParameters.end(), [&](TriggerParameters& t) { return t.sensorId == tp.sensorId; });

		if(triggerIt == triggersParameters.end())
		{
			// Error: trigger doesn't exist.
			throw -1;
		}

		// Update parameters
		*triggerIt = tp;

		config.SetTriggersParameters(triggersParameters);

		// Save
		config.SaveTriggersConfig();

		triggerConfigWindow->hide();

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


	void ConfigController::TriggerConfiguration(int sensorId)
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
