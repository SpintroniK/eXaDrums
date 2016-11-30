/*
 * InstrumentSelector.h
 *
 *  Created on: 30 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_WIDGETS_INSTRUMENTSELECTOR_H_
#define SOURCE_WIDGETS_INSTRUMENTSELECTOR_H_


#include <gtkmm/grid.h>
#include <gtkmm/label.h>

#include <memory>

namespace Widgets
{

	class InstrumentSelector : public Gtk::Grid
	{

	public:

		InstrumentSelector();
		virtual ~InstrumentSelector();

	private:


		Gtk::Label label;

	};


	typedef std::shared_ptr<InstrumentSelector> InstrumentSelectorPtr;

} /* namespace Widgets */

#endif /* SOURCE_WIDGETS_INSTRUMENTSELECTOR_H_ */
