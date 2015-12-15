/*
 * MainWindow.cpp
 *
 *  Created on: 13 Oct 2015
 *      Author: jeremy
 */


#include "MainWindow.h"
#include <gtkmm/stock.h>
#include <iostream>

namespace Gui
{

	MainWindow::MainWindow()
	: button(Gtk::Stock::MEDIA_PLAY), drumKit(nullptr), isDrumKitStarted(false)
	{

		// Sets the border width of the window.
		set_border_width(10);

		// When the button receives the "clicked" signal, it will call the
		// on_button_clicked() method defined below.HelloWorld
		button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));

		add(button);

		button.show();

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

	}

}

