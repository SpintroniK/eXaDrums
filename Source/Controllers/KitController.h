/*
 * KitController.h
 *
 *  Created on: 19 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_KITCONTROLLER_H_
#define SOURCE_CONTROLLERS_KITCONTROLLER_H_


#include "../Widgets/Fader.h"
#include "../Widgets/TriggerIdAndLocation.h"
#include "../Widgets/SoundTypeAndPath.h"
#include "../Widgets/InstrumentSelector.h"

#include <Source/Api/eXaDrums.h>
#include <Source/Api/KitCreator_api.h>

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>

#include <vector>
#include <string>
#include <memory>

namespace Controllers
{

	class KitController
	{

	public:

		KitController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit);
		virtual ~KitController();

	private:


		void CreateKitsList();
		int GetCurrentKitId() const;
		void SaveKitConfig(int id) const { drumKit->SaveKitConfig(id); }
		void SaveKitConfig() const { drumKit->SaveKitConfig(GetCurrentKitId()); }
		void DeleteKit(const int& id);
		void KitAdded();

		// Instruments
		int GetInstrumentVolume(int id) const { return drumKit->GetInstrumentVolume(id); };
		void AddInstrumentToKit();

		// Signals
		void ChangeKit();
		void PlayDrums();
		void ValidateKitData();
		void ChangeInstrumentType();
		void ValidateInstrumentData();
		void CancelInstrumentModif();
		void ShowInstrumentSeclectWindow();

		// Faders
		void UpdateFaders();
		void SaveFaders() const;


		// Keyboard
		void ShowKeyboard();
		void HideKeyboard();

		// Dialogs & Windows
		void DeleteKitDialog();
		void AddNewKitWindow();
		void AddNewKit();

		// Instruments
		void SetInstrumentVolume(Widgets::FaderPtr& fader) const;

		Glib::RefPtr<Gtk::Builder> builder;
		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;
		std::unique_ptr<eXaDrumsApi::KitCreator> kitCreator;

		// Buttons
		Gtk::Button* deleteKitButton;
		Gtk::Button* addDrumKitButton;
		Gtk::Button* playButton;
		Gtk::Button* kitPreferencesButton;

		// Comboboxes
		Gtk::ComboBoxText* kitsList;

		// Faders
		Gtk::Button* saveFaders;
		std::vector<Widgets::FaderPtr> faders;
		Gtk::Box* fadersList;

		// Kit creation
		std::vector<Widgets::TriggerIdAndLocationPtr> triggersIdsAndLocations;
		std::vector<Widgets::SoundTypeAndPathPtr> soundsTypesAndPaths;
		std::vector<Widgets::InstrumentSelectorPtr> instrumentsSelectors;


		// Windows
		Gtk::Window* newKitWindow;
		Gtk::Window* instrumentConfigWindow;
		Gtk::Window* instrumentSeclectWindow;


		// Class variables
		int numInstrumentsToCreate;


	};

} /* namespace Gui */

#endif /* SOURCE_CONTROLLERS_KITCONTROLLER_H_ */
