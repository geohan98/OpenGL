workspace "OpenGL"
	architecture "x64"
	startproject "OpenGL"
	systemversion "latest"
	cppdialect "C++17"

	configurations
	{
		"Debug"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}"

project "OpenGL"
	location "OpenGL"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("build/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/include/**.h",
		"%{prj.name}/src/**.cpp",
		"Vendor/GLAD/src/glad.c"
	}

	includedirs
	{
		"vendor/GLFW64/include",
		"vendor/Glad/include",
		"%{prj.name}/include"
	}
	
	libdirs { "vendor/GLFW64/lib" }
	
	links 
	{
		"GLFW3",
	}
	
	