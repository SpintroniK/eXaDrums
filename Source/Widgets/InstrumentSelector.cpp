/*
 * InstrumentSelector.cpp
 *
 *  Created on: 30 Nov 2016
 *      Author: jeremy
 */

#include "InstrumentSelector.h"

namespace Widgets
{

	InstrumentSelector::InstrumentSelector() : label("Test")
	{


		this->set_halign(Gtk::Align::ALIGN_START);
		this->set_column_homogeneous(true);
		// Set title
		label.set_halign(Gtk::Align::ALIGN_START);
		label.show();
		this->attach(label, 0, 0, 1, 1);

		this->show();

		return;
	}

	InstrumentSelector::~InstrumentSelector()
	{

		return;
	}

} /* namespace Widgets */
