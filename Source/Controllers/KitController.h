/*
 * KitController.h
 *
 *  Created on: 19 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_KITCONTROLLER_H_
#define SOURCE_CONTROLLERS_KITCONTROLLER_H_


#include "../Widgets/Fader.h"
#include "../Widgets/InstrumentSelector.h"

#include <Source/Api/eXaDrums.h>
#include <Source/Api/KitCreator_api.h>

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/entry.h>
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


		std::vector<std::string> RetrieveKitsNames() const;
		std::string GetDataFolderLoc() const;
		void CreateKitsList();
		int GetCurrentKitId() const;
		void SaveKitConfig(int id) const { drumKit->SaveKitConfig(id); }
		void SaveKitConfig() const { drumKit->SaveKitConfig(GetCurrentKitId()); }
		void DeleteKit(const int& id);

		// Instruments
		int GetInstrumentVolume(int id) const { return drumKit->GetInstrumentVolume(id); };
		std::vector<std::string> RetrieveInstrumentsNames() const;

		// Signals

		void ChangeKit();
		void PlayDrums();

		// Faders
		void UpdateFaders();
		void SaveFaders() const;


		// Keyboard
		void ShowKeyboard();
		void HideKeyboard();

		// Dialogs & Windows
		void DeleteKitDialog();
		void ShowNewKitWindow();
		void HideNewKitWindow();
		void ShowInstrumentsListWindow();
		void HideInstrumentsListWindow();

		// Instruments
		void SetInstrumentVolume(Widgets::FaderPtr& fader) const;

		Glib::RefPtr<Gtk::Builder> builder;
		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;
		std::unique_ptr<eXaDrumsApi::KitCreator> kitCreator;

		// Buttons
		Gtk::Button* deleteKitButton;
		Gtk::Button* addDrumKitButton;
		Gtk::Button* kitNameCancel;
		Gtk::Button* KitNameOk;
		Gtk::Button* playButton;
		Gtk::Button* instrumentsListCancel;

		// Comboboxes
		Gtk::ComboBoxText* kitsList;

		// Dialogs
		Gtk::MessageDialog* deleteKitDialog;

		// Windows
		Gtk::Window* newKitNameWindow;
		Gtk::Window* instrumentsListWindow;

		// Faders
		Gtk::Button* saveFaders;
		std::vector<Widgets::FaderPtr> faders;

		// Instrument selectors
		std::vector<Widgets::InstrumentSelectorPtr> instrumentSelectors;

		// Boxes
		Gtk::Box* fadersList;
		Gtk::Box* instrumentsListBox;

		// Entries
		Gtk::Entry* kitNameEntry;
		Gtk::Entry* numInstrumentsEntry;

	};

} /* namespace Gui */

#endif /* SOURCE_CONTROLLERS_KITCONTROLLER_H_ */
