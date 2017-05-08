/*
 * CoachController.h
 *
 *  Created on: 7 May 2017
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_COACHCONTROLLER_H_
#define SOURCE_CONTROLLERS_COACHCONTROLLER_H_

#include <Source/Api/eXaDrums.h>

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/scale.h>


namespace Controllers
{

	class CoachController
	{

	public:

		CoachController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit);
		virtual ~CoachController();

	private:

		void OpenRhythmCoach();
		void CloseRhythmCoach();
		bool UpdateClickMeter();

		Glib::RefPtr<Gtk::Builder> builder;
		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;

		Gtk::Window* coachWindow;
		Gtk::Button* coachButton;
		Gtk::Button* coachCloseButton;
		Gtk::Scale* clickMeter;
		sigc::connection clickMeterTimeout;

	};

} /* namespace Controllers */

#endif /* SOURCE_CONTROLLERS_COACHCONTROLLER_H_ */
