#ifndef SOURCE_SYSTEM_H_
#define SOURCE_SYSTEM_H_


#if __has_include(<filesystem>)
	#include <filesystem>
	namespace fs = std::filesystem;
#else
	#include <experimental/filesystem>
	namespace fs = std::experimental::filesystem;
#endif


#include <unistd.h>

inline const static fs::path systemUserPath = fs::path{std::getenv("HOME")}/".eXaDrums";
inline const static fs::path systemRootPath{"/usr/share/exadrums"};
inline const static bool systemIsRoot = getuid() == 0 && geteuid() == 0;

#endif