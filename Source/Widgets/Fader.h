/*
 * Fader.h
 *
 *  Created on: 21 Aug 2016
 *      Author: jeremy
 */

#ifndef SOURCE_WIDGETS_FADER_H_
#define SOURCE_WIDGETS_FADER_H_

#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/scale.h>

#include <string>
#include <memory>

namespace Widgets
{

	class Fader : public Gtk::Grid
	{

	public:

		Fader(const std::string& name, int instrumentId, int vol);
		virtual ~Fader() = default;

		Gtk::Scale& GetScale() { return volScale; };

		int GetInstrumentId() const { return instrument; }
		int GetValue() const { return (int)volScale.get_value(); }

	private:

		int instrument;
		int volume;
		Gtk::Label label;
		Gtk::Scale volScale;

	};

	using FaderPtr = std::unique_ptr<Fader>;

} /* namespace Gui */

#endif /* SOURCE_WIDGETS_FADER_H_ */
