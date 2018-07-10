/*
 * exadrumsConfig.h
 *
 *  Created on: 9 Jun 2018
 *      Author: jeremy
 */

#ifndef SOURCE_EXADRUMSCONFIG_H_
#define SOURCE_EXADRUMSCONFIG_H_

#include <Source/Api/eXaDrums.h>

#if __has_include(<filesystem>)
	#include <filesystem>
	namespace fs = std::filesystem;
#else
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#endif

#include <gtkmm/application.h>
#include <gtkmmconfig.h>
#include <glibmm/optiongroup.h>
#include <glibmm/optioncontext.h>
#include <giomm.h>

#include <utility>
#include <type_traits>
#include <string>
#include <iostream>
#include <cstdlib>

namespace eXaDrums
{

	constexpr auto EXADRUMS_MAJOR_VERSION = 0;
	constexpr auto EXADRUMS_MINOR_VERSION = 1;
	constexpr auto EXADRUMS_PATCH_VERSION = 0;
	constexpr char VERSION_SEPARATOR[] = ".";

	class Config
	{

	public:

		Config()
		{

		}

		~Config()
		{

		}

		template <typename... T>
		static constexpr auto VersionToStr(const T&... v)
		{
			std::string result = ( (std::to_string(v) + VERSION_SEPARATOR) + ... );
			result.pop_back();
			return result;
		}

		static std::string ExaDrumsVersion()
		{
			return VersionToStr(EXADRUMS_MAJOR_VERSION, EXADRUMS_MINOR_VERSION,EXADRUMS_PATCH_VERSION);
		}

		int CommandLineParser(const Glib::RefPtr<Gio::ApplicationCommandLine>& cmd, Glib::RefPtr<Gtk::Application>& app)
		{
			using namespace eXaDrumsApi;

			Glib::OptionContext optionContext;
			Glib::OptionGroup optionGroup("options", "Application Options: ");
			optionContext.add_group(optionGroup);

			// Add version entry
			auto versionEntry = MakeOption<bool>("version", 'v', "Show version information and exit");
			optionGroup.add_entry(versionEntry.first, versionEntry.second);

			// Add config folder entry
			auto configEntry = MakeOption<Glib::ustring>("config", 'c', "Change configuration directory");
			optionGroup.add_entry(configEntry.first, configEntry.second);

			// Get arguments
			int argc;
			char** argv = cmd->get_arguments(argc);
			optionContext.parse(argc, argv);

			// Handle results
			if(versionEntry.second)
			{
				std::cout << "eXaDrums version " << ExaDrumsVersion() << "\n\n";
				std::cout << "using libeXaDrums version " << VersionToStr(LIBEXADRUMS_MAJOR_VERSION, LIBEXADRUMS_MINOR_VERSION, LIBEXADRUMS_PATCH_VERSION) << "\n";
				std::cout << "using gtkmm version " << VersionToStr(GTKMM_MAJOR_VERSION, GTKMM_MINOR_VERSION, GTKMM_MICRO_VERSION) << std::endl;
				return 0;
			}

			if(!configEntry.second.empty())
			{
				std::cout << "Loading configuration from folder " << configEntry.second << std::endl;
				this->userPath = fs::path{configEntry.second};
			}

			// Activate the app
			app->activate();

			return 0;
		}

		bool IsInstalledForUser()
		{
			return fs::is_directory(userPath);
		}

		bool InstallForUser()
		{
			if(IsInstalledForUser())
			{
				return false;
			}

			fs::create_directory(userPath);
			fs::copy(RootDataPath(), UserDataPath(), fs::copy_options::recursive);

			return true;
		}

		// Paths
		fs::path UserPath()
		{
			return userPath;
		}

		fs::path RootPath()
		{
			return rootPath;
		}

		fs::path UserDataPath()
		{
			return userPath/"Data";
		}

		fs::path RootDataPath()
		{
			return rootPath/"Data";
		}

		fs::path UiPath()
		{
			return rootPath/"Ui/Ui.glade";
		}

	private:

		template <typename T>
		std::pair<Glib::OptionEntry, T> MakeOption(const std::string& ln, char sn, const std::string& desc)
		{
			Glib::OptionEntry optionEntry;
			optionEntry.set_long_name(ln.data());
			optionEntry.set_short_name(sn);
			optionEntry.set_description(desc);

			return std::make_pair(optionEntry, T{});
		}

		fs::path userPath = fs::path{std::getenv("HOME")}/".eXaDrums";
		const fs::path rootPath{"/usr/share/eXaDrums"};

	};

}


#endif /* SOURCE_EXADRUMSCONFIG_H_ */
