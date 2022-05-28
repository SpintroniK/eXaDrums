/*
 * SoundTypeAndPath.h
 *
 *  Created on: 6 Dec 2016
 *      Author: jeremy
 */

#ifndef SOURCE_WIDGETS_SOUNDTYPEANDPATH_H_
#define SOURCE_WIDGETS_SOUNDTYPEANDPATH_H_

#include <glibmm/refptr.h>

#include <gtkmm/adjustment.h>
#include <gtkmm/grid.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/label.h>
#include <gtkmm/filechooserdialog.h>
#include <gtkmm/button.h>

#include <vector>
#include <string>
#include <memory>

namespace Widgets
{

	class SoundTypeAndPath : public Gtk::Grid
	{

	public:

		SoundTypeAndPath(const std::vector<std::string>& types, const std::string& dataFolder, Gtk::FileChooserDialog* soundChooser);
		virtual ~SoundTypeAndPath() = default;


		void ShowSoundChooser(Gtk::FileChooserDialog* soundChooser, const std::string& dataFolder);

		void SetSoundType(const std::string& t) { typesList.set_active_text(t); }
		void SetSound(const std::string& t) { soundName.set_text(t); }
		void SetSoundChanged() { changingSound = false; }
		void SetMidiNote(uint8_t note) { midiNote.set_value(note); }

		std::string GetSoundType() const { return typesList.get_entry_text(); }
		std::string GetSound() const { return soundName.get_text(); }
		bool GetChangingSound() const noexcept { return changingSound; }
		auto GetMidiNote() const { return midiNote.get_value_as_int(); }

	private:

		Gtk::Label soundTypeLabel{"Sound type: "};
		Gtk::Label soundLabel{"Sound: "};
		Gtk::ComboBoxText typesList{true};
		Gtk::Label soundName{""};
		Gtk::Button soundChange{Gtk::StockID("gtk-edit")};
		Gtk::Label midiLabel{"Midi Note: "};
		Glib::RefPtr<Gtk::Adjustment> midiNoteAdj{Gtk::Adjustment::create(0, 0, 127)};
		Gtk::SpinButton midiNote{midiNoteAdj};

		bool changingSound{false};

	};

	typedef std::shared_ptr<SoundTypeAndPath> SoundTypeAndPathPtr;

} /* namespace Widgets */

#endif /* SOURCE_WIDGETS_SOUNDTYPEANDPATH_H_ */
