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
	: quitButton("", true),
	  grid(nullptr),
	  page(nullptr),
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

		//button.set_image_from_icon_name("media-playback-start");
		//button.signal_clicked().connect(sigc::mem_fun(*this, &MainWindow::on_button_clicked));

		quitButton.set_image_from_icon_name("application-exit");
		quitButton.signal_clicked().connect(sigc::mem_fun(this, &MainWindow::on_quitButton_clicked));

		//button.set_hexpand(true);
		quitButton.set_hexpand(false);

		grid->attach(quitButton, 1, 0, 1, 1);

		// Default page is the main page
		this->SwitchToPage(Pages::mainPage);

		grid->set_column_spacing(10);
		grid->set_row_spacing(10);

		grid->show_all();

		add(*grid);

		this->show_all();

		// Init drum kit

		std::string moduleLocation("../Data/");
		drumKit = std::unique_ptr<eXaDrums>(new eXaDrums(moduleLocation.c_str(), IO::SensorType::Hdd));

		std::string kitLocation("Kits/default.xml");
		drumKit->LoadKit(kitLocation.c_str());

		return;
	}

	MainWindow::~MainWindow()
	{

		if(drumKit->IsStarted())
		{
			drumKit->Stop();
		}

		return;
	}


	void MainWindow::SwitchToPage(Pages page)
	{

		if(this->page != nullptr)
		{
			this->page.release();
		}

		switch(page)
		{
			case Pages::mainPage:
			{

				MainPageModelPtr model = MainPageModelPtr(new MainPageModel());
				MainPageControllerPtr controller = MainPageControllerPtr(new MainPageController(model, this));
				this->page = PagePtr(new MainPageView(model, controller));

				grid->attach(*this->page , 0, 1, 1, 1);

				break;
			}
			default:
				break;
		}


		return;
	}

	/*void MainWindow::on_button_clicked()
	{

		if(!isDrumKitStarted)
		{
			drumKit->Start();
			button.set_label("_Stop");
			button.mnemonic_activate(true);
			button.set_image_from_icon_name("media-playback-stop");
		}
		else
		{
			drumKit->Stop();
			button.set_label("_Play");
			button.mnemonic_activate(true);
			button.set_image_from_icon_name("media-playback-start");
		}

		isDrumKitStarted ^= true;

		return;

	}
	*/

	void MainWindow::on_quitButton_clicked()
	{

		this->close();

		return;
	}

}

