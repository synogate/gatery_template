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

    group ""
        project "gatery-template"
            kind "ConsoleApp"
            links { "gatery_core", "gatery_scl" }
            files { "source/**" }
            includedirs { 
                "%{prj.location}/gatery/source", 
                "%{prj.location}/gatery/source/gen/"
            }

            filter "system:linux"
                links { 
                    "boost_unit_test_framework", 
                    "boost_program_options", 
                    "dl" 
                }

    group "gatery"
        include "libs/gatery/source/premake5.lua"

    project "*"
        GateryWorkspaceDefaults()