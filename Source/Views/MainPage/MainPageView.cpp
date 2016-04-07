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

		// Set kitFrame title
		kitFrame.set_label(model->GetKitFrameTitle());

		// Add kitFrameGrid to kitFrame
		kitFrame.add(kitFrameGrid);

		// Set kitFrameGrid's border
		kitFrameGrid.set_border_width(4);
		kitFrameGrid.set_column_spacing(4);
		kitFrameGrid.set_hexpand(true);

		// Show kitFrame's contents
		kitFrame.show_all();

		// Set playButton text and signal function
		playButton = Gtk::Button(controller->GetPlayButtonLabel());
		playButton.signal_clicked().connect(sigc::mem_fun(this, &MainPageView::onPlayButtonClicked));

		// Set addKitButton label
		addKitButton = Gtk::Button(model->GetAddKitButtonLabel());

		// Set deleteKitButton label
		deleteKitButton = Gtk::Button(model->GetdeleteKitButtonLabel());
		deleteKitButton.set_margin_right(20);

		// Set configure button label
		configureButton = Gtk::Button(model->GetConfigureButtonLabel());
		configureButton.set_margin_right(20);

		// Create kits list
		kitsList = Gtk::ComboBoxText();
		//XXX Add fake kit for test
		kitsList.append("Default");
		kitsList.set_active(0);

		// Add widgets to kitFrame's grid
		kitFrameGrid.attach(addKitButton, 0, 0, 1, 1);
		kitFrameGrid.attach_next_to(deleteKitButton, addKitButton, Gtk::PositionType::POS_RIGHT, 1, 1);
		kitFrameGrid.attach_next_to(kitsList, deleteKitButton, Gtk::PositionType::POS_RIGHT, 1, 1);
		kitFrameGrid.attach_next_to(configureButton, kitsList, Gtk::PositionType::POS_RIGHT, 1, 1);
		kitFrameGrid.attach_next_to(playButton, configureButton, Gtk::PositionType::POS_RIGHT, 1, 1);


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

		playButton.set_label(this->controller->GetPlayButtonLabel());
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
