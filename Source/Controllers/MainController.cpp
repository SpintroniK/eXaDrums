/*
 * Controller.cpp
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#include "MainController.h"


using namespace eXaDrumsApi;

namespace Controllers
{

	MainController::MainController(Glib::RefPtr<Gtk::Builder>& builder, std::string const& mainFolder)
	: mainFolder(mainFolder), builder(builder)
	{

		// Start drum kit
		const std::string moduleLocation(mainFolder+"/../Data/");
		drumKit = std::shared_ptr<eXaDrums>(new eXaDrums(moduleLocation.c_str()));

		// Set controllers
		metronomeController = std::unique_ptr<MetronomeController>(new MetronomeController(this->builder, this->drumKit));
		coachController = std::unique_ptr<CoachController>(new CoachController(this->builder, this->drumKit));
		kitController = std::unique_ptr<KitController>(new KitController(this->builder, this->drumKit));
		configController = std::unique_ptr<ConfigController>(new ConfigController(this->builder, this->drumKit));


		// Get all widgets
		{
			// Buttons
			builder->get_widget("AboutButton", aboutButton);
			builder->get_widget("RhythmCoachPrefButton", rhythmCoachPrefButton);

			// Dialogs
			builder->get_widget("eXaDrumsAboutDialog", aboutDialog);

			// Windows

		}


		// Connect all signals
		{
			// Buttons
			aboutButton->signal_clicked().connect([&] { ShowAboutDialog(); });
			rhythmCoachPrefButton->signal_clicked().connect([&] { metronomeController->ShowMetronomePrefs(); });

			// Dialog
			aboutDialog->signal_response().connect([&](int i) { HideAboutDialog(i); });

		}

		return;
	}

	MainController::~MainController()
	{

		// Delete all pointers (dialogs and windows)
		delete aboutDialog;

		// Stop drum kit
		if(drumKit->IsStarted())
		{
			drumKit->Stop();
		}

		return;
	}

	// PRIVATE METHODS



	void MainController::ShowAboutDialog()
	{
		aboutDialog->show();
		return;
	}

	void MainController::HideAboutDialog(int responseId)
	{
		aboutDialog->hide();
		return;
	}


} /* namespace Gui */
