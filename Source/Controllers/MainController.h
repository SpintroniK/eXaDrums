/*
 * Controller.h
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#ifndef SOURCE_CONTROLLERS_MAINCONTROLLER_H_
#define SOURCE_CONTROLLERS_MAINCONTROLLER_H_


#include "MetronomeController.h"
#include "KitController.h"

#include <Source/Api/eXaDrums.h>

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/window.h>

#include <string>
#include <memory>

#include <cstdlib>


namespace Gui
{

	class MainController
	{

	public:

		MainController(Glib::RefPtr<Gtk::Builder>& builder, std::string const& mainFolder);
		virtual ~MainController();

	private:

		// Signals methods

		// Dialogs
		void ShowAboutDialog();
		void HideAboutDialog(int responseId);


		std::string mainFolder;

		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;
		Glib::RefPtr<Gtk::Builder> builder;

		// Controllers
		std::unique_ptr<MetronomeController> metronomeController;
		std::unique_ptr<KitController> kitController;

		// Buttons
		Gtk::Button* aboutButton;
		Gtk::Button* rhythmCoachPrefButton;


		// Dialogs
		Gtk::AboutDialog* aboutDialog;

		// Windows


	};

} /* namespace Gui */

#endif /* SOURCE_CONTROLLERS_MAINCONTROLLER_H_ */
