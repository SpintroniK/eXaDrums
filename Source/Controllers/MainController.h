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
#include "ConfigController.h"
#include "CoachController.h"

#include <libexadrums/Api/eXaDrums.hpp>

#include <gtkmm/builder.h>
#include <gtkmm/button.h>
#include <gtkmm/checkbutton.h>
#include <gtkmm/aboutdialog.h>
#include <gtkmm/window.h>

#include <string>
#include <memory>
#include <functional>

#include <cstdlib>


namespace Controllers
{

	class MainController
	{

	public:

		MainController();
		virtual ~MainController();

		void Create(Glib::RefPtr<Gtk::Builder>& builder, const std::string& mf, const std::function<void()>& quit, bool isRoot);
		bool ReebootRequired() const 
		{
			if(configController != nullptr)
				return configController->IsImportConfig(); 
			
			return false;
		}

	private:

		// Signals methods
		// Dialogs
		void ShowAboutDialog();
		void HideAboutDialog(int responseId);

		bool isCreated = false;

		std::shared_ptr<eXaDrumsApi::eXaDrums> drumKit;
		Glib::RefPtr<Gtk::Builder> builder;

		// Controllers
		std::unique_ptr<MetronomeController> metronomeController;
		std::unique_ptr<CoachController> coachController;
		std::unique_ptr<KitController> kitController;
		std::unique_ptr<ConfigController> configController;

		// Buttons
		Gtk::Button* aboutButton = nullptr;
		Gtk::Button* rhythmCoachPrefButton = nullptr;

		// Dialogs
		Gtk::AboutDialog* aboutDialog = nullptr;

		// Windows


	};

} /* namespace Gui */

#endif /* SOURCE_CONTROLLERS_MAINCONTROLLER_H_ */
