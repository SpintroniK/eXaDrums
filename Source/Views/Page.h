/*
 * View.h
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_VIEWS_PAGE_H_
#define SOURCE_VIEWS_PAGE_H_

#include "../Models/Model.h"
#include "../Observers/Observer.h"

#include <gtkmm/grid.h>

#include <memory>

namespace Gui
{

	class Page : public Gtk::Grid, public Observer
	{

	public:

		virtual ~Page() {};

	};

	typedef std::unique_ptr<Page> PagePtr;


}


#endif /* SOURCE_VIEWS_PAGE_H_ */
