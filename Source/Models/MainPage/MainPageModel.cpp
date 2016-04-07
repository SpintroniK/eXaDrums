/*
 * MainPageModel.cpp
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#include "MainPageModel.h"

namespace Gui
{

	MainPageModel::MainPageModel()
	: kitFrameTitle("Drum kit"),
	  playButtonLabel("Play"),
	  addKitButtonLabel("Add"),
	  deleteKitButtonLabel("Delete"),
	  configureButtonLabel("Configure")
	{

		return;
	}

	MainPageModel::~MainPageModel()
	{

		return;
	}


	void MainPageModel::SetPlayButtonText(std::string text)
	{

		 this->playButtonLabel = text;

		 this->Notify();

		return;
	}

} /* namespace Gui */
