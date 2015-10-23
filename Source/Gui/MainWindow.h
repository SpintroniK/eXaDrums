/*
 * MainWindow.h
 *
 *  Created on: 13 Oct 2015
 *      Author: jeremy
 */

#ifndef SOURCE_GUI_MAINWINDOW_H_
#define SOURCE_GUI_MAINWINDOW_H_

#include <gtkmm/button.h>
#include <gtkmm/window.h>

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


	};

}


#endif /* SOURCE_GUI_MAINWINDOW_H_ */
