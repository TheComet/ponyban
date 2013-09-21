-------------------------------------------------------------------
-- Ponyban build script
-------------------------------------------------------------------

-- Windows specific settings
if os.get() == "windows" then

	-- root directories of required libraries
	local rootDir_SFML = "$(SFML_HOME)"
	
	-- global header include directories
	headerSearchDirs = {
		rootDir_SFML .. "/include",
		"dependencies/CHOCOBUN-1.0.0/include"
	}
	
	-- lib include directories
	libSearchDirs = {
		rootDir_SFML .. "/lib",
		"dependencies/CHOCOBUN-1.0.0/lib"
	}
	
	-- link libraries
	linklibs_chocobun_core_debug = {
	}
	linklibs_chocobun_core_release = {
	}
	linklibs_chocobun_console_debug = {
		"chocobun-core_d"
	}
	linklibs_chocobun_console_release = {
		"chocobun-core"
	}

elseif os.get() == "linux" then

	-- header search directories
	headerSearchDirs = {
		"dependencies/CHOCOBUN-1.0.0/include",
		"/usr/include",
		"/usr/local/include/"
	}

	-- lib include directories
	libSearchDirs = {
		"dependencies/CHOCOBUN-1.0.0/lib",
		"/usr/lib",
		"/usr/local/lib"
	}

	-- link libraries
	linklibs_chocobun_core_debug = {
	}
	linklibs_chocobun_core_release = {
	}
	linklibs_chocobun_console_debug = {
		"chocobun-core"
	}
	linklibs_chocobun_console_release = {
		"chocobun-core"
	}
	
-- MAAAC
elseif os.get() == "macosx" then

	-- header search directories
	headerSearchDirs = {
		"dependencies/CHOCOBUN-1.0.0/include",
		"/usr/include/"
	}

	-- lib include directories
	libSearchDirs = {
		"dependencies/CHOCOBUN-1.0.0/lib",
		"/usr/local/lib",
		"/usr/lib"
	}

	-- link libraries
	linklibs_chocobun_core_debug = {
	}
	linklibs_chocobun_core_release = {
	}
	linklibs_chocobun_console_debug = {
		"chocobun-core"
	}
	linklibs_chocobun_console_release = {
		"chocobun-core"
	}

-- OS couldn't be determined
else
	printf( "FATAL: Unable to determine your operating system!" )
end

-------------------------------------------------------------------
-- Ponyban Solution
-------------------------------------------------------------------

solution "Ponyban"
	configurations { "Debug", "Release" }
	location "build"
	
	-------------------------------------------------------------------
	-- Global #defines
	-------------------------------------------------------------------
	
	-- Windows specific
	if os.get() == "Windows" then
		defines {
			"WIN32",
			"_WINDOWS"
		}
	end
	
	-- Project #defines
	defines {
		"CHOCOBUN_CORE_DYNAMIC"
	}
	
	-------------------------------------------------------------------
	-- Chocobun core
	-------------------------------------------------------------------
	
	project "ponyban"
		kind "ConsoleApp"
		language "C++"
		files {
			"src/**.cpp",
			"include/**.hpp"
		}
		
		includedirs (headerSearchDirs)
		
		configuration "Debug"
			targetdir "bin/debug"
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			libdirs (libSearchDirs)
			links (linklibs_chocobun_core_debug)
			
		configuration "Release"
			targetdir "bin/release"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_chocobun_core_release)	
