/*
 * main.cpp
 *
 *  Created on: 6 Sep 2015
 *      Author: jeremy
 */

#include "exadrumsConfig.h"
#include "Util/Util.h"
#include "Controllers/MainController.h"
#include "MainWindow/MainWindow.h"

#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/button.h>

#include <string>

using namespace eXaDrums;
using namespace Util;

int main(int argc, char** argv)
{

	Config config;

	if(!config.IsInstalledForUser())
	{
		config.InstallForUser();
	}

	// Init main controller
	Controllers::MainController controller;

	auto app = Gtk::Application::create(argc, argv, "org.eXaDrums", Gio::APPLICATION_HANDLES_COMMAND_LINE);
	app->signal_command_line().connect([&](const Glib::RefPtr<Gio::ApplicationCommandLine>& cmd){ return config.CommandLineParser(cmd, app); }, false);

	Gui::MainWindow* mainWindow = nullptr;
	auto quit = [&] { mainWindow->hide(); };

	// Create main controller and Gui only if the app has been activated
	app->signal_activate().connect([&]
	{
		auto builder = Gtk::Builder::create_from_file(config.UiPath());
		controller.Create(builder, config.UserDataPath(), config.IsRoot());

		// Get about dialog and set software version
		GetWidget<Gtk::AboutDialog>(builder, "eXaDrumsAboutDialog")->set_version(Config::ExaDrumsVersion());

		// Get main window
		builder->get_widget_derived("MainWindow", mainWindow);

		// Handle quit button signal
		GetWidget<Gtk::Button>(builder, "QuitButton")->signal_clicked().connect(quit);

		app->add_window(*mainWindow);
		mainWindow->show();

	}, false);


	// Run application
	return app->run();
}
