/*
 * CoachController.h
 *
 *  Created on: 7 May 2017
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_COACHCONTROLLER_H_
#define SOURCE_CONTROLLERS_COACHCONTROLLER_H_

#include <libexadrums/Api/eXaDrums.hpp>

#include <gtkmm/builder.h>
#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/scale.h>
#include <gtkmm/levelbar.h>


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
		bool UpdateCoach();

		Glib::RefPtr<Gtk::Builder> builder;
		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;

		Gtk::Window* coachWindow;
		Gtk::Button* coachButton;
		Gtk::Button* coachCloseButton;
		Gtk::Scale* clickMeter;
		Gtk::Scale* jitterMeter;
		Gtk::LevelBar* hitMeterBar;

		sigc::connection coachTimeout;

	};

} /* namespace Controllers */

#endif /* SOURCE_CONTROLLERS_COACHCONTROLLER_H_ */
