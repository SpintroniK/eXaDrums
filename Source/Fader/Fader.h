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

	class Fader : public Gtk::Grid
	{

	public:

		Fader(const std::string& name, int vol);
		virtual ~Fader();

	private:

		Gtk::Label label;
		Gtk::Scale volScale;
		int volume;

	};

	typedef std::shared_ptr<Fader> FaderPtr;

} /* namespace Gui */

#endif /* SOURCE_FADER_FADER_H_ */
