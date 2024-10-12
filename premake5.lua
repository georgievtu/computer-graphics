workspace "ComputerGraphics"
    configurations { "Debug", "Release" }
    startproject "CG"

    flags { "MultiProcessorCompile" }

    filter "configurations:Debug"
        defines { "DEBUG", "DEBUG_SHADER" }
        symbols "On"

    filter "configurations:Release"
        defines { "RELEASE" }
        optimize "Speed"
        flags { "LinkTimeOptimization" }

project "CG"
    kind "ConsoleApp"
    language "C++"
    cppdialect "C++20"
	architecture "x86_64"

    targetdir "bin/%{cfg.buildcfg}"
    objdir "obj/%{cfg.buildcfg}"

    -- TODO seperate "include/" dir?
    includedirs { "dependencies/GLAD/include/", "dependencies/GLFW/include", "dependencies/GLM/", "dependencies/IMGUI" }

    files { "src/*.cpp", "src/*.h", "resources/**" }

    links { "GLFW", "GLM", "GLAD", "ImGui" }

    filter "system:linux"
        links { "dl", "pthread" }

        defines { "_X11" }

    filter "system:windows"
        defines { "_WINDOWS" }

include "dependencies/glfw.lua"
include "dependencies/glad.lua"
include "dependencies/glm.lua"
include "dependencies/imgui.lua"

