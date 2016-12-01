/*
 * InstrumentSelector.h
 *
 *  Created on: 30 Nov 2016
 *      Author: jeremy
 */

#ifndef SOURCE_WIDGETS_INSTRUMENTTYPESELECTOR_H_
#define SOURCE_WIDGETS_INSTRUMENTTYPESELECTOR_H_


#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/comboboxtext.h>

#include <memory>

namespace Widgets
{

	class InstrumentTypeSelector : public Gtk::Grid
	{

	public:

		InstrumentTypeSelector();
		virtual ~InstrumentTypeSelector();

	private:


		Gtk::Label label;
		Gtk::ComboBoxText selector;

	};


	typedef std::shared_ptr<InstrumentTypeSelector> InstrumentTypeSelectorPtr;

} /* namespace Widgets */

#endif /* SOURCE_WIDGETS_INSTRUMENTTYPESELECTOR_H_ */
