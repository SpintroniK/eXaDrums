/*
 * exadrumsConfig.h
 *
 *  Created on: 9 Jun 2018
 *      Author: jeremy
 */

#ifndef SOURCE_EXADRUMSCONFIG_H_
#define SOURCE_EXADRUMSCONFIG_H_

#include "../config.h"
#include <libexadrums/Api/eXaDrums.hpp>
#include <libexadrums/Api/Config/Config_api.hpp>

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

	constexpr char VERSION_SEPARATOR[] = ".";

	class Config
	{

	public:

		Config() = default;
		~Config() = default;

		template <typename... T>
		static auto VersionToStr(const T&... v)
		{
			std::string result = ( (std::to_string(v) + VERSION_SEPARATOR) + ... );
			result.pop_back();
			return result;
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

			// Import config from backup file
			auto importConfigEntry = MakeOption<Glib::ustring>("import-config", 'i', "Import configuration from file");
			optionGroup.add_entry(importConfigEntry.first, importConfigEntry.second);

			// Export config to folder
			auto exportConfigEntry = MakeOption<Glib::ustring>("export-config", 'e', "Export configuration to directory");
			optionGroup.add_entry(exportConfigEntry.first, exportConfigEntry.second);

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
				std::cout << "eXaDrums version " PACKAGE_VERSION "\n\n";
				std::cout << "using libeXaDrums version " << eXaDrumsApi::eXaDrums::GetVersion() << " (compiled against version " << LIBEXADRUMS_VERSION << ")\n";
				std::cout << "using gtkmm version " << VersionToStr(GTKMM_MAJOR_VERSION, GTKMM_MINOR_VERSION, GTKMM_MICRO_VERSION) << std::endl;
				return 0;
			}

			if(resetConfigEntry.second)
			{

				if(AnswerQuestion("This will reset the configuration to defaults. \n Current settings will be lost.\n"
				                  "Do you want to continue? [Y/n] ", "y"))
				{
					ResetConfig();
					std::cout << "The configuration has been reset." << std::endl;
				}

				if(!AnswerQuestion("Do you want to start eXaDrums? [Y/n] ", "y"))
				{
					return 0;
				}

			}

			if(!importConfigEntry.second.empty())
			{

				std::cout << "Imported configuration from file " << importConfigEntry.second << std::endl;
               
                try
                {
                    eXaDrumsApi::Config::ImportConfig(importConfigEntry.second, userPath.string());
                }
                catch(const std::exception& e)
                {
                    std::cerr << e.what() << '\n';
                }

				if(!AnswerQuestion("Do you want to start eXaDrums? [Y/n] ", "y"))
				{
					return 0;
				}

			}

            if(!exportConfigEntry.second.empty())
            {   
				try
				{
					eXaDrumsApi::Config::ExportConfig(userPath.string(), exportConfigEntry.second);
					std::cout << "Configuration exported to " << exportConfigEntry.second << std::endl;
				}
				catch(const std::exception& e)
				{
					std::cerr << e.what() << '\n';
				}

				if(!AnswerQuestion("Do you want to start eXaDrums? [Y/n] ", "y"))
				{
					return 0;
				}
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

		/**
		 * @brief Ask the user a question, and return true if the answer is good (equals expectedAnswer).
		 * 
		 * @param question Question to be submitted to the user.
		 * @param expectedAnswer Expected answer.
		 * @param isCaseSensitive Whether the answer is case sensitive or not.
		 * @return true If the answer is the same as expectedAnswer.
		 * @return false If the answer is not the same as expectedAnswer.
		 */
		bool AnswerQuestion(const std::string& question, const std::string& expectedAnswer, bool isCaseSensitive = false)
		{

			std::cout << question;

			std::string input;
			std::cin >> input;

			if(!isCaseSensitive)
			{
				std::transform(begin(input), end(input), begin(input), [](const auto c){ return std::tolower(c); });
			}

			if(input == expectedAnswer)
			{
				return true;
			}

			return false;
		}

		const fs::path userPath = fs::path{std::getenv("HOME")}/".eXaDrums";
		const fs::path rootPath{"/usr/share/exadrums"};
		const bool isRoot = getuid() == 0 && geteuid() == 0;

	};

}


#endif /* SOURCE_EXADRUMSCONFIG_H_ */
