/*
 * MainWindow.h
 *
 *  Created on: 13 Oct 2015
 *      Author: jeremy
 */

#ifndef SOURCE_GUI_MAINWINDOW_H_
#define SOURCE_GUI_MAINWINDOW_H_

#include <Source/Api/eXaDrumKit.h>
#include <Source/IO/HddSensor.h>
#include <Source/IO/ISensor.h>
#include <Source/IO/SensorType.h>

#include <gtkmm/button.h>
#include <gtkmm/window.h>

#include <iostream>
#include <string>
#include <thread>
#include <chrono>
#include <memory>
#include <vector>

using namespace eXaDrumKitApi;

namespace Gui
{

	class MainWindow : public Gtk::Window
	{

	public:

		MainWindow();
		~MainWindow();

	protected:

	  //Signal handlers:
	  void on_button_clicked();

	private:


	  //Member widgets:
	  Gtk::Button button;

	  //Drum kit
	  std::unique_ptr<eXaDrumKit> drumKit;

	  bool isDrumKitStarted;



	};

}


#endif /* SOURCE_GUI_MAINWINDOW_H_ */
