/*
 * GuiHddTest.cpp
 *
 *  Created on: 13 Oct 2015
 *      Author: jeremy
 */

#include "GuiHddTest.h"

#include "../Gui/MainWindow.h"

#include <Source/IO/HddSensor.h>
#include <Source/Api/eXaDrums.h>

#include <gtkmm/application.h>

using namespace eXaDrumsApi;

namespace Testing
{

	int GuiHddTest::RunTest(int argc, char* argv[])
	{

		  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "");

		  Gui::MainWindow test;

		  return app->run(test);

	}

}
