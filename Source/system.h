#ifndef EXADRUMS_SOURCE_SYSTEM_H
#define EXADRUMS_SOURCE_SYSTEM_H

#include <filesystem>

#include <vector>

#include <unistd.h>

namespace fs = std::filesystem;

inline const static fs::path systemUserPath = fs::path{std::getenv("HOME")}/".eXaDrums";
inline const static fs::path systemRootPath{"/usr/share/exadrums"};
inline const static bool systemIsRoot = getuid() == 0 && geteuid() == 0;

// Paths
inline fs::path UserPath()
{
	return systemUserPath;
}

inline fs::path RootPath()
{
	return systemRootPath;
}

inline fs::path RootDataPath()
{
	return systemRootPath/"Data";
}

inline fs::path UiPath()
{
	return systemRootPath/"Ui/Ui.glade";
}

inline bool IsRoot() { return systemIsRoot; }

// Various functions


inline void copyFiles(const fs::path& from, const fs::path& to, const std::vector<fs::path>& files)
{
	for(const auto& file : files)
	{
		fs::copy_file(from/file, to/file);
	}
}

inline bool IsInstalledForUser()
{
	return fs::is_directory(systemUserPath);
}

inline fs::path UserDataPath()
{
	return systemUserPath/"Data";
}

inline bool InstallForUser()
{
	if(IsInstalledForUser())
	{
		return false;
	}

	// Create directories first
	fs::create_directory(systemUserPath);
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
	copyFiles(systemRootPath, UserDataPath(), {	fs::path{"alsaConfig.xml"},
												fs::path{"metronomeConfig.xml"},
												fs::path{"sensorsConfig.xml"},
												fs::path{"triggersConfig.xml"},
												fs::path{"spiDev.xml"}});

	// Install default kit
	copyFiles(systemRootPath, UserDataPath()/"Kits", { fs::path{"Default.xml"} });
	copyFiles(systemRootPath, UserDataPath()/"SoundBank/SnareDrum", { fs::path{"Snr_Acou_01.wav"} });
	copyFiles(systemRootPath, UserDataPath()/"SoundBank/BassDrum", { fs::path{"BD_Acou_01.wav"} });
	copyFiles(systemRootPath, UserDataPath()/"SoundBank/Crash", { fs::path{"Crash_High.wav"} });
	copyFiles(systemRootPath, UserDataPath()/"SoundBank/HiHat", { fs::path{"HiHat.wav"} });
	copyFiles(systemRootPath, UserDataPath()/"SoundBank/Ride", { fs::path{"RideBell.wav"} });
	copyFiles(systemRootPath, UserDataPath()/"SoundBank/Ride", { fs::path{"RideEdge.wav"} });
	copyFiles(systemRootPath, UserDataPath()/"SoundBank/Tom", { fs::path{"Tom01.wav"} });
	copyFiles(systemRootPath, UserDataPath()/"SoundBank/Tom", { fs::path{"Tom03.wav"} });


	return true;
}

inline bool ResetConfig()
{
	fs::remove_all(systemUserPath);
	InstallForUser();

	return true;
}

#endif /* EXADRUMS_SOURCE_SYSTEM_H */
