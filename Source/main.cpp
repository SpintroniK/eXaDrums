/*
 * main.cpp
 *
 *  Created on: 6 Sep 2015
 *      Author: jeremy
 */

#include "MainWindow/MainWindow.h"
#include "Controller/Controller.h"

#include <gtkmm/application.h>
#include <gtkmm/builder.h>

#include <string>
#include <memory>

int main(int argc, char* argv[])
{

	const std::string uiFileLocation = "../Source/Ui.glade";

	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(uiFileLocation);

	Gui::MainWindow* mainWindow = nullptr;
	builder->get_widget_derived("MainWindow", mainWindow);

	std::shared_ptr<Gui::Controller> controller = std::shared_ptr<Gui::Controller>(new Gui::Controller(builder));

	mainWindow->SetController(controller);

	int ret = app->run(*mainWindow);

	delete mainWindow;

	return ret;
}
