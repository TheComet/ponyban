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
		"dependencies/CHOCOBUN-1.0.0/include",

		"include"
	}
	
	-- lib include directories
	libSearchDirs = {
		rootDir_SFML .. "/lib",
		"dependencies/CHOCOBUN-1.0.0/lib"
	}
	
	-- link libraries
	linklibs_ponyban_debug = {
		"chocobun-core_d"
	}
	linklibs_ponyban_release = {
		"chocobun-core"
	}

elseif os.get() == "linux" then

	-- header search directories
	headerSearchDirs = {
		"dependencies/CHOCOBUN-1.0.0/include",
		"/usr/include",
		"/usr/local/include/",

		"include"
	}

	-- lib include directories
	libSearchDirs = {
		"dependencies/CHOCOBUN-1.0.0/lib",
		"/usr/lib",
		"/usr/local/lib"
	}

	-- link libraries
	linklibs_ponyban_debug = {
		"chocobun-core",
		"sfml-system",
		"sfml-window",
		"sfml-graphics"
	}
	linklibs_ponyban_release = {
		"chocobun-core"
	}
	
-- MAAAC
elseif os.get() == "macosx" then

	-- header search directories
	headerSearchDirs = {
		"dependencies/CHOCOBUN-1.0.0/include",
		"/usr/include/",

		"include"
	}

	-- lib include directories
	libSearchDirs = {
		"dependencies/CHOCOBUN-1.0.0/lib",
		"/usr/local/lib",
		"/usr/lib"
	}

	-- link libraries
	linklibs_ponyban_debug = {
		"chocobun-core"
	}
	linklibs_ponyban_release = {
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
	-- Ponyban core
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
			links (linklibs_ponyban_debug)
			
		configuration "Release"
			targetdir "bin/release"
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}
			libdirs (libSearchDirs)
			links (linklibs_ponyban_release)	
