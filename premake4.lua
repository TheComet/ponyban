--------------------------------------------------------------------
-- Ponyban build script
-------------------------------------------------------------------

-- Windows specific settings
if os.get() == "windows" then

	-- root directories of required libraries
	local rootDir_SFML = "$(SFML_HOME)"
	
	-- global header include directories
	headerSearchDirs = {
		rootDir_SFML .. "/include",
		"chocobun/chocobun-core/",

		"ponyban"
	}
	
	-- lib include directories
	libSearchDirs = {
		rootDir_SFML .. "/lib",
		"chocobun/chocobun-core/bin/debug",
		"chocobun/chocobun-core/bin/release",
		"chocobun/chocobun-core/bin/lib"
	}
	
	-- link libraries
	linklibs_ponyban_debug = {
		"chocobun-core_d",
		"sfml-system-d",
		"sfml-window-d",
		"sfml-graphics-d"
	}
	linklibs_ponyban_release = {
		"chocobun-core",
		"sfml-system",
		"sfml-window",
		"sfml-graphics"
	}

elseif os.get() == "linux" then

	-- header search directories
	headerSearchDirs = {
		"dependencies/chocobun/chocobun-core",
		"/usr/include",
		"/usr/local/include/",

		"ponyban"
	}

	-- lib include directories
	libSearchDirs = {
		"dependencies/chocobun/bin/debug",
		"bin/debug",
		"/usr/lib",
		"/usr/local/lib"
	}

	-- link libraries
	linklibs_ponyban_debug = {
		"chocobun-core_d",
		"sfml-system",
		"sfml-window",
		"sfml-graphics"
	}
	linklibs_ponyban_release = {
		"chocobun-core",
		"sfml-system",
		"sfml-window",
		"sfml-graphics"
	}
	
-- MAAAC
elseif os.get() == "macosx" then

	-- header search directories
	headerSearchDirs = {
		"dependencies/chocobun/chocobun-core",
		"/usr/include/",

		"include"
	}

	-- lib include directories
	libSearchDirs = {
		"dependencies/chocobun/bin/debug",
		"bin/debug",
		"/usr/local/lib",
		"/usr/lib"
	}

	-- link libraries
	linklibs_ponyban_debug = {
		"chocobun-core_d",
		"sfml-system",
		"sfml-window",
		"sfml-graphics"
	}
	linklibs_ponyban_release = {
		"chocobun-core",
		"sfml-system",
		"sfml-window",
		"sfml-graphics"
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
	if os.get() == "windows" then
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

	project "chocobun-core"
		kind "SharedLib"
		language "C++"
		files {
			"dependencies/chocobun/chocobun-core/**.hpp",
			"dependencies/chocobun/chocobun-core/**.cpp"
		}

		includedirs (headerSearchDirs)

		configuration "Debug"	
			targetdir "bin/debug"
			targetsuffix "_d"
			if os.get() == "windows" then
				implibdir "bin/lib"
			end
			defines {
				"DEBUG",
				"_DEBUG"
			}
			flags {
				"Symbols"
			}
			
		configuration "Release"
			targetdir "bin/release"
			if os.get() == "windows" then
				implibdir "bin/lib"
			end
			defines {
				"NDEBUG"
			}
			flags {
				"Optimize"
			}

	-------------------------------------------------------------------
	-- Ponyban
	-------------------------------------------------------------------
	
	project "ponyban"
		kind "ConsoleApp"
		language "C++"
		files {
			"ponyban/**.cpp",
			"ponyban/**.hpp"
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
