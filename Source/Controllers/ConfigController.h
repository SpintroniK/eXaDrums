/*
 * ConfigController.h
 *
 *  Created on: 9 Feb 2017
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_CONFIGCONTROLLER_H_
#define SOURCE_CONTROLLERS_CONFIGCONTROLLER_H_

#include <libexadrums/Api/eXaDrums.hpp>
#include <libexadrums/Api/Config/Config_api.hpp>

#include "../Widgets/TriggerSelector.h"

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/filechooserdialog.h>

#include <functional>

namespace Controllers
{

	class ConfigController
	{

	public:

		ConfigController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit, const std::function<void()>& quit);
		virtual ~ConfigController();

		bool IsImportConfig() const { return isImportConfig; }

	private:

		// Signals
		void ShowMixerConfigWindow();
		void ShowSoundLibConfigWindow();

		// Triggers
		void ShowTriggersConfigWindow();
		void ApplyTriggerConfig();
		void CloseTriggerSelectWindow();
		void CloseTriggerConfigWindow();
		void SaveTriggerConfig();
		eXaDrumsApi::TriggerParameters GetCurrentTriggerParams() const;

		// Mixer
		void SaveMixerConfig();

		// Config
		void ExportConfiguration() const;
		void ImportConfiguration();
		void FactoryReset();

		void ShowSoundEffectsWindow();
		void ShowSensorsConfigWindow();
		void SaveSensorsConfig();
		void TriggerConfiguration(std::size_t sensorId);
		void AddTrigger();
		void TriggerDelete(int sensorId);
		bool UpdateTriggerValue(size_t id);

		bool isImportConfig = false;

		Glib::RefPtr<Gtk::Builder> builder;
		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;

		std::function<void()> quitCallback;

		sigc::connection triggerTimeout;

		// Widgets
		std::vector<Widgets::TriggerSelectorPtr> triggersSelectors;

		// Comboboxes
		Gtk::ComboBoxText* mixerDevices;

		// Windows
		Gtk::Window* sensorsConfigWindow;
		Gtk::Window* triggerSelectWindow;
		Gtk::Window* triggerConfigWindow;
		Gtk::Window* triggerAddWindow;
		Gtk::Window* mixerConfigWindow;
		Gtk::Window* importExportConfigWindow;
		Gtk::FileChooserDialog* exportConfigWindow;
		Gtk::FileChooserDialog* importConfigWindow;

		// eXaDrums
		eXaDrumsApi::Config config;


	};

} /* namespace Controllers */

#endif /* SOURCE_CONTROLLERS_CONFIGCONTROLLER_H_ */
