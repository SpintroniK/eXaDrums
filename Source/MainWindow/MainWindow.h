/*
 * MainWindow.h
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_MAINWINDOW_MAINWINDOW_H_
#define SOURCE_MAINWINDOW_MAINWINDOW_H_

#include "../Controller/Controller.h"

#include <gtkmm/window.h>
#include <gtkmm/builder.h>

#include <memory>

#ifndef __arm__
#define __arm__ (!(1==1))
#endif

namespace Gui
{

	class MainWindow : public Gtk::Window
	{

	public:

		MainWindow(BaseObjectType* baseObject, const Glib::RefPtr<Gtk::Builder>& builder);
		virtual ~MainWindow();

		void SetController(std::shared_ptr<Controller>& controller);

	private:

		Glib::RefPtr<Gtk::Builder> builder;
		std::shared_ptr<Controller> controller;

	};

} /* namespace Gui */

#endif /* SOURCE_MAINWINDOW_MAINWINDOW_H_ */
