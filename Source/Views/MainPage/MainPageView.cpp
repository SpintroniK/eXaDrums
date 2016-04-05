/*
 * MainPageView.cpp
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#include "MainPageView.h"

namespace Gui
{

	MainPageView::MainPageView(MainPageModelPtr modelPtr, MainPageControllerPtr controllerPtr)
	: model(modelPtr),
	  controller(controllerPtr)
	{

		playButton = Gtk::Button(controller->GetPlayButtonText());
		playButton.signal_clicked().connect(sigc::mem_fun(this, &MainPageView::onPlayButtonClicked));

		this->attach(playButton, 0, 0, 1, 1);

		this->show_all();


		// Register events
		this->model->Subscribe(this);

		// Update page
		Update();

		return;
	}

	MainPageView::~MainPageView()
	{

		this->model->Unsubscribe(this);

		return;
	}

	void MainPageView::Update()
	{

		playButton.set_label(this->controller->GetPlayButtonText());
		playButton.mnemonic_activate(true);

		if(controller->IsDrumKitStarted())
		{
			playButton.set_image_from_icon_name("media-playback-stop");
		}
		else
		{
			playButton.set_image_from_icon_name("media-playback-start");
		}

		return;
	}

	// Signals handling
	void MainPageView::onPlayButtonClicked()
	{

		this->controller->StartOrStopDrumKit();

		return;
	}


} /* namespace Gui */
