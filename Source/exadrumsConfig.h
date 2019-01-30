/*
 * exadrumsConfig.h
 *
 *  Created on: 9 Jun 2018
 *      Author: jeremy
 */

#ifndef SOURCE_EXADRUMSCONFIG_H_
#define SOURCE_EXADRUMSCONFIG_H_

#include <libexadrums/Api/eXaDrums.h>

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

#include <unistd.h>


namespace eXaDrums
{

	constexpr auto EXADRUMS_MAJOR_VERSION = 0;
	constexpr auto EXADRUMS_MINOR_VERSION = 2;
	constexpr auto EXADRUMS_PATCH_VERSION = 0;
	constexpr char VERSION_SEPARATOR[] = ".";

	class Config
	{

	public:

		Config() = default;
		~Config() = default;


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

			// Add reset config entry
			auto resetConfigEntry = MakeOption<bool>("reset-config", 'r', "Reset to default configuration");
			optionGroup.add_entry(resetConfigEntry.first, resetConfigEntry.second);

			// Get arguments
			int argc;
			char** argv = cmd->get_arguments(argc);
			optionContext.parse(argc, argv);

			// Handle results
			if(versionEntry.second)
			{
				std::cout << "eXaDrums version " << ExaDrumsVersion() << "\n\n";
				std::cout << "using libeXaDrums version " << LIBEXADRUMS_VERSION << "\n";
				std::cout << "using gtkmm version " << VersionToStr(GTKMM_MAJOR_VERSION, GTKMM_MINOR_VERSION, GTKMM_MICRO_VERSION) << std::endl;
				return 0;
			}

			if(resetConfigEntry.second)
			{
				std::cout << "This will reset the configuration to defaults. \n Current settings will be lost.\n";
				std::cout << "Do you want to continue? [Y/n] ";

				std::string input;
				std::cin >> input;

				if(std::tolower(input.front()) == 'y')
				{
					ResetConfig();
					std::cout << "The configuration has been reset." << std::endl;
				}

				std::cout << "Do you want to start eXaDrums? [Y/n] ";
				std::cin >> input;

				if(std::tolower(input.front()) != 'y')
				{
					return 0;
				}

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

			// Create directories first
			fs::create_directory(userPath);
			fs::create_directory(UserDataPath());
			fs::create_directory(UserDataPath()/"Kits");
			fs::create_directory(UserDataPath()/"Rec");
			fs::create_directory(UserDataPath()/"SoundBank");
			fs::create_directory(UserDataPath()/"SoundBank/BassDrum");
			fs::create_directory(UserDataPath()/"SoundBank/SnareDrum");
			fs::create_directory(UserDataPath()/"SoundBank/Crash");
			fs::create_directory(UserDataPath()/"SoundBank/HiHat");
			fs::create_directory(UserDataPath()/"SoundBank/Ride");
			fs::create_directory(UserDataPath()/"SoundBank/Tom");

			// Copy configuration files
			copyFiles(rootPath, UserDataPath(), {	fs::path{"alsaConfig.xml"},
													fs::path{"metronomeConfig.xml"},
													fs::path{"sensorsConfig.xml"},
													fs::path{"triggersConfig.xml"}});

			// Install default kit
			copyFiles(rootPath, UserDataPath()/"Kits", { fs::path{"Default.xml"} });
			copyFiles(rootPath, UserDataPath()/"SoundBank/SnareDrum", { fs::path{"Snr_Acou_01.wav"} });
			copyFiles(rootPath, UserDataPath()/"SoundBank/BassDrum", { fs::path{"BD_Acou_01.wav"} });
			copyFiles(rootPath, UserDataPath()/"SoundBank/Crash", { fs::path{"Crash_High.wav"} });
			copyFiles(rootPath, UserDataPath()/"SoundBank/HiHat", { fs::path{"HiHat.wav"} });
			copyFiles(rootPath, UserDataPath()/"SoundBank/Ride", { fs::path{"RideBell.wav"} });
			copyFiles(rootPath, UserDataPath()/"SoundBank/Ride", { fs::path{"RideEdge.wav"} });
			copyFiles(rootPath, UserDataPath()/"SoundBank/Tom", { fs::path{"Tom01.wav"} });
			copyFiles(rootPath, UserDataPath()/"SoundBank/Tom", { fs::path{"Tom03.wav"} });


			return true;
		}

		bool ResetConfig()
		{
			fs::remove_all(userPath);
			InstallForUser();

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

		bool IsRoot() const { return isRoot; }

	private:

		void copyFiles(const fs::path& from, const fs::path& to, const std::vector<fs::path>& files)
		{
			for(const auto& file : files)
			{
				fs::copy_file(from/file, to/file);
			}
		}

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
		const fs::path rootPath{"/usr/share/exadrums"};
		const bool isRoot = getuid() == 0 && geteuid() == 0;

	};

}


#endif /* SOURCE_EXADRUMSCONFIG_H_ */
