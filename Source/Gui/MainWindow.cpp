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
	: button("_Play", true),
	  buttonQuit("_Quit", true),
	  grid(nullptr),
	  drumKit(nullptr),
	  isDrumKitStarted(false)
	{

		// Sets the border width of the window.
		set_border_width(10);
		set_decorated(false);

		// Detect if the code is running on a Raspberry Pi
		if(!__arm__)
			set_size_request(800, 480);
		else
			fullscreen();

		grid = std::unique_ptr<Gtk::Grid>(new Gtk::Grid);

		// When the button receives the "clicked" signal, it will call the
		// on_button_clicked() method defined below.HelloWorld
		//button.set_label("_Play");

		button.set_image_from_icon_name("media-playback-start");
		button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));

		buttonQuit.set_image_from_icon_name("application-exit");
		buttonQuit.signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_button_Quit_clicked));

		button.set_hexpand(true);
		buttonQuit.set_hexpand(false);

		grid->attach(button, 0, 0, 1, 1);
		grid->attach(buttonQuit, 1, 0, 1, 1);

		grid->set_column_spacing(10);
		grid->set_row_spacing(10);

		grid->show_all();

		add(*grid);

		this->show_all();

		// Init drum kit

		std::string moduleLocation("./Data/");
		drumKit = std::unique_ptr<eXaDrums>(new eXaDrums(moduleLocation.c_str(), IO::SensorType::Hdd));

		std::string kitsPath("Kits");

		drumKit->CreateKitManager(kitsPath.c_str());

		std::string kitLocation("Kits/default.xml");
		drumKit->LoadKit(kitLocation.c_str());

		return;
	}

	MainWindow::~MainWindow()
	{

		if(isDrumKitStarted)
			drumKit->Stop();

		return;
	}


	void MainWindow::on_button_clicked()
	{

		if(!isDrumKitStarted)
		{
			drumKit->Start();
		}
		else
		{
			drumKit->Stop();
		}

		isDrumKitStarted ^= true;

		return;

	}

	void MainWindow::on_button_Quit_clicked()
	{

		this->close();

		return;
	}

}

