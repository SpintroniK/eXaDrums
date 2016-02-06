/*
 * main.cpp
 *
 *  Created on: 6 Sep 2015
 *      Author: jeremy
 */

#include "Gui/MainWindow.h"

#include <gtkmm/application.h>

int main(int argc, char* argv[])
{

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "eXaDrums");
	Gui::MainWindow mainWindow;

	return app->run(mainWindow);
}
