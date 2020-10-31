
workspace "Fireworks"
	architecture "x64"

	configurations {
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to root folder (solution directory).
-- We will add more as the projects grows.
IncludeDir = {}
IncludeDir["GLFW"] = "Fireworks/vendor/GLFW/include"
IncludeDir["Glad"] = "Fireworks/vendor/GLAD/include"
IncludeDir["ImGui"] = "Fireworks/vendor/imgui"

include "Fireworks/vendor/GLFW"
include "Fireworks/vendor/Glad"
include "Fireworks/vendor/ImGui"

project "Fireworks"
	location "Fireworks"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fzpch.h"
	pchsource "Fireworks/src/fzpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		--"%{prj.name}/Fireworks",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"FZ_PLATFORM_WINDOWS",
			"FZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}
		
		postbuildcommands {
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "FZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FZ_DIST"
		runtime "Release"
		optimize "On"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Fireworks/vendor/spdlog/include",
		"Fireworks/src"
	}

	links {
		"Fireworks"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines {
			"FZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FZ_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "FZ_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "FZ_DIST"
		runtime "Release"
		optimize "On"