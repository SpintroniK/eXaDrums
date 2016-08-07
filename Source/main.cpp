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
#include <gtkmm/button.h>

#include <string>
#include <memory>
#include <iostream>

int main(int argc, char* argv[])
{

	const std::string mainLocation = std::string(argv[0]);
	std::size_t pos = mainLocation.find_last_of("/");

	const std::string mainFolder = mainLocation.substr(0, pos);



	const std::string uiFileLocation = mainFolder + "/../Source/Ui.glade";

	// Create application and builder
	Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
	Glib::RefPtr<Gtk::Builder> builder = Gtk::Builder::create_from_file(uiFileLocation);

	// Get main window
	Gui::MainWindow* mainWindow = nullptr;
	builder->get_widget_derived("MainWindow", mainWindow);

	// Create controller
	std::shared_ptr<Gui::Controller> controller = std::shared_ptr<Gui::Controller>(new Gui::Controller(builder, mainFolder));

	// Give controller to main window
	mainWindow->SetController(controller);

	// Handle quit button signal
	Gtk::Button* quitButton = nullptr;
	builder->get_widget("QuitButton", quitButton);
	quitButton->signal_clicked().connect(sigc::mem_fun(mainWindow, &Gui::MainWindow::hide));

	// Run application
	int ret = app->run(*mainWindow);

	// Delete pointers
	delete mainWindow;
	delete quitButton;

	return ret;
}
