/*
 * MainWindow.h
 *
 *  Created on: 13 Oct 2015
 *      Author: jeremy
 */

#ifndef SOURCE_GUI_MAINWINDOW_H_
#define SOURCE_GUI_MAINWINDOW_H_

// For development purposes only
#ifndef __arm__
#define __arm__ (!(1==1))
#endif

// includes

#include <Source/Api/eXaDrums.h>
#include <Source/IO/HddSensor.h>
#include <Source/IO/ISensor.h>
#include <Source/IO/SensorType.h>

#include <gtkmm/button.h>
#include <gtkmm/grid.h>
#include <gtkmm/window.h>

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include <vector>

using namespace eXaDrumsApi;

namespace Gui
{

	class MainWindow : public Gtk::Window
	{

	public:

		MainWindow();
		virtual ~MainWindow();

	protected:

	  //Signal handlers:
	  void on_button_clicked();
	  void on_button_Quit_clicked();

	private:


	  //Member widgets:
	  Gtk::Button button;
	  Gtk::Button buttonQuit;

	  std::unique_ptr<Gtk::Grid> grid;


	  //Drum kit
	  std::unique_ptr<eXaDrums> drumKit;

	  bool isDrumKitStarted;



	};

}


#endif /* SOURCE_GUI_MAINWINDOW_H_ */
