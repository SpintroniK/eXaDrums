/*
 * Controller.cpp
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#include "Controller.h"

namespace Gui
{

	Controller::Controller(Glib::RefPtr<Gtk::Builder>& builder, std::string const& mainFolder)
	: mainFolder(mainFolder),
	  builder(builder),
	  aboutButton(nullptr),
	  playButton(nullptr),
	  aboutDialog(nullptr)
	{

		// Get all widgets
		builder->get_widget("AboutButton", aboutButton);
		builder->get_widget("PlayButton", playButton);
		builder->get_widget("eXaDrumsAboutDialog", aboutDialog);

		// Start drum kit
		const std::string moduleLocation(mainFolder+"/../Data/");
		const std::string kitLocation("Kits/default.xml");


		drumKit = std::unique_ptr<eXaDrums>(new eXaDrums(moduleLocation.c_str(), IO::SensorType::Hdd));

		drumKit->LoadKit(kitLocation.c_str());

		// Connect all signals
		aboutButton->signal_clicked().connect(sigc::mem_fun(this, &Controller::ShowAboutDialog));
		playButton->signal_clicked().connect(sigc::mem_fun(this, &Controller::PlayDrums));
		aboutDialog->signal_response().connect(std::bind(sigc::mem_fun(this, &Controller::HideAboutDialog), 0));

		return;
	}

	Controller::~Controller()
	{

		// Delete all pointers
		delete aboutButton;
		delete aboutDialog;
		delete playButton;

		if(drumKit->IsStarted())
		{
			drumKit->Stop();
		}

		return;
	}

	// PRIVATE

	void Controller::ShowAboutDialog()
	{

		aboutDialog->show();

		return;
	}

	void Controller::HideAboutDialog(int responseId)
	{

		aboutDialog->hide();

		return;
	}

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
