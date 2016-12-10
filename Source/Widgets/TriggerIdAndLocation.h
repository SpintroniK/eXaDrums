/*
 * TriggerIdAndLocation.h
 *
 *  Created on: 4 Dec 2016
 *      Author: jeremy
 */

#ifndef SOURCE_WIDGETS_TRIGGERIDANDLOCATION_H_
#define SOURCE_WIDGETS_TRIGGERIDANDLOCATION_H_

#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>

#include <memory>
#include <vector>
#include <string>

namespace Widgets
{

	class TriggerIdAndLocation : public Gtk::Grid
	{

	public:

		TriggerIdAndLocation(const std::vector<std::string>& locations, const std::vector<int>& ids);
		virtual ~TriggerIdAndLocation();


	private:

		Gtk::Label locationLabel;
		Gtk::Label triggerIdLabel;
		Gtk::ComboBoxText location;
		Gtk::ComboBoxText triggerId;

	};


	typedef std::shared_ptr<TriggerIdAndLocation> TriggerIdAndLocationPtr;

} /* namespace Widgets */

#endif /* SOURCE_WIDGETS_TRIGGERIDANDLOCATION_H_ */
