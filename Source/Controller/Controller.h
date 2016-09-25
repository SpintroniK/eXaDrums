/*
 * Controller.h
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLER_CONTROLLER_H_
#define SOURCE_CONTROLLER_CONTROLLER_H_

#include "../Fader/Fader.h"

#include <Source/Api/eXaDrums.h>

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/box.h>
#include <gtkmm/scale.h>

#include <string>
#include <memory>
#include <functional>
#include <algorithm>

using namespace eXaDrumsApi;

namespace Gui
{

	class Controller
	{

	public:

		Controller(Glib::RefPtr<Gtk::Builder>& builder, std::string const& mainFolder);
		virtual ~Controller();

	private:

		// Signals methods
		// Kits
		void ChangeKit();
		void PlayDrums();
		// Instruments
		void SetInstrumentVolume(FaderPtr& fader) const;
		// Metronome
		void EnableClick() const;
		void ChangeTempo() const;
		// Dialogs
		void ShowAboutDialog();
		void HideAboutDialog(int responseId);
		void DeleteKitDialog();
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

		std::unique_ptr<eXaDrums> drumKit;
		Glib::RefPtr<Gtk::Builder> builder;

		// Buttons
		Gtk::Button* aboutButton;
		Gtk::Button* playButton;
		Gtk::Button* deleteKitButton;
		Gtk::CheckButton* enableClickButton;

		// Comboboxes
		Gtk::ComboBoxText* kitsList;

		// Boxes
		Gtk::Box* fadersList;

		// Dialogs
		Gtk::AboutDialog* aboutDialog;
		Gtk::MessageDialog* deleteKitDialog;

		// Faders
		Gtk::Button* saveFaders;
		std::vector<FaderPtr> faders;

		// Scales
		Gtk::Scale* clickVolumeScale;

	};

} /* namespace Gui */

#endif /* SOURCE_CONTROLLER_CONTROLLER_H_ */
