/*
 * main.cpp
 *
 *  Created on: 6 Sep 2015
 *      Author: jeremy
 */


#include "Controllers/MainController.h"
#include "MainWindow/MainWindow.h"

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/button.h>

#include <string>
#include <memory>

int main(int argc, char* argv[])
{

	const std::string mainLocation{argv[0]};
	const std::size_t pos{mainLocation.find_last_of("/")};

	const std::string mainFolder{mainLocation.substr(0, pos)};
	const std::string uiFileLocation{mainFolder + "/../Source/Ui.glade"};

	// Create application and builder
	auto app = Gtk::Application::create(argc, argv);
	auto builder = Gtk::Builder::create_from_file(uiFileLocation);

	// Get main window
	Gui::MainWindow* mainWindow = nullptr;
	builder->get_widget_derived("MainWindow", mainWindow);

	// Create controller
	auto controller = std::make_unique<Controllers::MainController>(builder, mainFolder);

	// Handle quit button signal
	Gtk::Button* quitButton = nullptr;
	builder->get_widget("QuitButton", quitButton);
	quitButton->signal_clicked().connect([&] { mainWindow->hide(); });

	// Run application
	int ret = app->run(*mainWindow);

	// Delete pointers (dialogs and windows)
	delete mainWindow;

	return ret;
}
