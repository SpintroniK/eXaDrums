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

	MainController::MainController()
	{

	}

	MainController::~MainController()
	{

		if(isCreated)
		{
			// Stop drum kit
			if(drumKit->IsStarted())
			{
				drumKit->Stop();
			}
		}

		return;
	}

	void MainController::Create(Glib::RefPtr<Gtk::Builder>& bd, const std::string& mainFolder)
	{

		this->builder = bd;

		// Start drum kit
		drumKit = std::shared_ptr<eXaDrums>(new eXaDrums(mainFolder.data()));

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

		}

		// Connect all the signals
		{
			// Buttons
			aboutButton->signal_clicked().connect([&] { ShowAboutDialog(); });
			rhythmCoachPrefButton->signal_clicked().connect([&] { metronomeController->ShowMetronomePrefs(); });

			// Dialog
			aboutDialog->signal_response().connect([&](int i) { HideAboutDialog(i); });

		}

		isCreated = true;

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
