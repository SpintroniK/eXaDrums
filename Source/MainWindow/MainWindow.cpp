/*
 * MainWindow.cpp
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#include "MainWindow.h"

namespace Gui
{

	MainWindow::MainWindow(BaseObjectType* baseObject, const Glib::RefPtr<Gtk::Builder>& builder)
	: Gtk::Window(baseObject)
	{

		if(!__arm__)
		{
			set_size_request(800, 480);
		}
		else
		{
			fullscreen();
		}


		return;
	}

	MainWindow::~MainWindow()
	{

		return;
	}

} /* namespace Gui */
