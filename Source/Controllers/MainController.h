/*
 * Controller.h
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_MAINCONTROLLER_H_
#define SOURCE_CONTROLLERS_MAINCONTROLLER_H_

#include "../Fader/Fader.h"

#include "MetronomeController.h"

#include <Source/Api/eXaDrums.h>

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/dialog.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/box.h>
#include <gtkmm/window.h>
#include <gtkmm/entry.h>

#include <string>
#include <memory>
#include <functional>
#include <algorithm>

#include <cstdlib>

using namespace eXaDrumsApi;

namespace Gui
{

	class MainController
	{

	public:

		MainController(Glib::RefPtr<Gtk::Builder>& builder, std::string const& mainFolder);
		virtual ~MainController();

	private:

		// Signals methods

		// Kits
		void ChangeKit();
		void PlayDrums();

		// Instruments
		void SetInstrumentVolume(FaderPtr& fader) const;

		// Dialogs
		void ShowAboutDialog();
		void HideAboutDialog(int responseId);
		void DeleteKitDialog();
		void ShowNewKitDialog();
		void HideNewKitDialog();

		// Keyboard
		void ShowKeyboard();
		void HideKeyboard();

		// Windows

		// Faders
		void UpdateFaders();
		void SaveFaders() const;

		// Kit
		std::vector<std::string> RetrieveKitsNames() const;
		int GetCurrentKitId() const;
		void SaveKitConfig(int id) const { drumKit->SaveKitConfig(id); };
		void SaveKitConfig() const { drumKit->SaveKitConfig(GetCurrentKitId()); };
		void DeleteKit(const int& id);
		void CreateKitsList();

		// Instruments
		int GetInstrumentVolume(int id) const { return drumKit->GetInstrumentVolume(id); };
		std::vector<std::string> RetrieveInstrumentsNames() const;

		std::string mainFolder;

		std::shared_ptr<eXaDrums> drumKit;
		Glib::RefPtr<Gtk::Builder> builder;

		// Controllers
		std::unique_ptr<MetronomeController> metronomeController;

		// Buttons
		Gtk::Button* aboutButton;
		Gtk::Button* playButton;
		Gtk::Button* deleteKitButton;
		Gtk::Button* rhythmCoachPrefButton;
		Gtk::Button* addDrumKitButton;
		Gtk::Button* kitNameCancel;

		// Comboboxes
		Gtk::ComboBoxText* kitsList;

		// Boxes
		Gtk::Box* fadersList;

		// Dialogs
		Gtk::AboutDialog* aboutDialog;
		Gtk::MessageDialog* deleteKitDialog;
		Gtk::Dialog* newKitNameDialog;

		// Windows

		// Faders
		Gtk::Button* saveFaders;
		std::vector<FaderPtr> faders;

		// Entries
		Gtk::Entry* kitNameEntry;

		// Scales

	};

} /* namespace Gui */

#endif /* SOURCE_CONTROLLERS_MAINCONTROLLER_H_ */
