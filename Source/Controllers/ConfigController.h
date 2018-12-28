/*
 * ConfigController.h
 *
 *  Created on: 9 Feb 2017
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_CONFIGCONTROLLER_H_
#define SOURCE_CONTROLLERS_CONFIGCONTROLLER_H_

#include <libexadrums/Api/eXaDrums.h>
#include <libexadrums/Api/Config/Config_api.h>

#include "../Widgets/TriggerSelector.h"

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/comboboxtext.h>

namespace Controllers
{

	class ConfigController
	{

	public:

		ConfigController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit);
		virtual ~ConfigController();

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

		void ShowSoundEffectsWindow();
		void ShowSensorsConfigWindow();
		void SaveSensorsConfig();
		void TriggerConfiguration(int sensorId);
		void AddTrigger();
		void TriggerDelete(int sensorId);

		Glib::RefPtr<Gtk::Builder> builder;
		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;

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

		// eXaDrums
		eXaDrumsApi::Config config;


	};

} /* namespace Controllers */

#endif /* SOURCE_CONTROLLERS_CONFIGCONTROLLER_H_ */
