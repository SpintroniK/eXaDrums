/*
 * CoachController.cpp
 *
 *  Created on: 7 May 2017
 *      Author: jeremy
 */

#include "CoachController.h"

#include <gtkmm/grid.h>
#include <glibmm/main.h>
#include <gtkmm/label.h>

#include <chrono>

using namespace std::chrono;

namespace Controllers
{

	CoachController::CoachController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit)
	: builder(builder), drumKit(std::move(drumKit))
	{

		// Get all widgets
		{
			this->builder->get_widget("CoachWindow", coachWindow);
			this->builder->get_widget("CoachButton", coachButton);
			this->builder->get_widget("CoachCloseButton", coachCloseButton);
			this->builder->get_widget("ClickMeter", clickMeter);
			this->builder->get_widget("CoachJitterMeter", jitterMeter);
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


		double clickPos = drumKit->GetClickPosition();
		int bpm =  drumKit->GetBpmeas();
		double beatPos = clickPos * bpm;

		double beatFraction = beatPos - int(beatPos);
		beatFraction = std::min<double>(std::max<double>(0.0, beatFraction), 1.0);


		double clickFraction = clickPos - int(clickPos);

		// Update click section
		{

			if(int(beatPos) % 2 != 0)
			{
				this->clickMeter->set_inverted(false);
			}
			else
			{
				this->clickMeter->set_inverted(true);
			}


			// Clip fraction's value

			this->clickMeter->set_value(100*beatFraction);
		}

		// Update LEDs states
		{
			Gtk::Label* greenLed = nullptr;
			Gtk::Label* redLed = nullptr;

			this->builder->get_widget("CoachGreenLed", greenLed);
			this->builder->get_widget("CoachRedLed", redLed);

			double th = 0.2;

			if(beatFraction < th)
			{
				greenLed->set_visible(true);
			}
			else
			{
				greenLed->set_visible(false);
			}

			if(clickFraction < th/double(bpm))
			{
				redLed->set_visible(true);
			}
			else
			{
				redLed->set_visible(false);
			}

		}


		// Update hit meter section
		long long lastTrigTime = drumKit->GetLastTrigTime();
		{
			high_resolution_clock::time_point now = high_resolution_clock::now();
			long long t = (long long) time_point_cast<microseconds>(now).time_since_epoch().count();

			long long dt = (t - lastTrigTime);

			double fraction = std::exp(-double(dt) / 200000.0);
			double value = double(drumKit->GetLastTrigValue()) / 100.0;

			hitMeterBar->set_value(std::max(value * fraction, 0.));
		}

		// Check accuracy
		{
			long long lastClickTime = drumKit->GetLastClickTime();
			int tempo = drumKit->GetTempo();
			double measureDuration = bpm * 60e6 / double(tempo) / drumKit->GetRhythm(); // Measure duration in µs

			// Create vector of the clicks times
			std::vector<long long> clicksTimes(bpm + 1);

			for(std::size_t i = 0; i < clicksTimes.size(); i++)
			{
				clicksTimes[i] =  lastClickTime + (long long)(i * (measureDuration / bpm));
			}

			std::vector<int> offsets(clicksTimes.size());
			std::transform(clicksTimes.begin(), clicksTimes.end(), offsets.begin(), [&](long long v) { return int(lastTrigTime - v); });


			// Find the most accurate hit's error
			int bestHitError = *std::min_element(offsets.begin(), offsets.end(), [](int x, int y) { return std::abs(x) < std::abs(y); });

			int maxError = int(measureDuration / bpm);
			int jitterValue = -(100 * bestHitError) / maxError + 50;

			jitterMeter->set_value(jitterValue);

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
