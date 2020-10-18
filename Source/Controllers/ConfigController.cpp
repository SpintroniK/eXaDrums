/*
 * ConfigController.cpp
 *
 *  Created on: 9 Feb 2017
 *      Author: jeremy
 */

#include "../Util/Util.h"
#include "../Util/ErrorHandler.h"
#include "ConfigController.h"

#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/entry.h>
#include <gtkmm/box.h>

#include <iostream>

#include <unistd.h>

using namespace eXaDrumsApi;
using namespace Widgets;
using namespace Errors;
using namespace Util;

namespace Controllers
{

	ConfigController::ConfigController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrums> drumKit, const std::function<void()>& quit)
	: builder(builder), drumKit(drumKit), config(*drumKit.get())
	{

		this->quitCallback = quit;

		Gtk::Button* mixerConfigButton = nullptr;
		Gtk::Button* soundLibraryButton = nullptr;
		Gtk::Button* importExportConfigButton = nullptr;

		// Config management
		Gtk::Button* exportConfigButton = nullptr;
		Gtk::Button* exportConfigSaveButton = nullptr;


		// Triggers
		Gtk::Button* triggersConfigButton = nullptr;
		Gtk::Button* triggersSelectCloseButton = nullptr;
		Gtk::Button* triggerConfigCancelButton = nullptr;
		Gtk::Button* triggerConfigApplyButton = nullptr;
		Gtk::Button* triggerConfigSaveButton = nullptr;
		Gtk::Button* addtriggerButton = nullptr;
		Gtk::Button* triggerAddCancel = nullptr;
		Gtk::Button* triggerAddAdd = nullptr;

		Gtk::Button* soundEffectsButton = nullptr;

		// Sensors
		Gtk::Button* sensorsConfigButton = nullptr;
		Gtk::Button* sensorsConfigOkayButton = nullptr;
		Gtk::Button* sensorsConfigCancelButton = nullptr;

		// Mixer
		Gtk::Button* mixerConfigCancelButton = nullptr;
		Gtk::Button* mixerConfigSaveButton = nullptr;

		// Get all widgets
		{

			// Buttons
			builder->get_widget("MixerConfigButton", mixerConfigButton);
			builder->get_widget("SoundLibraryButton", soundLibraryButton);
			builder->get_widget("ImportExportConfigButton", importExportConfigButton);

			// Config
			builder->get_widget("ExportConfigButton", exportConfigButton);
			builder->get_widget("ExportConfigSaveButton", exportConfigSaveButton);

			// Triggers
			builder->get_widget("TriggersConfigButton", triggersConfigButton);
			builder->get_widget("TriggerSelectCloseButton", triggersSelectCloseButton);
			builder->get_widget("TriggerConfigCancel", triggerConfigCancelButton);
			builder->get_widget("TriggerConfigApply", triggerConfigApplyButton);
			builder->get_widget("TriggerConfigSave", triggerConfigSaveButton);
			builder->get_widget("AddTriggerButton", addtriggerButton);
			builder->get_widget("TriggerAddCancel", triggerAddCancel);
			builder->get_widget("TriggerAddAdd", triggerAddAdd);


			builder->get_widget("SoundEffectsButton", soundEffectsButton);

			// Sensors
			builder->get_widget("SensorsConfigButton", sensorsConfigButton);
			builder->get_widget("SensorsConfigCancelButton", sensorsConfigCancelButton);
			builder->get_widget("SensorsConfigOkayButton", sensorsConfigOkayButton);

			// Mixer
			builder->get_widget("MixerConfigCancel", mixerConfigCancelButton);
			builder->get_widget("MixerConfigSave", mixerConfigSaveButton);

			// Comboboxes
			builder->get_widget("MixerDevices", mixerDevices);

			// Windows
			builder->get_widget("SensorsConfigWindow", sensorsConfigWindow);
			builder->get_widget("TriggerSeclectWindow", triggerSelectWindow);
			builder->get_widget("TriggerConfigurationWindow", triggerConfigWindow);
			builder->get_widget("TriggerAddWindow", triggerAddWindow);
			builder->get_widget("MixerConfigWindow", mixerConfigWindow);
			builder->get_widget("ImportExportConfigWindow", importExportConfigWindow);
			builder->get_widget("ExportConfigWindow", exportConfigWindow);

		}

		// Connect signals
		{

			mixerConfigButton->signal_clicked().connect([&] { ShowMixerConfigWindow(); });
			soundLibraryButton->signal_clicked().connect([&] { ShowSoundLibConfigWindow(); });
			soundEffectsButton->signal_clicked().connect([&] { ShowSoundEffectsWindow(); });
			sensorsConfigCancelButton->signal_clicked().connect([&] { sensorsConfigWindow->hide(); });
			importExportConfigButton->signal_clicked().connect([&] { importExportConfigWindow->show(); });

			// Config
			exportConfigButton->signal_clicked().connect([&] { exportConfigWindow->show(); });
			exportConfigSaveButton->signal_clicked().connect([&] { ExportConfiguration(); });

			// Triggers config
			triggersConfigButton->signal_clicked().connect([&] { ShowTriggersConfigWindow(); });
			triggersSelectCloseButton->signal_clicked().connect([&] { CloseTriggerSelectWindow(); });
			triggerConfigCancelButton->signal_clicked().connect([&] { CloseTriggerConfigWindow(); });
			triggerConfigApplyButton->signal_clicked().connect([&] { ApplyTriggerConfig(); });
			triggerConfigSaveButton->signal_clicked().connect([&] { SaveTriggerConfig(); });
			addtriggerButton->signal_clicked().connect([&] { triggerSelectWindow->hide(); triggerAddWindow->show(); });
			triggerAddCancel->signal_clicked().connect([&] { triggerAddWindow->hide(); triggerSelectWindow->show(); });
			triggerAddAdd->signal_clicked().connect([&] { AddTrigger(); });

			// Sensors config
			sensorsConfigButton->signal_clicked().connect([&] { ShowSensorsConfigWindow(); });
			sensorsConfigOkayButton->signal_clicked().connect([&] { SaveSensorsConfig(); });

			// Mixer config
			mixerConfigCancelButton->signal_clicked().connect([&] { mixerConfigWindow->hide(); });
			mixerConfigSaveButton->signal_clicked().connect([&] { SaveMixerConfig(); });

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

		// Add trigger window
		{
			// Triggers types
			Gtk::ComboBoxText* types = nullptr;
			builder->get_widget("TATypes", types);

			std::vector<std::string> typesVec = config.GetTriggersTypes();
			std::for_each(typesVec.cbegin(), typesVec.cend(), [&](const std::string& s) { types->append(s); });
			types->set_active(0);

			// Triggers responses
			Gtk::ComboBoxText* responses = nullptr;
			builder->get_widget("TAResponses", responses);

			std::vector<std::string> responsesVec = config.GetTriggersResponses();
			std::for_each(responsesVec.cbegin(), responsesVec.cend(), [&](const std::string& s) { responses->append(s); });
			responses->set_active(0);
		}


		return;
	}


	ConfigController::~ConfigController()
	{

		return;
	}

	// Private Methods

	void ConfigController::ShowMixerConfigWindow()
	{

		Gtk::Button* playButton = nullptr;
		Gtk::Entry* sampleRate = nullptr;
		Gtk::Entry* bufferLength = nullptr;
		Gtk::Entry* periodLength = nullptr;
		Gtk::Entry* nbChannels = nullptr;

		builder->get_widget("PlayButton", playButton);
		builder->get_widget("MixerSamplingRate", sampleRate);
		builder->get_widget("MixerBufferLength", bufferLength);
		builder->get_widget("MixerPeriodLength", periodLength);
		builder->get_widget("MixerNbChannels", nbChannels);

		if(drumKit->IsStarted())
		{
			playButton->set_property("label", Gtk::StockID("gtk-media-play"));
			try
			{
				drumKit->Stop();
			}
			catch(const Exception& e)
			{
				errorDialog(e);
			}
		}

		// Configure mixer window
		{
			mixerDevices->unset_active();
			mixerDevices->remove_all();

			// Get sound devices
			std::vector<std::string> devices = config.GetAudioDevicesNames();

			for(const auto& device : devices)
			{
				mixerDevices->append(device);
			}

			// Get selected device
			std::string devName = config.GetAudioDeviceName();
			mixerDevices->set_active_text(devName);

			AlsaParamsApi alsaParameters = config.GetAudioDeviceParams();

			sampleRate->set_text(std::to_string(alsaParameters.sampleRate));
			bufferLength->set_text(std::to_string(alsaParameters.bufferTime));
			periodLength->set_text(std::to_string(alsaParameters.periodTime));
			nbChannels->set_text(std::to_string(alsaParameters.nChannels));

		}

		mixerConfigWindow->show();

		return;
	}

	void ConfigController::SaveMixerConfig()
	{

		Gtk::Entry* sampleRate = nullptr;
		Gtk::Entry* bufferLength = nullptr;
		Gtk::Entry* periodLength = nullptr;
		Gtk::Entry* nbChannels = nullptr;

		builder->get_widget("MixerSamplingRate", sampleRate);
		builder->get_widget("MixerBufferLength", bufferLength);
		builder->get_widget("MixerPeriodLength", periodLength);
		builder->get_widget("MixerNbChannels", nbChannels);

		AlsaParamsApi alsaParameters;
		alsaParameters.sampleRate = std::stoi(sampleRate->get_text());
		alsaParameters.bufferTime = std::stoi(bufferLength->get_text());
		alsaParameters.periodTime = std::stoi(periodLength->get_text());
		alsaParameters.nChannels = std::stoi(nbChannels->get_text());

		std::strcpy(alsaParameters.device, mixerDevices->get_active_text().data());

		try
		{
			config.SaveAudioDeviceConfig(alsaParameters);
			config.ResetAudioDevice();
		}
		catch(const Exception& e)
		{
			errorDialog(e);
			return;
		}

		mixerConfigWindow->hide();

		return;
	}

	void ConfigController::ExportConfiguration()
	{
		const std::string fileName = exportConfigWindow->get_filename();

		try
		{
			const auto path = fs::path{fileName};
			if(path.filename().string().length() <= 3)
			{
				throw Exception("File name is too short.", error_type_warning);
			}

			// Export configuration
			const std::string pathStr = std::getenv("HOME") + std::string{"/.eXaDrums"};
			Config::ExportConfig(pathStr, fileName);

		}
		catch(const Exception& e)
		{
			errorDialog(e);
			return;
		}

		exportConfigWindow->hide();
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
			ts->GetPreferencesButton().signal_clicked().connect([&] { TriggerConfiguration(ts->GetSensorId()); });
			ts->GetDeleteButton().signal_clicked().connect([&] { TriggerDelete(ts->GetSensorId()); });
		}

		triggerSelectWindow->show();

		return;
	}


	void ConfigController::CloseTriggerSelectWindow()
	{

		triggerSelectWindow->hide();

		return;
	}

	void ConfigController::CloseTriggerConfigWindow()
	{

		try
		{
			config.LoadTriggersConfig();
			config.SaveTriggersConfig();
		}
		catch(const Exception& e)
		{
			errorDialog(e);
			return;
		}

		triggerConfigWindow->hide();
		triggerSelectWindow->show();

		return;
	}

	TriggerParameters ConfigController::GetCurrentTriggerParams() const
	{

		// Get widgets
		auto sensorNb = GetWidget<Gtk::Entry>(builder, "TCSensorNb");
		auto threshold = GetWidget<Gtk::Entry>(builder, "TCThreshold");
		auto gain = GetWidget<Gtk::Entry>(builder, "TCGain");
		auto scanTime = GetWidget<Gtk::Entry>(builder, "TCScanTime");
		auto maskTime = GetWidget<Gtk::Entry>(builder, "TCMaskTime");;
		auto types = GetWidget<Gtk::ComboBoxText>(builder, "TCTypes");
		auto responses = GetWidget<Gtk::ComboBoxText>(builder, "TCResponses");

		// Convert to trigger parameters
		TriggerParameters tp;

		tp.sensorId = std::stoi(sensorNb->get_text());
		tp.threshold = std::stoi(threshold->get_text());
		tp.gain = std::stod(gain->get_text());
		tp.scanTime = std::stoi(scanTime->get_text());
		tp.maskTime = std::stoi(maskTime->get_text());

		const std::string types_str = types->get_active_text();
		const std::string responses_str = responses->get_active_text();

		tp.type[types_str.copy(tp.type, types_str.size())] = '\0';
		tp.response[responses_str.copy(tp.response, responses_str.size())] = '\0';

		return tp;
	}

	void ConfigController::ApplyTriggerConfig()
	{

		TriggerParameters params = GetCurrentTriggerParams();
		config.SetTriggerParameters(params.sensorId, params);

		return;
	}

	void ConfigController::SaveTriggerConfig()
	{

		TriggerParameters tp = GetCurrentTriggerParams();

		// Get triggers parameters
		try
		{
			config.LoadTriggersConfig();
		}
		catch(const Exception& e)
		{
			errorDialog(e);
			return;
		}

		std::vector<TriggerParameters> triggersParameters = config.GetTriggersParameters();

		// Find the trigger we want to modify
		auto triggerIt = std::find_if(triggersParameters.begin(), triggersParameters.end(), [&](TriggerParameters& t) { return t.sensorId == tp.sensorId; });

		if(triggerIt == triggersParameters.end())
		{
			// Error: trigger doesn't exist.
			errorDialog("Error: trigger " + std::to_string(tp.sensorId) + " doesn't exist.", errorType::error_type_error);
			return;
		}

		// Update parameters
		*triggerIt = tp;

		config.SetTriggersParameters(triggersParameters);

		// Save
		try
		{
			config.SaveTriggersConfig();
		}
		catch(const Exception& e)
		{
			errorDialog(e);
		}

		triggerConfigWindow->hide();
		triggerSelectWindow->show();

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

		try
		{
			config.SaveSensorsConfig();
		}
		catch(const Exception& e)
		{
			errorDialog(e);
			return;
		}
		

		sensorsConfigWindow->hide();

		return;
	}

	void ConfigController::TriggerDelete(int sensorId)
	{

		if(config.GetNbTriggers() > 1)
		{
			// Delete trigger
			try
			{
				config.DeleteTrigger(sensorId);
			}
			catch(const Exception& e)
			{
				errorDialog(e);
			}

			// Update triggers config window
			ShowTriggersConfigWindow();
		}
	}

	void ConfigController::TriggerConfiguration(std::size_t sensorId)
	{


		triggerSelectWindow->hide();

		// Create pointers
		Gtk::Entry* sensorNb = nullptr;
		Gtk::Entry* threshold = nullptr;
		Gtk::Entry* scanTime = nullptr;
		Gtk::Entry* maskTime = nullptr;
		Gtk::Entry* gain = nullptr;
		Gtk::ComboBoxText* types = nullptr;
		Gtk::ComboBoxText* responses = nullptr;

		// Get widgets
		{
			builder->get_widget("TCSensorNb", sensorNb);
			builder->get_widget("TCThreshold", threshold);
			builder->get_widget("TCGain", gain);
			builder->get_widget("TCScanTime", scanTime);
			builder->get_widget("TCMaskTime", maskTime);
			builder->get_widget("TCTypes", types);
			builder->get_widget("TCResponses", responses);
		}

		const std::vector<TriggerParameters>& triggers = config.GetTriggersParameters();

		if(sensorId >= triggers.size())
		{
			errorDialog("The selected trigger does not exist", error_type_warning);
			return;
		}

		const TriggerParameters& trigger = triggers[sensorId];

		const std::string type(trigger.type);
		const std::string response(trigger.response);

		// Set fields values
		{
			sensorNb->set_text(std::to_string(trigger.sensorId));
			gain->set_text(std::to_string(trigger.gain));
			threshold->set_text(std::to_string(trigger.threshold));
			scanTime->set_text(std::to_string(trigger.scanTime));
			maskTime->set_text(std::to_string(trigger.maskTime));
			types->set_active_text(type);
			responses->set_active_text(response);
		}

		triggerConfigWindow->show();

		return;
	}

	void ConfigController::AddTrigger()
	{
		const auto sensorId = GetWidget<Gtk::Entry>(builder, "TASensorNb")->get_text();
		const auto threshold = GetWidget<Gtk::Entry>(builder, "TAThreshold")->get_text();
		const auto gain = GetWidget<Gtk::Entry>(builder, "TAGain")->get_text();
		const auto scanTime = GetWidget<Gtk::Entry>(builder, "TAScanTime")->get_text();
		const auto maskTime = GetWidget<Gtk::Entry>(builder, "TAMaskTime")->get_text();
		const auto type = GetWidget<Gtk::ComboBoxText>(builder, "TATypes")->get_active_text();
		const auto response = GetWidget<Gtk::ComboBoxText>(builder, "TAResponses")->get_active_text();

		TriggerParameters trigger;
		trigger.sensorId = std::stoi(sensorId.raw());
		trigger.threshold = std::stoi(threshold.raw());
		trigger.gain = std::stod(gain.raw());
		trigger.scanTime = std::stoi(scanTime.raw());
		trigger.maskTime = std::stoi(maskTime.raw());
		std::copy(type.begin(), type.end(), trigger.type);
		std::copy(response.begin(), response.end(), trigger.response);

		try
		{
			config.AddTrigger(trigger);
		}
		catch(const Exception& e)
		{
			errorDialog(e);
			return;
		}

		triggerAddWindow->hide();
		ShowTriggersConfigWindow();
	}



} /* namespace Controllers */
