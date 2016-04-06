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
	: playButtonText("Play"),
	  kitFrameTitle("Drum kit")
	{

		return;
	}

	MainPageModel::~MainPageModel()
	{

		return;
	}


	void MainPageModel::SetPlayButtonText(std::string text)
	{

		 this->playButtonText = text;

		 this->Notify();

		return;
	}

} /* namespace Gui */
