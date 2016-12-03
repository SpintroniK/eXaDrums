/*
 * InstrumentSelector.cpp
 *
 *  Created on: 30 Nov 2016
 *      Author: jeremy
 */

#include "InstrumentTypeSelector.h"

#include <algorithm>

namespace Widgets
{

	InstrumentTypeSelector::InstrumentTypeSelector(const std::string& instrumentName, const std::vector<std::string>& types)
	: label(instrumentName), selector(true)
	{


		this->set_halign(Gtk::Align::ALIGN_FILL);
		this->set_column_homogeneous(true);

		// Set label
		label.set_halign(Gtk::Align::ALIGN_CENTER);
		label.show();
		this->attach(label, 0, 0, 1, 1);


		// Set selector
		// Populate
		std::for_each(types.cbegin(), types.cend(), [&](const std::string& s) { selector.append(s); });

		// Set parameters
		selector.get_entry()->set_can_focus(false);
		selector.set_active(0);
		selector.show();
		this->attach_next_to(selector, label, Gtk::PositionType::POS_RIGHT, 1, 1);

		// Show widget
		this->show();

		return;
	}

	InstrumentTypeSelector::~InstrumentTypeSelector()
	{

		return;
	}



} /* namespace Widgets */
