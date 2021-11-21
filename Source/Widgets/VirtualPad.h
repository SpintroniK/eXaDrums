/*
 * VirtualInstrument.h
 *
 *  Created on: 13 Jan 2019
 *      Author: jeremy
 */

#ifndef EXADRUMS_SOURCE_WIDGETS_VIRTUALPAD_H
#define EXADRUMS_SOURCE_WIDGETS_VIRTUALPAD_H

#include <gtkmm/grid.h>
#include <gtkmm/button.h>
#include <gtkmm/entry.h>
#include <gtkmm/label.h>

#include <string>
#include <functional>
#include <algorithm>
#include <memory>

namespace Widgets
{

	class VirtualPad : public Gtk::Grid
	{

	public:
		VirtualPad(std::string const& name, std::vector<std::function<void()>>&& soundsVec)
		{

			// Register functions that play sounds
			for(auto&& f : soundsVec)
			{
				sounds.emplace_back(std::move(f));
			}

			const size_t nbTrigs = sounds.size();

			// Prepare keys vector
			keys.resize(nbTrigs);


			// Create buttons and entries
			for(size_t i = 0; i < nbTrigs; ++i)
			{
				// Add button to vector
				if(nbTrigs > 1)
				{
					buttons.emplace_back(name + " (Trig." + std::to_string(i) + ")");
				}
				else
				{
					buttons.emplace_back(name);
				}

				// Connect button signal
				buttons.back().signal_clicked().connect(sounds[i], false);

				// Add entry to vector
				shortcuts.emplace_back();

				// Connect entry signal
				shortcuts.back().signal_changed().connect([&, i]{ keys[i] = shortcuts[i].get_text(); });
			}


			// Attach buttons and entries
			for(size_t i = 0; i < buttons.size(); ++i)
			{
				buttons[i].set_hexpand();
				shortcuts[i].set_tooltip_text("Keyboard shortcuts (2 max) for this trigger.");
				shortcuts[i].set_max_width_chars(3);
				shortcuts[i].set_max_length(2);
				shortcuts[i].set_width_chars(3);

				if(i == 0)
				{
					this->attach(buttons[i], 0, 0, 1, 1);
					this->attach_next_to(shortcuts[i], buttons[i], Gtk::PositionType::POS_RIGHT, 1, 1);
				}
				else
				{
					this->attach_next_to(buttons[i], buttons[i-1], Gtk::PositionType::POS_BOTTOM, 1, 1);
					this->attach_next_to(shortcuts[i], buttons[i], Gtk::PositionType::POS_RIGHT, 1, 1);
				}
			}

			this->set_halign(Gtk::Align::ALIGN_FILL);
			this->show_all();

		}

		virtual ~VirtualPad() = default;

		void PlaySound(char k) const
		{
			auto kIt = std::find_if(keys.begin(), keys.end(), [&] (const auto& key) { return key.find(k) != std::string::npos; });

			if(kIt != keys.end())
			{
				const size_t index = kIt - keys.begin();
				if(sounds[index])
				{
					sounds[index]();
				}
			}

		}


	private:

		std::vector<std::function<void()>> sounds;
		std::vector<Gtk::Button> buttons;
		std::vector<Gtk::Entry> shortcuts;
		std::vector<std::string> keys;

	};

	using VirtualPadPtr = std::unique_ptr<VirtualPad>;

}

#endif /* EXADRUMS_SOURCE_WIDGETS_VIRTUALPAD_H */
