/*
 * Fader.cpp
 *
 *  Created on: 21 Aug 2016
 *      Author: jeremy
 */

#include "Fader.h"

namespace Widgets
{

	Fader::Fader(const std::string& name, int instrumentId, int vol)
	: instrument(instrumentId), volume(vol), label(name+" "), volScale(Gtk::Orientation::ORIENTATION_HORIZONTAL)
	{

		this->set_halign(Gtk::Align::ALIGN_FILL);
		this->set_hexpand();

		// Set title
		label.set_halign(Gtk::Align::ALIGN_START);
		label.set_justify(Gtk::Justification::JUSTIFY_LEFT);
		label.set_size_request(72, -1);
		label.show();
		this->attach(label, 0, 0, 1, 1);

		// Set scale parameters
		volScale.set_range(0, 100);
		volScale.set_digits(0);
		volScale.set_value_pos(Gtk::PositionType::POS_RIGHT);
		volScale.set_halign(Gtk::Align::ALIGN_FILL);
		volScale.set_hexpand();
		volScale.set_size_request(-1, 16);

		volScale.set_value(vol);

		volScale.show();
		this->attach_next_to(volScale, label, Gtk::PositionType::POS_RIGHT, 1, 1);

		this->show();

		return;
	}


} /* namespace Gui */
