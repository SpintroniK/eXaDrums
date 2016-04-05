/*
 * MainWindow.h
 *
 *  Created on: 13 Oct 2015
 *      Author: jeremy
 */

#ifndef SOURCE_MAINWINDOW_MAINWINDOW_H_
#define SOURCE_MAINWINDOW_MAINWINDOW_H_

// For development purposes only
#ifndef __arm__
#define __arm__ (!(1==1))
#endif

// includes


#include "../Models/Model.h"
#include "../Views/Page.h"
#include "../Views/Pages.h"
#include "../Views/MainPage/MainPageView.h"


#include <Source/Api/eXaDrums.h>
#include <Source/IO/HddSensor.h>
#include <Source/IO/ISensor.h>
#include <Source/IO/SensorType.h>

#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/window.h>

#include <string>
#include <memory>

using namespace eXaDrumsApi;

namespace Gui
{

	class MainWindow : public Gtk::Window
	{

	public:

		MainWindow();
		virtual ~MainWindow();

		eXaDrums* GetDrumKit() { return drumKit.get(); }

		void SwitchToPage(Pages page);

	protected:

	  //Signal handlers:
	  void on_quitButton_clicked();

	private:


	  //Member widgets:
	  Gtk::Button button;
	  Gtk::Button quitButton;

	  std::unique_ptr<Gtk::Grid> grid;

	  PagePtr page;

	  //Drum kit
	  std::unique_ptr<eXaDrums> drumKit;

	  bool isDrumKitStarted;



	};

}


#endif /* SOURCE_MAINWINDOW_MAINWINDOW_H_ */
