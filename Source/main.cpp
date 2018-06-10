/*
 * main.cpp
 *
 *  Created on: 6 Sep 2015
 *      Author: jeremy
 */

#include "exadrumsConfig.h"
#include "Controllers/MainController.h"
#include "MainWindow/MainWindow.h"

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/button.h>

#include <string>

int main(int argc, char** argv)
{

	const std::string mainLocation{argv[0]};
	const std::size_t pos{mainLocation.find_last_of("/")};

	const std::string mainFolder{mainLocation.substr(0, pos)};
	const std::string uiFileLocation{mainFolder + "/../Source/Ui.glade"};

	// Init main controller
	Controllers::MainController controller(mainFolder);

	auto app = Gtk::Application::create(argc, argv, "org.eXaDrums", Gio::APPLICATION_HANDLES_COMMAND_LINE);
	app->signal_command_line().connect([&](const Glib::RefPtr<Gio::ApplicationCommandLine>& cmd){ return CommandLineParser(cmd, app); }, false);

	Gui::MainWindow* mainWindow = nullptr;
	auto quit = [&] { mainWindow->hide(); };

	// Create main controller and Gui only if the app has been activated
	app->signal_activate().connect([&]
	{
		auto builder = Gtk::Builder::create_from_file(uiFileLocation);
		controller.Create(builder);

		// Get about dialog and set software version
		Gtk::AboutDialog* aboutDialog = nullptr;
		builder->get_widget("eXaDrumsAboutDialog", aboutDialog);
		aboutDialog->set_version(ExaDrumsVersion());

		// Get main window
		builder->get_widget_derived("MainWindow", mainWindow);

		// Handle quit button signal
		Gtk::Button* quitButton = nullptr;
		builder->get_widget("QuitButton", quitButton);
		quitButton->signal_clicked().connect(quit);

		app->add_window(*mainWindow);
		mainWindow->show();

	}, false);


	// Run application
	return app->run();
}
