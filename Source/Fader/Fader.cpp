/*
 * Fader.cpp
 *
 *  Created on: 21 Aug 2016
 *      Author: jeremy
 */

#include "Fader.h"

namespace Gui
{

	Fader::Fader(const std::string& name, int vol) : label(name+" "), volume(vol)
	{

		this->set_border_width(2);
		this->set_halign(Gtk::Align::ALIGN_END);
		this->set_hexpand(true);

		// Set title
		label.show();
		this->attach(label, 0, 0, 1, 1);

		// Set scale
		volScale = Gtk::Scale(Gtk::Orientation::ORIENTATION_HORIZONTAL);
		volScale.set_range(0, 100);
		volScale.set_digits(0);
		volScale.set_value_pos(Gtk::PositionType::POS_LEFT);
		volScale.set_halign(Gtk::Align::ALIGN_END);

		volScale.set_value(vol);
		volScale.set_size_request(200, 10);

		volScale.show();
		this->attach_next_to(volScale, label, Gtk::PositionType::POS_RIGHT, 1, 1);

		this->show();

		return;
	}

	Fader::~Fader()
	{


		return;
	}

} /* namespace Gui */
