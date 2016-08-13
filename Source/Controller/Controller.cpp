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
	  kitsList(nullptr),
	  aboutDialog(nullptr)
	{

		// Get all widgets
		{
			builder->get_widget("AboutButton", aboutButton);
			builder->get_widget("PlayButton", playButton);
			builder->get_widget("KitsList", kitsList);
			builder->get_widget("eXaDrumsAboutDialog", aboutDialog);
		}

		// Start drum kit
		const std::string moduleLocation(mainFolder+"/../Data/");
		// Create and load drum kit
		drumKit = std::unique_ptr<eXaDrums>(new eXaDrums(moduleLocation.c_str(), IO::SensorType::Hdd));

		// Add kits to the list
		{
			int numKits = drumKit->GetNumKits();
			for(int i = 0; i < numKits; i++)
			{
				std::string kitName = this->GetKitNameById(i);
				kitsList->append(kitName);
			}
			//xxx Set current kit to first of the list
			kitsList->set_active(1);
		}

		const std::string currentKitName = GetCurrentKitName();
		const std::string kitLocation("Kits/" + currentKitName);

		drumKit->LoadKit(kitLocation.c_str());

		// Connect all signals
		{
			aboutButton->signal_clicked().connect(sigc::mem_fun(this, &Controller::ShowAboutDialog));
			playButton->signal_clicked().connect(sigc::mem_fun(this, &Controller::PlayDrums));
			//kitsList->signal_changed().connect()
			aboutDialog->signal_response().connect(std::bind(sigc::mem_fun(this, &Controller::HideAboutDialog), 0));
		}


		return;
	}

	Controller::~Controller()
	{

		// Delete all pointers
		delete aboutButton;
		delete aboutDialog;
		delete playButton;
		delete kitsList;

		if(drumKit->IsStarted())
		{
			drumKit->Stop();
		}

		return;
	}

	// PRIVATE


	std::string Controller::GetKitNameById(int id) const
	{

		// Create local array to store string given by libeXaDrums
		char kitName[128];
		int nameLength;

		// Get characters and string's length
		drumKit->GetKitNameById(id, kitName, nameLength);

		// Convert to string
		std::string name(kitName, nameLength);

		return name;
	}


	std::string Controller::GetCurrentKitName() const
	{

		int currentKitId = kitsList->get_active_row_number();

		return GetKitNameById(currentKitId);
	}


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
			this->playButton->set_property("label", Gtk::StockID("gtk-media-play"));
			drumKit->Stop();
		}
		else
		{
			this->playButton->set_property("label", Gtk::StockID("gtk-media-stop"));
			drumKit->Start();
		}

		return;
	}

} /* namespace Gui */
