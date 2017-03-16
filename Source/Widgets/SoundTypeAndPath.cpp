/*
 * SoundTypeAndPath.cpp
 *
 *  Created on: 6 Dec 2016
 *      Author: jeremy
 */

#include "SoundTypeAndPath.h"

namespace Widgets
{

	SoundTypeAndPath::SoundTypeAndPath(const std::vector<std::string>& types, const std::vector<std::string>& sounds)
	: soundTypeLabel("Sound type: "), soundLabel("Sound: "), typesList(true), soundsList(true)
	{


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
		for(const auto& sound : sounds)
		{
			soundsList.append(sound);
		}
		soundsList.set_active(0);

		// Configure and add sounds to widget
		soundsList.set_halign(Gtk::Align::ALIGN_CENTER);
		soundsList.get_entry()->set_width_chars(24);
		this->attach_next_to(soundsList, soundLabel, Gtk::PositionType::POS_RIGHT, 1, 1);
		soundsList.show();


		this->show();

		return;
	}


} /* namespace Widgets */
