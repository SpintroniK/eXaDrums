/*
 * Controller.cpp
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#include "Controller.h"

namespace Gui
{

	Controller::Controller(Glib::RefPtr<Gtk::Builder>& builder)
	: builder(builder),
	  playButton(nullptr)
	{

		// Get all widgets
		builder->get_widget("PlayButton", playButton);

		// Start drum kit
		const std::string moduleLocation("../Data/");
		const std::string kitLocation("Kits/default.xml");

		drumKit = std::unique_ptr<eXaDrums>(new eXaDrums(moduleLocation.c_str(), IO::SensorType::Hdd));

		drumKit->LoadKit(kitLocation.c_str());

		// Connect all signals
		playButton->signal_clicked().connect(sigc::mem_fun(this, &Controller::PlayDrums));

		return;
	}

	Controller::~Controller()
	{

		// Delete all pointers
		delete playButton;

		if(drumKit->IsStarted())
		{
			drumKit->Stop();
		}

		return;
	}

	// PRIVATE

	void Controller::PlayDrums()
	{

		if(drumKit->IsStarted())
		{
			drumKit->Stop();
		}
		else
		{
			drumKit->Start();
		}

		return;
	}

} /* namespace Gui */
