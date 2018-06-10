/*
 * exadrumsConfig.h
 *
 *  Created on: 9 Jun 2018
 *      Author: jeremy
 */

#ifndef SOURCE_EXADRUMSCONFIG_H_
#define SOURCE_EXADRUMSCONFIG_H_

#include <gtkmm/application.h>
#include <gtkmmconfig.h>
#include <glibmm/optiongroup.h>
#include <glibmm/optioncontext.h>
#include <giomm.h>

#include <utility>
#include <type_traits>
#include <string>
#include <iostream>


constexpr auto EXADRUMS_MAJOR_VERSION = 0;
constexpr auto EXADRUMS_MINOR_VERSION = 1;
constexpr auto EXADRUMS_PATCH_VERSION = 0;
constexpr char VERSION_SEPARATOR[] = ".";


template <typename... T>
inline constexpr auto VersionToStr(const T&... v)
{
	std::string result;
	(void)std::initializer_list<std::common_type_t<T...>>{ (result += std::to_string(v) + VERSION_SEPARATOR, 0)... };
	result.pop_back();
	return result;
}

inline std::string ExaDrumsVersion()
{
	return VersionToStr(EXADRUMS_MAJOR_VERSION, EXADRUMS_MINOR_VERSION,EXADRUMS_PATCH_VERSION);
}

inline int CommandLineParser(const Glib::RefPtr<Gio::ApplicationCommandLine>& cmd, Glib::RefPtr<Gtk::Application>& app)
{

	Glib::OptionContext optionContext;
	Glib::OptionGroup optionGroup("options", "Application Options:");
	optionContext.add_group(optionGroup);

	// Add version entry
	Glib::OptionEntry optionEntry;
	optionEntry.set_long_name("version");
	optionEntry.set_short_name('v');
	optionEntry.set_description("Show version information and exit");

	bool showVersion = false;
	optionGroup.add_entry(optionEntry, showVersion);

	// Get arguments
	int argc;
	char** argv = cmd->get_arguments(argc);
	optionContext.parse(argc, argv);

	// Handle results
	if(showVersion)
	{
		std::cout << "eXaDrums version " << ExaDrumsVersion() << "\n\n";
		//std::cout << "using libeXaDrums version " << EXADRUMS_MAJOR_VERSION << "." << EXADRUMS_MINOR_VERSION << "." << EXADRUMS_PATCH_VERSION << "\n";
		std::cout << "using gtkmm version " << VersionToStr(GTKMM_MAJOR_VERSION, GTKMM_MINOR_VERSION, GTKMM_MICRO_VERSION) << std::endl;
		return 0;
	}

	// Activate the app
	app->activate();

	return 0;
}


#endif /* SOURCE_EXADRUMSCONFIG_H_ */
