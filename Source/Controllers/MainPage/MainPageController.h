/*
 * MainPageController.h
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_MAINPAGE_MAINPAGECONTROLLER_H_
#define SOURCE_CONTROLLERS_MAINPAGE_MAINPAGECONTROLLER_H_

#include "../../Models/MainPage/MainPageModel.h"

#include <memory>
#include <string>

namespace Gui
{

	class MainWindow;

	class MainPageController
	{

	public:

		MainPageController(MainPageModelPtr& modelPtr, MainWindow* mainWindow);
		virtual ~MainPageController();

		void StartOrStopDrumKit();
		bool IsDrumKitStarted() const { return isDrumKitStarted; }
		std::string GetPlayButtonLabel() const;

	private:

		MainPageModelPtr model;
		MainWindow* main;

		bool isDrumKitStarted;


	};

	typedef std::shared_ptr<MainPageController> MainPageControllerPtr;


} /* namespace Gui */

#endif /* SOURCE_CONTROLLERS_MAINPAGE_MAINPAGECONTROLLER_H_ */
