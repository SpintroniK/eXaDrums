/*
 * ConfigController.h
 *
 *  Created on: 9 Feb 2017
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_CONFIGCONTROLLER_H_
#define SOURCE_CONTROLLERS_CONFIGCONTROLLER_H_

#include <Source/Api/eXaDrums.h>

#include <gtkmm/builder.h>

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
		void ShowTriggersConfigWindow();
		void ShowSoundEffectsWindow();
		void ShowSensorsConfigWindow();

		Glib::RefPtr<Gtk::Builder> builder;
		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;


	};

} /* namespace Controllers */

#endif /* SOURCE_CONTROLLERS_CONFIGCONTROLLER_H_ */