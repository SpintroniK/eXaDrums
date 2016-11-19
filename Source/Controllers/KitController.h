/*
 * KitController.h
 *
 *  Created on: 19 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_KITCONTROLLER_H_
#define SOURCE_CONTROLLERS_KITCONTROLLER_H_


#include "../Fader/Fader.h"

#include <Source/Api/eXaDrums.h>

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/dialog.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/entry.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/box.h>

#include <functional>
#include <algorithm>


namespace Gui
{

	class KitController
	{

	public:

		KitController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit);
		virtual ~KitController();

	private:


		std::vector<std::string> RetrieveKitsNames() const;
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

		// Dialogs
		void DeleteKitDialog();
		void ShowNewKitDialog();
		void HideNewKitDialog();

		// Instruments
		void SetInstrumentVolume(FaderPtr& fader) const;

		Glib::RefPtr<Gtk::Builder> builder;
		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;

		// Buttons
		Gtk::Button* deleteKitButton;
		Gtk::Button* addDrumKitButton;
		Gtk::Button* kitNameCancel;
		Gtk::Button* playButton;

		// Comboboxes
		Gtk::ComboBoxText* kitsList;

		// Dialogs
		Gtk::MessageDialog* deleteKitDialog;
		Gtk::Dialog* newKitNameDialog;

		// Faders
		Gtk::Button* saveFaders;
		std::vector<FaderPtr> faders;

		// Boxes
		Gtk::Box* fadersList;

		// Entries
		Gtk::Entry* kitNameEntry;

	};

} /* namespace Gui */

#endif /* SOURCE_CONTROLLERS_KITCONTROLLER_H_ */
