workspace "gatery-template"
    configurations { "Debug", "Release" }
    architecture "x64"
    symbols "On"
    flags { "MultiProcessorCompile" }
    cppdialect "C++latest"
    startproject "gatery-template"

    targetdir "%{wks.location}/bin/%{cfg.system}-%{cfg.architecture}-%{cfg.longname}"
    objdir "%{wks.location}/obj/%{cfg.system}-%{cfg.architecture}-%{cfg.longname}"

    defines "NOMINMAX"

    filter "configurations:Debug"
        runtime "Debug"

    filter "configurations:Release"
        runtime "Release"
        optimize "On"

    filter "system:linux"
        buildoptions { "-std=c++2a", "-fcoroutines"}

    project "gatery-template"
        kind "ConsoleApp"
        links { "gatery"}
        files { "source/**" }
        includedirs { 
            "%{prj.location}/libs/gatery/source",
        }

        filter "system:linux"
            links { 
                "boost_unit_test_framework", 
                "boost_program_options", 
                "dl" 
            }


include "libs/gatery/source/premake5.lua"
-- Enable to also build unit tests of gatery
-- include "libs/gatery/tests/premake5.lua"