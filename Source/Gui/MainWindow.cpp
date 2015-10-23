/*
 * MainWindow.cpp
 *
 *  Created on: 13 Oct 2015
 *      Author: jeremy
 */


#include "MainWindow.h"

#include <iostream>

namespace Gui
{

	MainWindow::MainWindow()
	: button("Start/Stop")
	{

		// Sets the border width of the window.
		set_border_width(10);

		// When the button receives the "clicked" signal, it will call the
		// on_button_clicked() method defined below.HelloWorld
		button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));

		add(button);

		button.show();

		return;
	}

	MainWindow::~MainWindow()
	{

		return;
	}


	void MainWindow::on_button_clicked()
	{
	  std::cout << "Hello World" << std::endl;
	}

}

