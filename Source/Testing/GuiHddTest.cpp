/*
 * GuiHddTest.cpp
 *
 *  Created on: 13 Oct 2015
 *      Author: jeremy
 */

#include "GuiHddTest.h"

#include "../Gui/MainWindow.h"

#include <Source/Api/eXaDrumKit.h>
#include <Source/IO/HddSensor.h>

#include <gtkmm/application.h>

using namespace eXaDrumKitApi;

namespace Testing
{

	int GuiHddTest::RunTest(int argc, char* argv[])
	{

		  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

		  Gui::MainWindow test;

		  return app->run(test);

	}

}
