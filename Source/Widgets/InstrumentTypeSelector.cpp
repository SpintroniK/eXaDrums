/*
 * InstrumentSelector.cpp
 *
 *  Created on: 30 Nov 2016
 *      Author: jeremy
 */

#include "InstrumentTypeSelector.h"

namespace Widgets
{

	InstrumentTypeSelector::InstrumentTypeSelector() : label("Test"), selector()
	{


		this->set_halign(Gtk::Align::ALIGN_FILL);
		this->set_column_homogeneous(true);

		// Set label
		label.set_halign(Gtk::Align::ALIGN_CENTER);
		label.show();
		this->attach(label, 0, 0, 1, 1);


		// Set selector
		selector.show();
		this->attach_next_to(selector, label, Gtk::PositionType::POS_RIGHT, 1, 1);

		this->show();

		return;
	}

	InstrumentTypeSelector::~InstrumentTypeSelector()
	{

		return;
	}

} /* namespace Widgets */
