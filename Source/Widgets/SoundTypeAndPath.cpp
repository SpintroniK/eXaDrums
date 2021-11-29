/*
 * SoundTypeAndPath.cpp
 *
 *  Created on: 6 Dec 2016
 *      Author: jeremy
 */

#include "SoundTypeAndPath.h"

namespace Widgets
{

	SoundTypeAndPath::SoundTypeAndPath(const std::vector<std::string>& types, const std::string& dataFolder, Gtk::FileChooserDialog* soundChooser)
	: soundTypeLabel("Sound type: "), soundLabel("Sound: "), typesList(true), soundName(""), soundChange(Gtk::StockID("gtk-edit")), changingSound(false)
	{

		this->set_hexpand(true);

		// Configure and add sound type label
		soundTypeLabel.set_halign(Gtk::Align::ALIGN_CENTER);
		this->attach(soundTypeLabel, 0, 0, 1, 1);
		soundTypeLabel.show();

		this->set_halign(Gtk::Align::ALIGN_FILL);
		this->set_column_spacing(4);

		// Populate types combobox
		for(const auto& type : types)
		{
			typesList.append(type);
		}
		typesList.set_active(0);

		// Configure and add types to widget
		typesList.set_halign(Gtk::Align::ALIGN_CENTER);
		typesList.get_entry()->set_width_chars(12);
		this->attach_next_to(typesList, soundTypeLabel, Gtk::PositionType::POS_RIGHT, 1, 1);
		typesList.show();


		// Configure and add sound label
		soundLabel.set_halign(Gtk::Align::ALIGN_CENTER);
		this->attach_next_to(soundLabel, typesList, Gtk::PositionType::POS_RIGHT, 1, 1);
		soundLabel.show();

		// Populate sounds combobox

		this->attach_next_to(soundName, soundLabel, Gtk::PositionType::POS_RIGHT, 1, 1);
		soundName.show();

		this->attach_next_to(soundChange, soundName, Gtk::PositionType::POS_RIGHT, 1, 1);
		soundChange.set_halign(Gtk::Align::ALIGN_END);
		soundChange.set_hexpand(true);
		soundChange.show();

		soundChange.signal_clicked().connect([=, this] { ShowSoundChooser(soundChooser, dataFolder); });


		this->show();

		return;
	}


	void SoundTypeAndPath::ShowSoundChooser(Gtk::FileChooserDialog* soundChooser, const std::string& dataFolder)
	{
		this->changingSound = true;
		soundChooser->set_current_folder(dataFolder + "SoundBank/");
		soundChooser->show();
	}

} /* namespace Widgets */
