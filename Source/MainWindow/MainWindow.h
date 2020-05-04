/*
 * MainWindow.h
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_MAINWINDOW_MAINWINDOW_H_
#define SOURCE_MAINWINDOW_MAINWINDOW_H_

#include "../Controllers/MainController.h"

#include <gtkmm/window.h>
#include <gtkmm/builder.h>


namespace Gui
{

	class MainWindow : public Gtk::Window
	{

	public:

		MainWindow(BaseObjectType* baseObject, const Glib::RefPtr<Gtk::Builder>& builder);
		virtual ~MainWindow();

	private:

	};

} /* namespace Gui */

#endif /* SOURCE_MAINWINDOW_MAINWINDOW_H_ */
