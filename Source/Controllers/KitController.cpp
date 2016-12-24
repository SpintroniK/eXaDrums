/*
 * KitController.cpp
 *
 *  Created on: 19 Nov 2016
 *      Author: jeremy
 */

#include "KitController.h"

#include <gtkmm/entry.h>
#include <gtkmm/messagedialog.h>

#include <functional>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace eXaDrumsApi;
using namespace Widgets;

namespace Controllers
{

	KitController::KitController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrums> drumKit)
	: builder(builder), drumKit(drumKit)
	{

		numInstrumentsToCreate = 0;

		std::string dataFolder = drumKit->GetDataLocation();

		this->kitCreator = std::unique_ptr<KitCreator>(new KitCreator(dataFolder.c_str()));


		Gtk::Button* instrumentConfigOkay = nullptr;
		Gtk::Button* instrumentConfigCancel = nullptr;
		Gtk::Button* kitNameCancel = nullptr;
		Gtk::Button* KitNameOk = nullptr;

		Gtk::ComboBoxText* instrumentConfig_Type = nullptr;



		// Get all widgets
		{
			// Buttons
			builder->get_widget("PlayButton", playButton);
			builder->get_widget("DeleteDrumKitButton", deleteKitButton);
			builder->get_widget("AddDrumKitButton", addDrumKitButton);
			builder->get_widget("InstrumentConfigOkay", instrumentConfigOkay);
			builder->get_widget("InstrumentConfigCancel", instrumentConfigCancel);
			builder->get_widget("KitNameCancel", kitNameCancel);
			builder->get_widget("KitNameOk", KitNameOk);


			// Lists
			builder->get_widget("KitsList", kitsList);

			// Faders' box
			builder->get_widget("FadersSaveButton", saveFaders);
			builder->get_widget("FadersList", fadersList);

			// Comboboxes
			builder->get_widget("InstrumentConfig_Type", instrumentConfig_Type);


			// Windows
			builder->get_widget("NewKitNameWindow", newKitWindow);
			builder->get_widget("InstrumentConfigWindow", instrumentConfigWindow);


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
			playButton->signal_clicked().connect(sigc::mem_fun(this, &KitController::PlayDrums));
			saveFaders->signal_clicked().connect(sigc::mem_fun(this, &KitController::SaveFaders));
			deleteKitButton->signal_clicked().connect(sigc::mem_fun(this, &KitController::DeleteKitDialog));
			addDrumKitButton->signal_clicked().connect(sigc::mem_fun(this, &KitController::AddNewKitWindow));
			instrumentConfigOkay->signal_clicked().connect(sigc::mem_fun(this, &KitController::ValidateInstrumentData));
			instrumentConfigCancel->signal_clicked().connect(sigc::mem_fun(this, &KitController::CancelInstrumentModif));
			kitNameCancel->signal_clicked().connect(sigc::mem_fun(newKitWindow, &Gtk::Window::hide));
			KitNameOk->signal_clicked().connect(sigc::mem_fun(this, &KitController::ValidateKitData));

			// Comboboxes
			instrumentConfig_Type->signal_changed().connect(sigc::mem_fun(this, &KitController::ChangeInstrumentType));

			// Kits list
			kitsList->signal_changed().connect(sigc::mem_fun(this, &KitController::ChangeKit));
		}

		return;
	}

	KitController::~KitController()
	{

		// Delete all pointers (dialogs and windows)
		delete newKitWindow;
		delete instrumentConfigWindow;

		return;
	}


	// Private Methods


	void KitController::CreateKitsList()
	{

		// Retrieve kits names
		std::vector<std::string> kitsNames = drumKit->GetKitsNames();

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


		Gtk::MessageDialog d("Are you sure you want to delete the current drum kit?", false, Gtk::MessageType::MESSAGE_QUESTION, Gtk::ButtonsType::BUTTONS_YES_NO);
		d.set_title("Delete Kit");
		// Get answer
		int answer = d.run();

		// Check answer
		switch (answer)
		{
			case Gtk::ResponseType::RESPONSE_NO: break;
			case Gtk::ResponseType::RESPONSE_YES: this->DeleteKit(GetCurrentKitId()); break;
			default: break;
		}

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

	void KitController::AddNewKit()
	{

		if(drumKit->IsStarted())
		{
			PlayDrums();
		}


		// Retrieve kits names
		std::vector<std::string> oldKitsNames = drumKit->GetKitsNames();

		// Reload kits
		drumKit->ReloadKits();

		// Retrieve kits names
		std::vector<std::string> newkitsNames = drumKit->GetKitsNames();

		auto newOldKit = std::mismatch(newkitsNames.cbegin(), newkitsNames.cend(), oldKitsNames.cbegin());

		// Get new kit's name and position in the list
		std::string newKitName = *(newOldKit.first);
		int pos = std::distance(oldKitsNames.cbegin(), newOldKit.second);

		// Insert new kit into list, and activate it
		kitsList->insert(pos, newKitName);
		kitsList->set_active(pos);

		// Set new kit
		ChangeKit();

		return;
	}

	void KitController::KitAdded()
	{

		Gtk::MessageDialog d("A new drum kit has been added.", false, Gtk::MessageType::MESSAGE_INFO, Gtk::ButtonsType::BUTTONS_OK);
		d.set_title("New kit added");
		d.run();


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

		std::vector<std::string> instNames = drumKit->GetInstrumentsNames();
		for(std::size_t i = 0; i < instNames.size(); i++)
		{
			std::string name(instNames[i]);
			int volume = GetInstrumentVolume(i);

			FaderPtr fader(new Fader(name, i, volume));

			faders.push_back(fader);
		}

		// Add all faders to GUI
		std::for_each(faders.cbegin(), faders.cend(), [this](const FaderPtr& f){ this->fadersList->add(*f); });

		// Connect faders signals
		for(FaderPtr& fader : faders)
		{
			fader->GetScale().signal_value_changed().connect(std::bind(sigc::mem_fun(this, &KitController::SetInstrumentVolume), std::ref(fader)));
		}

		return;
	}


	void KitController::AddNewKitWindow()
	{

		newKitWindow->show();
		ShowKeyboard();

		return;
	}



	void KitController::AddInstrumentToKit()
	{

		int numInstruments = kitCreator->GetNumInstruments();

		if(numInstruments < this->numInstrumentsToCreate)
		{

			// Retrieve data
			std::string instrumentName = "Instrument " + std::to_string(numInstruments + 1);

			// Retrieve window's widgets
			Gtk::Entry* instrumentConfig_Name = nullptr;
			Gtk::ComboBoxText* instrumentConfig_Type = nullptr;

			// Get widgets
			builder->get_widget("InstrumentConfig_Name", instrumentConfig_Name);
			builder->get_widget("InstrumentConfig_Type", instrumentConfig_Type);


			// Create vector of instruments types
			std::vector<std::string> instrumentTypes = kitCreator->GetInstrumentsTypes();

			// Populate instrument config window
			{

				std::string text = instrumentConfig_Type->get_active_text();

				// Populate only if not already done
				if(text == "")
				{

					for(std::size_t i = 0; i < instrumentTypes.size(); i++)
					{
						instrumentConfig_Type->insert(i, instrumentTypes[i]);
					}

					// Set default instrument and call ChangeInstrumentType() method
					instrumentConfig_Type->set_active(0);
				}

			}

			instrumentConfig_Name->set_text(instrumentName);


			// Show window
			instrumentConfigWindow->show();

		}
		else if(numInstruments == this->numInstrumentsToCreate && numInstruments != 0)
		{
			// All instruments have been added, save kit.
			kitCreator->SaveKit();
			instrumentConfigWindow->hide();

			AddNewKit();

			KitAdded();

		}
		else
		{
			// Should never happen => error.
		}

		return;
	}

	void KitController::ChangeInstrumentType()
	{

		Gtk::ComboBoxText* instrumentConfig_Type = nullptr;
		Gtk::Box* instrumentConfig_TriggersBox = nullptr;
		Gtk::Box* instrumentConfig_SoundsBox = nullptr;

		builder->get_widget("InstrumentConfig_Type", instrumentConfig_Type);
		builder->get_widget("InstrumentConfig_TriggersBox", instrumentConfig_TriggersBox);
		builder->get_widget("InstrumentConfig_SoundsBox", instrumentConfig_SoundsBox);



		std::string instrumentType = instrumentConfig_Type->get_active_text();

		// Retrieve triggers locations
		std::vector<std::string> triggersLocations = kitCreator->GetTriggersLocations(instrumentType);

		// Retrieve sounds types
		std::vector<std::string> soundsTypes = kitCreator->GetSoundsTypes(instrumentType);

		// Retrieve sounds files
		std::vector<std::string> soundsFiles = kitCreator->GetSoundsFiles();

		// Create tirggers ids and locations
		{

			std::vector<int> triggersIds = kitCreator->GetTriggersIds();

			std::for_each(triggersIdsAndLocations.begin(), triggersIdsAndLocations.end(), [](TriggerIdAndLocationPtr& t) { t.reset(); });
			triggersIdsAndLocations.clear();

			for(std::size_t i = 0; i < triggersLocations.size(); i++)
			{
				//XXX Need to add the triggers to the kitCreator.
				triggersIdsAndLocations.push_back(std::make_shared<TriggerIdAndLocation>(triggersLocations, triggersIds));
			}

			std::for_each(triggersIdsAndLocations.cbegin(), triggersIdsAndLocations.cend(), [&instrumentConfig_TriggersBox](const TriggerIdAndLocationPtr& t){ instrumentConfig_TriggersBox->add(*t); });
		}

		// Create sounds types and paths
		{

			std::for_each(soundsTypesAndPaths.begin(), soundsTypesAndPaths.end(), [](SoundTypeAndPathPtr& t) { t.reset(); });
			soundsTypesAndPaths.clear();

			for(std::size_t i = 0; i < soundsTypes.size(); i++)
			{
				soundsTypesAndPaths.push_back(std::make_shared<SoundTypeAndPath>(soundsTypes, soundsFiles));
			}

			// Add sounds types to window
			std::for_each(soundsTypesAndPaths.cbegin(), soundsTypesAndPaths.cend(), [&instrumentConfig_SoundsBox](const SoundTypeAndPathPtr& t){ instrumentConfig_SoundsBox->add(*t); });

		}

		return;
	}

	void KitController::CancelInstrumentModif()
	{

		kitCreator->CreateNewKit();
		this->numInstrumentsToCreate = 0;

		this->instrumentConfigWindow->hide();

		return;
	}

	void KitController::ValidateInstrumentData()
	{

		Gtk::Entry* instrumentConfig_Name = nullptr;
		Gtk::ComboBoxText* instrumentConfig_Type = nullptr;

		builder->get_widget("InstrumentConfig_Name", instrumentConfig_Name);
		builder->get_widget("InstrumentConfig_Type", instrumentConfig_Type);

		// Get instrument name
		std::string instrumentName = instrumentConfig_Name->get_text();
		// Get instrument type
		std::string instrumentType = instrumentConfig_Type->get_entry_text();

		// Create instrument
		kitCreator->CreateNewInstrument();
		kitCreator->SetInstrumentVolume(1.0f);
		kitCreator->SetInstrumentName(instrumentName.c_str());
		kitCreator->SetInstrumentType(instrumentType.c_str());

		// Add instrument sounds
		for(const auto& sound : soundsTypesAndPaths)
		{
			std::string soundType = sound->GetSoundType();
			std::string soundFile = sound->GetSound();

			kitCreator->AddInstrumentSound(soundFile.c_str(), soundType.c_str());
		}

		// Add instrument triggers
		for(const auto& trigger : triggersIdsAndLocations)
		{
			int id = trigger->GetTriggerId();
			std::string location = trigger->GetTriggerLoc();

			kitCreator->AddInstrumentTrigger(id, location.c_str());
		}

		kitCreator->AddInstrumentToKit();


		AddInstrumentToKit();

		return;
	}

	void KitController::ValidateKitData()
	{

		Gtk::Entry* kitNameEntry = nullptr;
		Gtk::Entry* numInstrumentsEntry = nullptr;


		builder->get_widget("KitNameEntry", kitNameEntry);
		builder->get_widget("NumInstrumentsEntry", numInstrumentsEntry);

		std::string kitName = kitNameEntry->get_text();

		// Check kit name
		std::vector<std::string> kitsNames = drumKit->GetKitsNames();
		auto it = std::find(kitsNames.cbegin(), kitsNames.cend(), kitName);
		if(it != kitsNames.cend())
		{

			Gtk::MessageDialog d("A drum kit with the same name already exists.", false, Gtk::MessageType::MESSAGE_ERROR, Gtk::ButtonsType::BUTTONS_CLOSE);
			d.set_title("Error");
			d.run();

			return;
		}

		if(kitName.length() < 3)
		{
			return;
		}

		int numInstruments;
		try
		{
			numInstruments = std::stoi(numInstrumentsEntry->get_text());
		}
		catch(std::invalid_argument& e)
		{
			// Return so that the entry isn't validated
			return;
		}

		this->numInstrumentsToCreate = numInstruments;

		// Create kit
		kitCreator->CreateNewKit();
		kitCreator->SetKitName(kitName.c_str());

		// Hide window
		this->newKitWindow->hide();
		HideKeyboard();

		AddInstrumentToKit();

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
