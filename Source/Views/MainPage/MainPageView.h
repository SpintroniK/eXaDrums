/*
 * MainPageView.h
 *
 *  Created on: 3 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_VIEWS_MAINPAGE_MAINPAGEVIEW_H_
#define SOURCE_VIEWS_MAINPAGE_MAINPAGEVIEW_H_

#include "../../Models/Model.h"
#include "../../Models/MainPage/MainPageModel.h"
#include "../../Controllers/MainPage/MainPageController.h"
#include "../Page.h"


#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/grid.h>
#include <gtkmm/comboboxtext.h>

namespace Gui
{

	class MainPageView : public Page
	{

	public:

		MainPageView(MainPageModelPtr modelPtr, MainPageControllerPtr controllerPtr);
		virtual ~MainPageView();

		virtual void Update();

	protected:

		void onPlayButtonClicked();

	private:

		MainPageModelPtr model;
		MainPageControllerPtr controller;

		Gtk::Frame kitFrame;
		Gtk::Grid kitFrameGrid;
		Gtk::Button playButton;
		Gtk::Button addKitButton;
		Gtk::Button deleteKitButton;
		Gtk::Button configureButton;
		Gtk::ComboBoxText kitsList;
	};

} /* namespace Gui */

#endif /* SOURCE_VIEWS_MAINPAGE_MAINPAGEVIEW_H_ */
