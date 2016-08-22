/*
 * Fader.h
 *
 *  Created on: 21 Aug 2016
 *      Author: jeremy
 */

#ifndef SOURCE_FADER_FADER_H_
#define SOURCE_FADER_FADER_H_

#include <gtkmm/grid.h>
#include <gtkmm/label.h>
#include <gtkmm/scale.h>

#include <string>
#include <memory>

namespace Gui
{

	class Controller;

	class Fader : public Gtk::Grid
	{

	friend class Controller;

	public:

		Fader(const std::string& name, int instrumentId, int vol);
		virtual ~Fader();

		int GetInstrumentId() const { return instrument; }

	private:

		int instrument;
		int volume;
		Gtk::Label label;
		Gtk::Scale volScale;

	};

	typedef std::shared_ptr<Fader> FaderPtr;

} /* namespace Gui */

#endif /* SOURCE_FADER_FADER_H_ */
