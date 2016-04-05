/*
 * MainPageController.cpp
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#include "../../MainWindow/MainWindow.h"

#include "MainPageController.h"

namespace Gui
{

	MainPageController::MainPageController(MainPageModelPtr& modelPtr, MainWindow* mainWindow)
	:  model(modelPtr),
	   main(mainWindow),
	   isDrumKitStarted(false)

	{

		return;
	}

	MainPageController::~MainPageController()
	{

		return;
	}

	void MainPageController::StartOrStopDrumKit()
	{

		if(isDrumKitStarted == true)
		{
			isDrumKitStarted = false;
			main->GetDrumKit()->Stop();
			model->SetPlayButtonText(model->GetPlayText());
		}
		else
		{
			isDrumKitStarted = true;
			main->GetDrumKit()->Start();
			model->SetPlayButtonText(model->GetStopText());
		}

		return;
	}

	std::string MainPageController::GetPlayButtonText() const
	{
		return model->GetPlayButtonText();
	}

} /* namespace Gui */
