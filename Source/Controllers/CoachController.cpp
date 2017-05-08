/*
 * CoachController.cpp
 *
 *  Created on: 7 May 2017
 *      Author: jeremy
 */

#include "CoachController.h"

#include <gtkmm/grid.h>
#include <glibmm/main.h>

#include <chrono>

using namespace std::chrono;

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
			this->builder->get_widget("HitMeterBar", hitMeterBar);
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

	bool CoachController::UpdateCoach()
	{


		// Update trigger section
		{
			high_resolution_clock::time_point now = high_resolution_clock::now();
			unsigned long long t = (unsigned long long) time_point_cast<microseconds>(now).time_since_epoch().count();
			unsigned long long lastTrigTime = drumKit->GetLastTrigTime();

			unsigned long long dt = (t - lastTrigTime);

			double fraction = std::exp(-double(dt) / 200000.0);
			double value = double(drumKit->GetLastTrigValue()) / 100.0;

			hitMeterBar->set_value(value * fraction);
		}

		// Update click section
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
		}

		return true;
	}

	void CoachController::OpenRhythmCoach()
	{

		coachTimeout = Glib::signal_timeout().connect(sigc::mem_fun(this, &CoachController::UpdateCoach), 20);

		coachWindow->show();

		return;
	}

	void CoachController::CloseRhythmCoach()
	{

		coachWindow->hide();

		coachTimeout.disconnect();

		return;
	}


} /* namespace Controllers */
