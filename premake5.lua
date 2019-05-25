workspace "Graphics-Sandbox"
	architecture "x86_64"
	configurations { "Debug", "Develop", "Release" }
	startproject "Graphics-Sandbox"

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

project "Graphics-Sandbox"
	location "Graphics-Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "On"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch/pch.cpp"

	files {
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs {
		"%{prj.name}/src/pch/",
		"%{prj.name}/include/",
		"%{prj.name}/extlib/GLFW/include/",
		"%{prj.name}/extlib/GLM/include/"
	}

	libdirs {
		"%{prj.name}/extlib/GLFW/"
	}

	links {
		"glad",
		"OpenGL32",
		"glfw3"
	}

	filter "system:windows"
		systemversion "latest"

	filter { "configurations:Debug or Develop" }
		includedirs {
			"%{prj.name}/extlib/Glad/Glad-debug/include/"
		}
		libdirs {
			"%{prj.name}/extlib/Glad/Glad-debug/"
		}

	filter { "configurations:Release" }
		includedirs {
			"%{prj.name}/extlib/Glad/Glad/include/"
		}
		libdirs {
			"%{prj.name}/extlib/Glad/Glad/"
		}

	filter "configurations:Debug"
		defines "DMN_DEBUG"
		symbols "On"
		optimize "Off"
		runtime "Debug"
		
	filter "configurations:Develop"
		defines "DMN_DEVELOP"
		symbols "Off"
		optimize "On"
		runtime "Release"

	filter "configurations:Release"
		defines "DMN_RELEASE"
		symbols "Off"
		optimize "Full"
		runtime "Release"
