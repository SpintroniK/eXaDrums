/*
 * main.cpp
 *
 *  Created on: 6 Sep 2015
 *      Author: jeremy
 */

#include "../config.h"
#include "exadrumsConfig.h"
#include "Util/Util.h"
#include "Util/ErrorHandler.h"
#include "Controllers/MainController.h"

#include <gtkmm/window.h>
#include <gtkmm/application.h>
#include <gtkmm/builder.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/button.h>

#include <string>

using namespace eXaDrums;
using namespace Util;
using namespace Errors;

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

    Gtk::Window* mainWindow = nullptr;
    auto quit = [&] { mainWindow->hide(); };

    auto toggle_fullscreen = [&](Gtk::Button* fs_button)
    {
        if(!is_fullscreen)
        {
            mainWindow->fullscreen();
            fs_button->set_property("label", Gtk::StockID("gtk-leave-fullscreen"));
            is_fullscreen = true;
        }
        else
        {
            mainWindow->unfullscreen();
            fs_button->set_property("label", Gtk::StockID("gtk-fullscreen"));
            is_fullscreen = false;
        }
    };

    // Create main controller and Gui only if the app has been activated
    app->signal_activate().connect([&]
    {
        
        Glib::RefPtr<Gtk::Builder> builder;
        try
        {
            builder = Gtk::Builder::create_from_file(config.UiPath());
        }
        catch(...)
        {
            errorDialog("Could not find UI file (" + config.UiPath().string() + ").", error_type_error);
            return; // Exit properly if UI file can't be loaded.
        }

        try
        {
            controller.Create(builder, config.UserDataPath(), quit, config.IsRoot());
        }
        catch(...)
        {
            return; // Exit properly if controller can't be created.
        }

        // Get about dialog and set software version
        GetWidget<Gtk::AboutDialog>(builder, "eXaDrumsAboutDialog")->set_version(PACKAGE_VERSION);

        // Get main window
        builder->get_widget("MainWindow", mainWindow);

        // Handle quit button signal
        GetWidget<Gtk::Button>(builder, "QuitButton")->signal_clicked().connect(quit);
        const auto fsButton = GetWidget<Gtk::Button>(builder, "FullScreenButton");
        fsButton->signal_clicked().connect([&, fsButton]{ toggle_fullscreen(fsButton); });

        if(is_fullscreen)
        {
            is_fullscreen = false;
            toggle_fullscreen(fsButton);
        }

        app->add_window(*mainWindow);
        mainWindow->show();

    }, false);


    // Run application
    return app->run();
}
