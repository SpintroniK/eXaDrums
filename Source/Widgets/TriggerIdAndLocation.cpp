/*
 * TriggerIdAndLocation.cpp
 *
 *  Created on: 4 Dec 2016
 *      Author: jeremy
 */

#include "TriggerIdAndLocation.h"

namespace Widgets
{

	TriggerIdAndLocation::TriggerIdAndLocation(const std::vector<std::string>& locations, const std::vector<int>& triggersIds)
	: locationLabel("Location: "), triggerIdLabel("Trigger Id: "), location(true), triggerId(true)
	{


		this->set_halign(Gtk::Align::ALIGN_FILL);
		this->set_column_spacing(4);

		// Add locations
		for(const auto& l : locations)
		{
			location.append(l);
		}
		location.set_active(0);

		// Add triggers ids
		for(const auto& i : triggersIds)
		{
			triggerId.append(std::to_string(i));
		}
		triggerId.set_active(0);

		// Add location label
		locationLabel.set_halign(Gtk::Align::ALIGN_CENTER);
		locationLabel.show();
		this->attach(locationLabel, 0, 0, 1, 1);

		// Add location combobox
		location.set_halign(Gtk::Align::ALIGN_CENTER);
		location.get_entry()->set_width_chars(16);
		location.show();
		this->attach_next_to(location, locationLabel, Gtk::PositionType::POS_RIGHT, 1, 1);

		// Add id label
		triggerIdLabel.set_halign(Gtk::Align::ALIGN_CENTER);
		triggerIdLabel.show();
		this->attach_next_to(triggerIdLabel, location, Gtk::PositionType::POS_RIGHT, 1, 1);

		// Add id combobox
		triggerId.set_halign(Gtk::Align::ALIGN_CENTER);
		triggerId.get_entry()->set_width_chars(2);
		triggerId.show();
		this->attach_next_to(triggerId, triggerIdLabel, Gtk::PositionType::POS_RIGHT, 1, 1);


		this->show();

		return;
	}

	TriggerIdAndLocation::~TriggerIdAndLocation()
	{

		return;
	}

} /* namespace Widgets */
