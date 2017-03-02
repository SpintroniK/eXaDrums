/*
 * ConfigController.cpp
 *
 *  Created on: 9 Feb 2017
 *      Author: jeremy
 */

#include "ConfigController.h"

#include <gtkmm/button.h>


using namespace eXaDrumsApi;

namespace Controllers
{

	ConfigController::ConfigController(Glib::RefPtr<Gtk::Builder> builder, std::shared_ptr<eXaDrums> drumKit)
	: builder(builder), drumKit(drumKit), drumsConfig(*drumKit.get())
	{

		Gtk::Button* mixerConfigButton = nullptr;
		Gtk::Button* soundLibraryButton = nullptr;
		Gtk::Button* triggersConfigButton = nullptr;
		Gtk::Button* soundEffectsButton = nullptr;
		Gtk::Button* sensorsConfigButton = nullptr;

		// Get all widgets
		{

			// Buttons
			builder->get_widget("MixerConfigButton", mixerConfigButton);
			builder->get_widget("SoundLibraryButton", soundLibraryButton);
			builder->get_widget("TriggersConfigButton", triggersConfigButton);
			builder->get_widget("SoundEffectsButton", soundEffectsButton);
			builder->get_widget("SensorsConfigButton", sensorsConfigButton);

			// Windows
			builder->get_widget("SensorsConfigWindow", sensorsConfigWindow);

		}

		// Connect signals
		{

			mixerConfigButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowMixerConfigWindow));
			soundLibraryButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowSoundLibConfigWindow));
			triggersConfigButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowTriggersConfigWindow));
			soundEffectsButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowSoundEffectsWindow));
			sensorsConfigButton->signal_clicked().connect(sigc::mem_fun(this, &ConfigController::ShowSensorsConfigWindow));

		}

		return;
	}


	ConfigController::~ConfigController()
	{

		delete sensorsConfigWindow;

		return;
	}

	// Private Methods

	void ConfigController::ShowMixerConfigWindow()
	{


		return;
	}

	void ConfigController::ShowSoundLibConfigWindow()
	{

		return;
	}

	void ConfigController::ShowTriggersConfigWindow()
	{

		return;
	}

	void ConfigController::ShowSoundEffectsWindow()
	{

		return;
	}

	void ConfigController::ShowSensorsConfigWindow()
	{

		sensorsConfigWindow->show();

		return;
	}


} /* namespace Controllers */
