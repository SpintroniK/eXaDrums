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
	: Gtk::Window(baseObject),
	  builder(builder)
	{


		return;
	}

	MainWindow::~MainWindow()
	{

		return;
	}

	void MainWindow::SetController(std::shared_ptr<Controller>& controller)
	{

		this->controller = controller;

		return;
	}

} /* namespace Gui */
