/*
 * InstrumentSelector.cpp
 *
 *  Created on: 27 Dec 2016
 *      Author: jeremy
 */

#include "InstrumentSelector.h"


namespace Widgets
{

	InstrumentSelector::InstrumentSelector(const std::string& name)
	: instrumentName(name), preferencesButton(Gtk::StockID("gtk-preferences")), deleteButton(Gtk::StockID("gtk-remove"))
	{

		this->set_column_homogeneous(true);
		this->set_border_width(4);

		this->attach(instrumentName, 0, 0, 1, 1);
		instrumentName.show();

		this->attach_next_to(preferencesButton, instrumentName, Gtk::PositionType::POS_RIGHT, 1, 1);
		preferencesButton.show();

		deleteButton.set_margin_left(4);
		this->attach_next_to(deleteButton, preferencesButton, Gtk::PositionType::POS_RIGHT, 1, 1);
		deleteButton.show();


		this->show();

		return;
	}


} /* namespace Widgets */
