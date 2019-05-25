/*
 * KitController.cpp
 *
 *  Created on: 19 Nov 2016
 *      Author: jeremy
 */

#include "../Util/ErrorHandler.h"
#include "KitController.h"

#include <gtkmm/entry.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/filechooserdialog.h>

#include <functional>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iostream>

using namespace eXaDrumsApi;
using namespace Widgets;
using namespace Util;
using namespace Errors;

namespace Controllers
{

	KitController::KitController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrums>& drumKit, bool isRoot)
	: builder(builder), drumKit(drumKit), isRoot(isRoot)
	{

		numInstrumentsToCreate = 0;
		instrumentToModify = -1;

		std::string dataFolder(drumKit->GetDataLocation());

		this->kitCreator = std::make_unique<KitCreator>(dataFolder.c_str());


		Gtk::Button* instrumentConfigOkay = nullptr;
		Gtk::Button* instrumentConfigCancel = nullptr;
		Gtk::Button* instrumentSelectSave = nullptr;
		Gtk::Button* instrumentSelectCancel = nullptr;
		Gtk::Button* kitNameCancel = nullptr;
		Gtk::Button* KitNameOk = nullptr;
		Gtk::Button* soundChooserCancel = nullptr;
		Gtk::Button* soundChooserOkay = nullptr;
		Gtk::Button* recorderCancel = nullptr;
		Gtk::Button* recorderSave = nullptr;

		Gtk::FileChooserDialog* soundChooser = nullptr;

		Gtk::ComboBoxText* instrumentConfig_Type = nullptr;


		// Get all widgets
		{
			// Buttons
			builder->get_widget("PlayButton", playButton);
			builder->get_widget("RecordButton", recordButton);
			builder->get_widget("DeleteDrumKitButton", deleteKitButton);
			builder->get_widget("AddDrumKitButton", addDrumKitButton);
			builder->get_widget("KitPreferencesButton", kitPreferencesButton);
			builder->get_widget("InstrumentConfigOkay", instrumentConfigOkay);
			builder->get_widget("InstrumentConfigCancel", instrumentConfigCancel);
			builder->get_widget("ISSave", instrumentSelectSave);
			builder->get_widget("ISCancel", instrumentSelectCancel);
			builder->get_widget("KitNameCancel", kitNameCancel);
			builder->get_widget("KitNameOk", KitNameOk);
			builder->get_widget("SoundChooserCancel", soundChooserCancel);
			builder->get_widget("SoundChooserOkay", soundChooserOkay);
			builder->get_widget("RecorderCancel", recorderCancel);
			builder->get_widget("RecorderSave", recorderSave);

			builder->get_widget("SoundChooser", soundChooser);


			// Lists
			builder->get_widget("KitsList", kitsList);

			// Faders' box
			builder->get_widget("FadersSaveButton", saveFaders);
			builder->get_widget("FadersList", fadersList);

			// Virtual kit
			builder->get_widget("VirtualPadsList", virtualPadsList);

			// Comboboxes
			builder->get_widget("InstrumentConfig_Type", instrumentConfig_Type);


			// Windows
			builder->get_widget("NewKitNameWindow", newKitWindow);
			builder->get_widget("InstrumentConfigWindow", instrumentConfigWindow);
			builder->get_widget("InstrumentSeclectWindow", instrumentSeclectWindow);
			builder->get_widget("RecorderWindow", recorderWindow);
			builder->get_widget("VirtualPadWindow", virtualPadWindow);

		}

		// Populate Kits list
		CreateKitsList();

		// Add faders
		UpdateFaders();
		saveFaders->set_sensitive(false);

		// Create virtual kit
		UpdateVirtualKit();

		// Load current kit
		drumKit->SelectKit(GetCurrentKitId());

		// Connect signals
		{
			playButton->signal_clicked().connect([&] { PlayDrums(); });
			recordButton->signal_toggled().connect([&] { EnableRecording(); });
			saveFaders->signal_clicked().connect([&] { SaveFaders(); });
			deleteKitButton->signal_clicked().connect([&] { DeleteKitDialog(); });
			addDrumKitButton->signal_clicked().connect([&] { AddNewKitWindow(); });
			kitPreferencesButton->signal_clicked().connect([&] { ShowInstrumentSelectWindow(); });
			instrumentConfigOkay->signal_clicked().connect([&] { ValidateInstrumentData(); });
			instrumentConfigCancel->signal_clicked().connect([&] { CancelInstrumentModif(); });
			instrumentSelectSave->signal_clicked().connect([&] { SaveKitPreferences(); });
			instrumentSelectCancel->signal_clicked().connect([&] { instrumentSeclectWindow->hide(); });
			kitNameCancel->signal_clicked().connect([&] { newKitWindow->hide(); });
			KitNameOk->signal_clicked().connect([&] { ValidateKitData(); });
			soundChooserCancel->signal_clicked().connect([=] { soundChooser->hide(); });
			soundChooserOkay->signal_clicked().connect([&] { ChangeInstrumentSound(); });
			recorderCancel->signal_clicked().connect([&] { recorderWindow->hide(); });
			recorderSave->signal_clicked().connect([&] { RecorderExport(); });

			// Comboboxes
			instrumentConfig_Type->signal_changed().connect([&] { ChangeInstrumentType(); });

			// Kits list
			kitsList->signal_changed().connect([&] { ChangeKit(); });

			// Windows
			virtualPadWindow->signal_key_press_event().connect([&](GdkEventKey* e)
			{
				for(const auto& v : virtualPads)
				{
					v->PlaySound(e->keyval);
				}

				return false;
			}, false);

		}

		return;
	}

	KitController::~KitController()
	{

		// Delete all pointers (dialogs and windows)
		delete newKitWindow;
		delete instrumentConfigWindow;
		delete instrumentSeclectWindow;
		delete recorderWindow;

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
		switch(answer)
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
			int activeKit = (id == 0)? 1 : 0;
			kitsList->set_active(activeKit);

			// Delete kit
			try
			{
				drumKit->DeleteKit(id);
			}
			catch(const Exception& e)
			{
				errorDialog(e);
				return;
			}

			// Remove kit from list
			kitsList->remove_text(id);

			// Set new kit
			ChangeKit();

		}
		else
		{
			Errors::errorDialog({"Cannot delete drum kit.", errorType::error_type_error});
		}

		return;
	}

	void KitController::AddNewKit()
	{

		if(drumKit->IsStarted())
		{
			try
			{
				PlayDrums();
			}
			catch(const Exception& e)
			{
				errorDialog(e);
				return;
			}
		}


		// Retrieve kits names
		std::vector<std::string> oldKitsNames = drumKit->GetKitsNames();

		// Reload kits
		drumKit->ReloadKits();

		// Retrieve kits names
		std::vector<std::string> newkitsNames = drumKit->GetKitsNames();

		auto newOldKit = std::mismatch(oldKitsNames.cbegin(), oldKitsNames.cend(), newkitsNames.cbegin());

		// Get new kit's name and position in the list
		std::string newKitName = *(newOldKit.second);
		int pos = std::distance(newkitsNames.cbegin(), newOldKit.second);

		// Insert new kit into list, and activate it
		kitsList->insert(pos, newKitName);
		kitsList->set_active(pos);

		// Set new kit
		ChangeKit();

		return;
	}

	void KitController::KitAdded()
	{
		Errors::errorDialog({"A new drum kit has been added.", errorType::error_type_other});
		return;
	}

	void KitController::EnableRecording()
	{
		bool isRecording = this->recordButton->get_active();

		drumKit->EnableRecording(isRecording);

		if(!isRecording)
		{
			recorderWindow->show();
		}
	}

	void KitController::RecorderExport()
	{
		std::string fileName = recorderWindow->get_filename();

		//TODO: need to check for errors.
		drumKit->RecorderExport(fileName);

		recorderWindow->hide();
	}

	void KitController::PlayDrums()
	{

		if(drumKit->IsStarted())
		{
			this->playButton->set_property("label", Gtk::StockID("gtk-media-play"));

			if(drumKit->IsSensorVirtual())
			{
				virtualPadWindow->hide();
			}


			drumKit->Stop();
		}
		else
		{
			this->playButton->set_property("label", Gtk::StockID("gtk-media-stop"));

			if(drumKit->IsSensorVirtual())
			{
				virtualPadWindow->show();
			}

			if(drumKit->IsSensorSpi() && !isRoot)
			{
				Errors::errorDialog({"Using SPI sensors may require superuser privileges.", errorType::error_type_other});
			}

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


		// Load new kit or exit if it doesn't exist
		try
		{
			drumKit->SelectKit(GetCurrentKitId());
		}
		catch(const Exception& e)
		{
			Errors::errorDialog(e);
			return;
		}

		// Update faders
		this->UpdateFaders();
		saveFaders->set_sensitive(false);

		// Update virtual kit
		UpdateVirtualKit();

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

			faders.emplace_back(std::move(fader));
		}

		// Add all faders to GUI
		std::for_each(faders.cbegin(), faders.cend(), [&](const FaderPtr& f){ this->fadersList->add(*f); });

		// Connect faders signals
		for(FaderPtr& fader : faders)
		{
			fader->GetScale().signal_value_changed().connect([&] { SetInstrumentVolume(fader); });
		}

		return;
	}

	void KitController::UpdateVirtualKit()
	{
		// Remove current virtual pads
		std::for_each(virtualPads.begin(), virtualPads.end(), [](VirtualPadPtr& vpad) { vpad.reset(); });
		virtualPads.clear();

		auto const instNames = drumKit->GetInstrumentsNames();
		auto const max = static_cast<short>(std::pow(2, drumKit->GetSensorsResolution())/2 - 1);

		// Add new virtual pads
		for(size_t i = 0; i < instNames.size(); i++)
		{
			auto trigsIds = drumKit->GetInstrumentTriggersIds(i);
			std::vector<std::function<void()>> soundTriggers(trigsIds.size());

			std::transform(trigsIds.begin(), trigsIds.end(), soundTriggers.begin(), [&, max] (int trigId)
			{
				return [&, trigId, max] () -> void { drumKit->SetTriggerSensorValue(trigId, 0, max); };
			});

			VirtualPadPtr vpad(new VirtualPad(instNames[i], std::move(soundTriggers)));
			virtualPads.emplace_back(std::move(vpad));
		}

		std::for_each(virtualPads.begin(), virtualPads.end(), [&](const VirtualPadPtr& vpad) { this->virtualPadsList->add(*vpad); });

	}


	void KitController::AddNewKitWindow()
	{

		newKitWindow->show();
		ShowKeyboard();

		return;
	}

	void KitController::ModifyInstrument(int i)
	{

		// Get instrument name
		std::vector<std::string> instrumentsNames = kitCreator->GetInstrumentsNames();
		std::string instrumentName = instrumentsNames[i];

		// Get instrument type
		std::string instrumentType = kitCreator->GetInstrumentType(i);

		// Get instrument triggers
		std::vector<int> instrumentTriggersIds = kitCreator->GetInstrumentTriggersIds(i);
		std::vector<std::string> instrumentLocations = kitCreator->GetInstrumentTriggersLocations(i);

		// Get instrument sounds
		std::vector<std::string> instrumentSoundsTypes = kitCreator->GetInstrumentSoundsTypes(i);
		std::vector<std::string> instrumentSoundsLocs = kitCreator->GetInstrumentSoundsLocs(i);

		// Get widgets
		Gtk::ComboBoxText* instrumentConfig_Type = nullptr;
		Gtk::Entry* instrumentConfig_Name = nullptr;

		builder->get_widget("InstrumentConfig_Type", instrumentConfig_Type);
		builder->get_widget("InstrumentConfig_Name", instrumentConfig_Name);

		// Set widgets values

		// Set instrument name
		instrumentConfig_Name->set_text(instrumentName);

		// Create vector of instruments types
		std::vector<std::string> instrumentTypes = kitCreator->GetInstrumentsTypes();

		// Populate instrument config window
		{

			std::string text = instrumentConfig_Type->get_active_text();

			// Populate only if not already done
			if(text.empty())
			{

				for(std::size_t i = 0; i < instrumentTypes.size(); i++)
				{
					instrumentConfig_Type->insert(i, instrumentTypes[i]);
				}

				// Set default instrument and call ChangeInstrumentType() method
				instrumentConfig_Type->set_active(0);
			}

		}

		instrumentConfig_Type->set_active_text(instrumentType);

		for(std::size_t i = 0; i < triggersIdsAndLocations.size(); i++)
		{
			auto& t = triggersIdsAndLocations[i];

			t->SetTriggerId(instrumentTriggersIds[i]);
			t->SetTriggerLoc(instrumentLocations[i]);
		}

		for(std::size_t i = 0; i < soundsTypesAndPaths.size(); i++)
		{
			auto& s = soundsTypesAndPaths[i];

			s->SetSoundType(instrumentSoundsTypes[i]);
			s->SetSound(instrumentSoundsLocs[i]);
		}

		// Keep track of the instrument id
		instrumentToModify = i;

		// Show window
		instrumentConfigWindow->show();

		return;
	}

	void KitController::RemoveInstrument(int i)
	{

		if(instrumentsSelectors.size() > 1)
		{

			// Load current kit into the kit creator for modifications
			std::string kitLocation = drumKit->GetKitDataFileName();
			kitCreator->CreateFromModel(kitLocation.c_str());

			kitCreator->RemoveInstrument(i);

			// Remove instrument from GUI
			if(i >= 0 && i < (int)instrumentsSelectors.size())
			{
				instrumentsSelectors[i].reset();
				instrumentsSelectors.erase(instrumentsSelectors.begin() + i);
			}
		}

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
				if(text.empty())
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

			kitCreator->CreateNewKit();
			this->numInstrumentsToCreate = 0;

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
		// std::vector<std::string> soundsFiles = kitCreator->GetSoundsFiles();

		// Create tirggers ids and locations
		{

			std::vector<int> triggersIds = kitCreator->GetTriggersIds();

			std::for_each(triggersIdsAndLocations.begin(), triggersIdsAndLocations.end(), [](TriggerIdAndLocationPtr& t) { t.reset(); });
			triggersIdsAndLocations.clear();

			for(std::size_t i = 0; i < triggersLocations.size(); i++)
			{
				triggersIdsAndLocations.push_back(std::make_shared<TriggerIdAndLocation>(triggersLocations, triggersIds));
			}

			std::for_each(triggersIdsAndLocations.cbegin(), triggersIdsAndLocations.cend(), [&](const TriggerIdAndLocationPtr& t){ instrumentConfig_TriggersBox->add(*t); });
		}

		// Create sounds types and paths
		{

			std::for_each(soundsTypesAndPaths.begin(), soundsTypesAndPaths.end(), [](SoundTypeAndPathPtr& t) { t.reset(); });
			soundsTypesAndPaths.clear();

			Gtk::FileChooserDialog* soundChooser = nullptr;
			this->builder->get_widget("SoundChooser", soundChooser);

			for(std::size_t i = 0; i < soundsTypes.size(); i++)
			{
				soundsTypesAndPaths.push_back(std::make_shared<SoundTypeAndPath>(soundsTypes, drumKit->GetDataLocation(), soundChooser));
			}

			// Add sounds types to window
			std::for_each(soundsTypesAndPaths.cbegin(), soundsTypesAndPaths.cend(), [&](const SoundTypeAndPathPtr& t){ instrumentConfig_SoundsBox->add(*t); });

		}

		return;
	}

	void KitController::CancelInstrumentModif()
	{

		if(this->numInstrumentsToCreate != 0)
		{
			kitCreator->CreateNewKit();
		}

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

		// Check if we are modifying or adding an instrument
		bool isModif = (numInstrumentsToCreate == 0);

		if(isModif)
		{

			// Get instrument id
			int id = instrumentToModify;

			// Modify instrument
			{
				// Retrieve triggers ids and locations
				std::vector<std::pair<int, std::string>> trigIdsAndLocs;
				for(const auto& t : triggersIdsAndLocations)
				{
					trigIdsAndLocs.push_back({t->GetTriggerId(), t->GetTriggerLoc()});
				}

				// Retrieve sounds types and locations
				std::vector<std::pair<std::string, std::string>> sndTypesAndLocs;
				for(const auto& s : soundsTypesAndPaths)
				{
					sndTypesAndLocs.push_back({s->GetSoundType(), s->GetSound()});
				}

				// Change instrument name
				kitCreator->SetInstrumentName(id, instrumentName.c_str());

				// Change instrument type
				kitCreator->SetInstrumentType(id, instrumentType.c_str());

				// Modify triggers ids and locations
				kitCreator->SetInstrumentTriggersIdsAndLocs(id, trigIdsAndLocs);

				// Modify sounds
				kitCreator->SetInstrumentSoundsTypesAndLocs(id, sndTypesAndLocs);


				// Change instrument name on the kit config window
				instrumentsSelectors[id]->SetInstrumentName(instrumentName);

				instrumentConfigWindow->hide();

				// Save kit
				//kitCreator->SaveKit();

			}

			// We're done, so we disable instrument modification
			instrumentToModify = -1;
		}
		else
		{

			// Create instrument
			kitCreator->CreateNewInstrument();
			kitCreator->SetInstrumentVolume(1.0f);
			try
			{
				kitCreator->SetInstrumentName(instrumentName.c_str());
			}
			catch(const Exception& e)
			{
				kitCreator->RemoveLastInstrument();
				Errors::errorDialog(e);
				return;
			}
			
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
		}

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

			Gtk::MessageDialog d("Kit's name must be at least 3 characters long.", false, Gtk::MessageType::MESSAGE_WARNING, Gtk::ButtonsType::BUTTONS_CLOSE);
			d.set_title("Error");
			d.run();

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

		ChangeInstrumentType();
		AddInstrumentToKit();

		return;
	}

	void KitController::ShowInstrumentSelectWindow()
	{


		Gtk::Entry* kitNameEntry = nullptr;
		Gtk::Box* instrumentsBox = nullptr;

		builder->get_widget("ISKitName", kitNameEntry);
		builder->get_widget("ISListBox", instrumentsBox);

		kitNameEntry->set_text(kitsList->get_active_text());

		// Load current kit into the kit creator for modifications
		std::string kitLocation = drumKit->GetKitDataFileName();
		kitCreator->CreateFromModel(kitLocation.c_str());

		// Get kit's instruments
		std::vector<std::string> instrumentsNames = kitCreator->GetInstrumentsNames();

		// Reset instruments selectors
		std::for_each(instrumentsSelectors.begin(), instrumentsSelectors.end(), [](InstrumentSelectorPtr& i) { i.reset(); });
		instrumentsSelectors.clear();

		// Create new instruments selectors
		std::transform(instrumentsNames.cbegin(), instrumentsNames.cend(), std::back_inserter(instrumentsSelectors), [](const std::string& name) { return std::make_shared<InstrumentSelector>(name); });

		// Add selectors to window
		std::for_each(instrumentsSelectors.cbegin(), instrumentsSelectors.cend(), [&instrumentsBox](const InstrumentSelectorPtr& i) { instrumentsBox->add(*i); });

		// Connect signals
		for(std::size_t i = 0; i < instrumentsSelectors.size(); i++)
		{
			auto& is = instrumentsSelectors[i];
			is->GetPreferencesButton().signal_clicked().connect([=] { ModifyInstrument(i); });
			is->GetDeleteButton().signal_clicked().connect([=] { RemoveInstrument(i); });
		}

		instrumentSeclectWindow->show();

		return;
	}

	void KitController::SaveKitPreferences()
	{

		// Get kit name
		Gtk::Entry* kitName = nullptr;
		builder->get_widget("ISKitName", kitName);
		std::string name = kitName->get_text();

		// Set kit name
		kitCreator->SetKitName(name.c_str());

		// Save kit parameters to file
		kitCreator->SaveKit();

		// Reload kits
		{

			bool isStarted = drumKit->IsStarted();
			// Stop  module
			if(isStarted)
			{
				PlayDrums();
			}

			// Reload kits
			drumKit->ReloadKits();


			//XXX Doesn't update the active entry when there's only one kit
			if(name != kitsList->get_active_text())
			{
				kitsList->get_active()->set_value(0, name);

				if(drumKit->GetKitsNames().size() > 1 && kitsList->get_active_row_number() == 0)
				{
					kitsList->set_active(1);
				}
				else
				{
					kitsList->set_active(0);
				}

				kitsList->set_active_text(name);
			}

			// Set active kit
			ChangeKit();

			if(isStarted)
			{
				PlayDrums();
			}

		}

		// Close window
		instrumentSeclectWindow->hide();

		return;
	}

	void KitController::ChangeInstrumentSound()
	{

		// Retrieve soundChooser
		Gtk::FileChooserDialog* soundChooser = nullptr;
		this->builder->get_widget("SoundChooser", soundChooser);

		// Get new sound's path
		std::string folder = soundChooser->get_filename();

		// Find which sound's been modified
		auto itSound = std::find_if(soundsTypesAndPaths.begin(), soundsTypesAndPaths.end(), [](auto& s) { return s->GetChangingSound(); });

		if(itSound == soundsTypesAndPaths.cend())
		{
			return;
		}

		// Get path relative to the sound bank's folder
		std::string soundLoc;
		{

			std::string parentFolder("SoundBank");
			auto pos = folder.find(parentFolder);

			// If the path is invalid
			if(pos == std::string::npos)
			{
				// Close sound chooser
				soundChooser->hide();
				return;
			}

			soundLoc = folder.substr(pos + parentFolder.size() + 1);

		}

		// Set new sound
		itSound->get()->SetSound(soundLoc);
		itSound->get()->SetSoundChanged();

		// Close sound chooser
		soundChooser->hide();

		return;

	}

	void KitController::ShowKeyboard()
	{
		HideKeyboard();
		//std::system("onboard --size=800x160 -x 0 -y 280 &");
		return;
	}

	void KitController::HideKeyboard()
	{

		//std::system("killall onboard");
		return;
	}



} /* namespace Gui */
