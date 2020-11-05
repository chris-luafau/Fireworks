
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
IncludeDir["glm"] = "Fireworks/vendor/glm"

include "Fireworks/vendor/GLFW"
include "Fireworks/vendor/Glad"
include "Fireworks/vendor/imgui"

project "Fireworks"
	location "Fireworks"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "fzpch.h"
	pchsource "Fireworks/src/fzpch.cpp"

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines {
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs {
		"%{prj.name}/vendor/spdlog/include",
		"%{prj.name}/src",
		--"%{prj.name}/Fireworks",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links {
		"GLFW",
		"Glad",
		"ImGui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"FZ_PLATFORM_WINDOWS",
			"FZ_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "FZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FZ_DIST"
		runtime "Release"
		optimize "on"


project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir("bin/" .. outputdir .. "/%{prj.name}")
	objdir("bin-int/" .. outputdir .. "/%{prj.name}")

	files {
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"Fireworks/vendor/spdlog/include",
		"Fireworks/src",
		"Fireworks/vendor",
		"%{IncludeDir.glm}"
	}

	links {
		"Fireworks"
	}

	filter "system:windows"
		systemversion "latest"

		defines {
			"FZ_PLATFORM_WINDOWS"
		}

	filter "configurations:Debug"
		defines "FZ_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "FZ_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "FZ_DIST"
		runtime "Release"
		optimize "on"
