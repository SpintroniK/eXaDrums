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
	  fadersList(nullptr),
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

			// Faders' box
			builder->get_widget("FadersList", fadersList);

			// Dialogs
			builder->get_widget("eXaDrumsAboutDialog", aboutDialog);
			builder->get_widget("DeleteKitDialog", deleteKitDialog);
		}

		// Start drum kit
		const std::string moduleLocation(mainFolder+"/../Data/");
		drumKit = std::unique_ptr<eXaDrums>(new eXaDrums(moduleLocation.c_str()));

		// Retrieve kit names
		std::vector<std::string> kitNames = RetrieveKitsNames();

		// Add kits to the list
		for(std::string const& name : kitNames)
		{
			kitsList->append(name);
		}
		// Set default kit
		kitsList->set_active(0);


		// Add faders
		UpdateFaders();


		// Load current kit
		drumKit->SelectKit(GetCurrentKitId());

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

	void Controller::SetInstrumentVolume(FaderPtr& fader)
	{

		drumKit->SetInstrumentVolume(fader->GetInstrumentId(), fader->GetValue());

		return;
	}

	void Controller::UpdateFaders()
	{

		// Remove existing faders
		std::for_each(faders.begin(), faders.end(), [](FaderPtr& fader) { fader.reset(); });
		faders.clear();

		std::vector<std::string> instNames = RetrieveInstrumentsNames();
		for(std::size_t i = 0; i < instNames.size(); i++)
		{
			std::string name(instNames[i]);
			FaderPtr fader(new Fader(name, i, 20));
			faders.push_back(fader);
		}

		// Add all faders to GUI
		std::for_each(faders.cbegin(), faders.cend(), [this](FaderPtr const& f){ this->fadersList->add(*f); });

		// Connect faders signals
		for(FaderPtr& fader : faders)
		{
			fader->GetScale().signal_value_changed().connect(std::bind(sigc::mem_fun(this, &Controller::SetInstrumentVolume), std::ref(fader)));
		}

		return;
	}

	std::vector<std::string> Controller::RetrieveKitsNames() const
	{

		int numKits = drumKit->GetNumKits();

		// Get kit names
		std::vector<std::string> kitsNames(numKits);
		{
			for(int i = 0; i < numKits; i++)
			{

				// Create local array to store string given by libeXaDrums
				char kitName[128];
				int nameLength;

				// Get characters and string's length
				drumKit->GetKitNameById(i, kitName, nameLength);

				// Convert to string
				std::string name(kitName, nameLength);

				kitsNames[i] = name;
			}
		}

		return kitsNames;
	}

	std::vector<std::string> Controller::RetrieveInstrumentsNames() const
	{

		int numInstruments = drumKit->GetNumInstruments();

		// Get instruments names
		std::vector<std::string> instNames(numInstruments);
		{
			for(int i = 0; i < numInstruments; i++)
			{

				// Create local array to store string given by libeXaDrums
				char instName[128];
				int nameLength;

				// Get characters and string's length
				drumKit->GetInstrumentName(i, instName, nameLength);

				// Convert to string
				std::string name(instName, nameLength);

				instNames[i] = name;
			}
		}

		return instNames;
	}


	int Controller::GetCurrentKitId() const
	{

		int currentKitId = kitsList->get_active_row_number();

		return currentKitId;
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
		drumKit->SelectKit(GetCurrentKitId());

		// Update faders
		this->UpdateFaders();

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
