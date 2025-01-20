workspace "rtinaweekend"
    configurations { "Debug", "Release" }
    platforms { "Win64" }

project "rtinaweekend"
    kind "ConsoleApp"
    language "C++"
    targetdir "bin/%{cfg.buildcfg}"
    cppdialect "C++23"

    files { "include/**.h", "include/**.hpp", "src/**.c", "src/**.cpp" }

    includedirs { "include" }
    includedirs { "src" }

    filter "configurations:Debug"
    defines { "DEBUG" }
    symbols "On"

    filter "configurations:Release"
    defines { "NDEBUG" }
    optimize "On"