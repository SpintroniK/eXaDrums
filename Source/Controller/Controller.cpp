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
	: mainFolder(mainFolder), builder(builder),
	  aboutButton(nullptr), playButton(nullptr), deleteKitButton(nullptr),
	  kitsList(nullptr),
	  aboutDialog(nullptr), deleteKitDialog(nullptr)
	{

		// Get all widgets
		{
			// Button
			builder->get_widget("AboutButton", aboutButton);
			builder->get_widget("PlayButton", playButton);
			builder->get_widget("DeleteDrumKitButton", deleteKitButton);

			// Kits list
			builder->get_widget("KitsList", kitsList);

			// Dialogs
			builder->get_widget("eXaDrumsAboutDialog", aboutDialog);
			builder->get_widget("DeleteKitDialog", deleteKitDialog);
		}

		// Start drum kit
		const std::string moduleLocation(mainFolder+"/../Data/");
		drumKit = std::unique_ptr<eXaDrums>(new eXaDrums(moduleLocation.c_str()));

		// Add kits to the list
		{
			int numKits = drumKit->GetNumKits();
			for(int i = 0; i < numKits; i++)
			{
				std::string kitName = this->GetKitNameById(i);
				kitName[0] = std::toupper(kitName[0]);
				kitsList->append(kitName);
			}
			//xxx Set current kit to first of the list
			kitsList->set_active(0);
		}

		const std::string currentKitName = GetCurrentKitName();
		const std::string kitLocation("Kits/" + currentKitName + ".xml");

		drumKit->LoadKit(kitLocation.c_str());

		// Connect all signals
		{
			// Buttons
			aboutButton->signal_clicked().connect(sigc::mem_fun(this, &Controller::ShowAboutDialog));
			playButton->signal_clicked().connect(sigc::mem_fun(this, &Controller::PlayDrums));
			deleteKitButton->signal_clicked().connect(sigc::mem_fun(this, &Controller::DeleteKitDialog));

			// Kits list
			kitsList->signal_changed().connect(sigc::mem_fun(this, &Controller::ChangeKit));

			// Dialog
			aboutDialog->signal_response().connect(std::bind(sigc::mem_fun(this, &Controller::HideAboutDialog), 0));
		}


		return;
	}

	Controller::~Controller()
	{

		// Delete all pointers (dialogs and windows)
		delete deleteKitDialog;
		delete aboutDialog;

		// Stop drum kit
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

	void Controller::ChangeKit()
	{

		bool started = drumKit->IsStarted();

		// Stop module if started
		if(started)
		{
			drumKit->Stop();
		}


		// Load new kit
		const std::string currentKitName = GetCurrentKitName();
		const std::string kitLocation("Kits/" + currentKitName + ".xml");
		drumKit->LoadKit(kitLocation.c_str());

		// Restart module if needed
		if(started)
		{
			drumKit->Start();
		}

		return;
	}

	void Controller::DeleteKitDialog()
	{

		// Get answer
		int answer = deleteKitDialog->run();

		// Check answer
		switch (answer)
		{
			case Gtk::RESPONSE_CANCEL: break;

			case Gtk::RESPONSE_OK:
			{

			}
			break;

			default: break;
		}

		// Close dialog
		deleteKitDialog->hide();

		return;
	}

} /* namespace Gui */
