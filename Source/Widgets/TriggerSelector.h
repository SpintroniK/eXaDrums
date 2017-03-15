/*
 * TriggerSelector.h
 *
 *  Created on: 14 Mar 2017
 *      Author: jeremy
 */

#ifndef SOURCE_WIDGETS_TRIGGERSELECTOR_H_
#define SOURCE_WIDGETS_TRIGGERSELECTOR_H_

#include <gtkmm/grid.h>

#include <memory>

namespace Widgets
{

	class TriggerSelector : public Gtk::Grid
	{

	public:

		TriggerSelector();
		virtual ~TriggerSelector();

	};


	typedef std::shared_ptr<TriggerSelector> TriggerSelectorPtr;

} /* namespace Widgets */

#endif /* SOURCE_WIDGETS_TRIGGERSELECTOR_H_ */
