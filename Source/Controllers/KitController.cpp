/*
 * KitController.cpp
 *
 *  Created on: 19 Nov 2016
 *      Author: jeremy
 */

#include "KitController.h"


using namespace eXaDrumsApi;
using namespace Widgets;

namespace Controllers
{

	KitController::KitController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrums> drumKit)
	: builder(builder), drumKit(drumKit)
	{

		std::string dataFolder = GetDataFolderLoc();

		this->kitCreator = std::unique_ptr<KitCreator>(new KitCreator(dataFolder.c_str()));


		// Get all widgets
		{
			// Buttons
			builder->get_widget("DeleteDrumKitButton", deleteKitButton);
			builder->get_widget("AddDrumKitButton", addDrumKitButton);
			builder->get_widget("KitNameCancel", kitNameCancel);
			builder->get_widget("PlayButton", playButton);

			// Entries
			builder->get_widget("KitNameEntry", kitNameEntry);

			// Lists
			builder->get_widget("KitsList", kitsList);

			// Faders' box
			builder->get_widget("FadersSaveButton", saveFaders);
			builder->get_widget("FadersList", fadersList);

			// Dialogs
			builder->get_widget("DeleteKitDialog", deleteKitDialog);

			// Windows
			builder->get_widget("NewKitNameWindow", newKitNameWindow);


		}

		// Populate Kits list
		CreateKitsList();


		// Add faders
		UpdateFaders();
		saveFaders->set_sensitive(false);


		// Load current kit
		drumKit->SelectKit(GetCurrentKitId());

		// Connect signals
		{
			deleteKitButton->signal_clicked().connect(sigc::mem_fun(this, &KitController::DeleteKitDialog));
			playButton->signal_clicked().connect(sigc::mem_fun(this, &KitController::PlayDrums));
			saveFaders->signal_clicked().connect(sigc::mem_fun(this, &KitController::SaveFaders));
			addDrumKitButton->signal_clicked().connect(sigc::mem_fun(this, &KitController::ShowNewKitWindow));
			kitNameCancel->signal_clicked().connect(sigc::mem_fun(this, &KitController::HideNewKitWindow));

			// Entries
			//kitNameEntry->signal_grab_focus().connect(sigc::mem_fun(this, &KitController::ShowKeyboard));

			// Kits list
			kitsList->signal_changed().connect(sigc::mem_fun(this, &KitController::ChangeKit));
		}

		return;
	}

	KitController::~KitController()
	{

		// Delete all pointers (dialogs and windows)
		delete newKitNameWindow;
		delete deleteKitDialog;

		return;
	}


	// Private Methods

	std::string KitController::GetDataFolderLoc() const
	{

		char folder[256];
		int folderLength;

		drumKit->GetDataLocation(folder, folderLength);

		return std::string(folder, folderLength);
	}

	std::vector<std::string> KitController::RetrieveKitsNames() const
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

	void KitController::CreateKitsList()
	{

		// Retrieve kits names
		std::vector<std::string> kitsNames = RetrieveKitsNames();

		// Add kits to the list
		for(std::size_t i = 0; i < kitsNames.size(); i++)
		{
			kitsList->insert(i, kitsNames[i]);
		}
		// Set default kit
		kitsList->set_active(0);

		return;
	}

	int KitController::GetCurrentKitId() const
	{

		int currentKitId = kitsList->get_active_row_number();

		return currentKitId;
	}

	void KitController::DeleteKitDialog()
	{

		// Get answer
		int answer = deleteKitDialog->run();

		// Check answer
		switch (answer)
		{
			case Gtk::RESPONSE_CANCEL: break;
			case Gtk::RESPONSE_OK: this->DeleteKit(GetCurrentKitId()); break;
			default: break;
		}

		// Close dialog
		deleteKitDialog->hide();

		return;
	}

	void KitController::DeleteKit(const int& id)
	{

		int numKits = drumKit->GetNumKits();

		// Can't delete if only one kit
		if(numKits > 1)
		{
			// Stop module if started
			if(drumKit->IsStarted())
			{
				PlayDrums();
			}

			// Deselect kit
			int activeKit;

			if(id == 0)
			{
				activeKit = 1;
			}
			else
			{
				activeKit = id - 1;
			}


			kitsList->set_active(activeKit);

			// Delete kit
			drumKit->DeleteKit(id);

			// Remove kit from list
			kitsList->remove_text(id);

			// Set new kit
			ChangeKit();

		}

		return;
	}

	void KitController::PlayDrums()
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

	void KitController::ChangeKit()
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
		saveFaders->set_sensitive(false);

		// Restart module if needed
		if(started)
		{
			drumKit->Start();
		}

		return;
	}

	void KitController::SetInstrumentVolume(FaderPtr& fader) const
	{

		saveFaders->set_sensitive(true);
		drumKit->SetInstrumentVolume(fader->GetInstrumentId(), fader->GetValue());

		return;
	}


	std::vector<std::string> KitController::RetrieveInstrumentsNames() const
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

	void KitController::SaveFaders() const
	{

		SaveKitConfig();

		// Disable button
		saveFaders->set_sensitive(false);

		return;
	}

	void KitController::UpdateFaders()
	{

		// Remove existing faders
		std::for_each(faders.begin(), faders.end(), [](FaderPtr& fader) { fader.reset(); });
		faders.clear();

		std::vector<std::string> instNames = RetrieveInstrumentsNames();
		for(std::size_t i = 0; i < instNames.size(); i++)
		{
			std::string name(instNames[i]);
			int volume = GetInstrumentVolume(i);

			FaderPtr fader(new Fader(name, i, volume));

			faders.push_back(fader);
		}

		// Add all faders to GUI
		std::for_each(faders.cbegin(), faders.cend(), [this](FaderPtr const& f){ this->fadersList->add(*f); });

		// Connect faders signals
		for(FaderPtr& fader : faders)
		{
			fader->GetScale().signal_value_changed().connect(std::bind(sigc::mem_fun(this, &KitController::SetInstrumentVolume), std::ref(fader)));
		}

		return;
	}


	void KitController::ShowNewKitWindow()
	{

		newKitNameWindow->show();
		ShowKeyboard();

		return;
	}

	void KitController::HideNewKitWindow()
	{

		HideKeyboard();
		newKitNameWindow->hide();
		return;
	}


	void KitController::ShowKeyboard()
	{
		HideKeyboard();
		std::system("onboard --size=800x160 -x 0 -y 280 &");
		return;
	}

	void KitController::HideKeyboard()
	{

		std::system("killall onboard");
		return;
	}



} /* namespace Gui */
