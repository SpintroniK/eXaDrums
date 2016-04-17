/*
 * Controller.h
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLER_CONTROLLER_H_
#define SOURCE_CONTROLLER_CONTROLLER_H_

#include <Source/Api/eXaDrums.h>

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/aboutdialog.h>

#include <memory>
#include <functional>

using namespace eXaDrumsApi;

namespace Gui
{

	class Controller
	{

	public:

		Controller(Glib::RefPtr<Gtk::Builder>& builder);
		virtual ~Controller();

	private:

		void ShowAboutDialog();
		void HideAboutDialog(int responseId);
		void PlayDrums();

		std::unique_ptr<eXaDrums> drumKit;
		Glib::RefPtr<Gtk::Builder> builder;

		// Buttons
		Gtk::Button* aboutButton;
		Gtk::Button* playButton;

		// Dialogs
		Gtk::AboutDialog* aboutDialog;

	};

} /* namespace Gui */

#endif /* SOURCE_CONTROLLER_CONTROLLER_H_ */