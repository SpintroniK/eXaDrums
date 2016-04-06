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
	  controller(controllerPtr),
	  kitFrame(),
	  kitFrameGrid()
	{

		// Set kitFrame title
		kitFrame.set_label(model->GetKitFrameTitle());

		// Add kitFrameGrid to kitFrame
		kitFrame.add(kitFrameGrid);

		// Set kitFrameGrid's border
		kitFrameGrid.set_border_width(10);
		kitFrameGrid.set_hexpand(true);

		// Show kitFrame's contents
		kitFrame.show_all();

		// Set button text and signal function
		playButton = Gtk::Button(controller->GetPlayButtonText());
		playButton.signal_clicked().connect(sigc::mem_fun(this, &MainPageView::onPlayButtonClicked));

		// Add button to kitFrame's grid
		kitFrameGrid.attach(playButton, 0, 0, 1, 1);

		kitFrameGrid.show_all();

		// Add kitFrame to main grid
		this->attach(kitFrame, 0, 0, 1, 1);

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
