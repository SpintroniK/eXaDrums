/*
 * CoachController.cpp
 *
 *  Created on: 7 May 2017
 *      Author: jeremy
 */

#include "CoachController.h"

#include <gtkmm/grid.h>
#include <glibmm/main.h>


namespace Controllers
{

	CoachController::CoachController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit)
	: builder(builder), drumKit(drumKit)
	{

		// Get all widgets
		{
			this->builder->get_widget("CoachWindow", coachWindow);
			this->builder->get_widget("CoachButton", coachButton);
			this->builder->get_widget("CoachCloseButton", coachCloseButton);
			this->builder->get_widget("ClickMeter", clickMeter);
		}

		// Connect all signals
		{
			coachButton->signal_clicked().connect(sigc::mem_fun(this, &CoachController::OpenRhythmCoach));
			coachCloseButton->signal_clicked().connect(sigc::mem_fun(this, &CoachController::CloseRhythmCoach));
		}


		return;
	}

	CoachController::~CoachController()
	{

		delete coachWindow;

		return;
	}

	bool CoachController::UpdateClickMeter()
	{

		double fraction = drumKit->GetClickPosition();

		fraction *= drumKit->GetBpmeas();

		if(int(fraction) % 2 != 0)
		{
			this->clickMeter->set_inverted(false);
		}
		else
		{

			this->clickMeter->set_inverted(true);
		}

		fraction -= int(fraction);


		// Clip fraction's value
		fraction = std::min<double>(std::max<double>(0.0, fraction), 1.0);

		this->clickMeter->set_value(100*fraction);

		return true;
	}

	void CoachController::OpenRhythmCoach()
	{

		clickMeterTimeout = Glib::signal_timeout().connect(sigc::mem_fun(this, &CoachController::UpdateClickMeter), 20);

		coachWindow->show();

		return;
	}

	void CoachController::CloseRhythmCoach()
	{

		coachWindow->hide();

		clickMeterTimeout.disconnect();

		return;
	}


} /* namespace Controllers */
