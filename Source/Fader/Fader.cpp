/*
 * Fader.cpp
 *
 *  Created on: 21 Aug 2016
 *      Author: jeremy
 */

#include "Fader.h"

namespace Gui
{

	Fader::Fader(const std::string& name, int instrumentId, int vol)
	: instrument(instrumentId), volume(vol), label(name+" "), volScale(Gtk::Orientation::ORIENTATION_HORIZONTAL)
	{

		this->set_halign(Gtk::Align::ALIGN_START);
		this->set_column_homogeneous(true);

		// Set title
		label.set_halign(Gtk::Align::ALIGN_START);
		label.show();
		this->attach(label, 0, 0, 1, 1);

		// Set scale parameters
		volScale.set_range(0, 100);
		volScale.set_digits(0);
		volScale.set_value_pos(Gtk::PositionType::POS_LEFT);
		volScale.set_halign(Gtk::Align::ALIGN_CENTER);

		volScale.set_value(vol);
		volScale.set_size_request(148, 10);

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
