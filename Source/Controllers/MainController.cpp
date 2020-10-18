/*
 * Controller.cpp
 *
 *  Created on: 16 Apr 2016
 *      Author: jeremy
 */

#include "MainController.h"

#include "../Util/ErrorHandler.h"

using namespace eXaDrumsApi;
using namespace Util;
using namespace Errors;

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
				try
				{
					drumKit->Stop();
				}
				catch(...)
				{
					// Ignore error...
				}
			}
		}

		return;
	}


	void MainController::Create(Glib::RefPtr<Gtk::Builder>& bd, const std::string& mainFolder, const std::function<void()>& quit, bool isRoot)
	{

		this->builder = bd;

		// Start drum kit
		drumKit = std::make_shared<eXaDrums>(mainFolder.data());

		try
		{
			ErrorToException([&] { return drumKit->GetInitError(); });
		}
		catch(const Exception& e)
		{
			errorDialog(e);
			throw; // Rethrow exception so that it can be dealt with in main().
		}

		// Set controllers
		metronomeController = std::make_unique<MetronomeController>(this->builder, this->drumKit);
		coachController = std::make_unique<CoachController>(this->builder, this->drumKit);
		kitController = std::make_unique<KitController>(this->builder, this->drumKit, isRoot);
		configController = std::make_unique<ConfigController>(this->builder, this->drumKit, quit);


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
