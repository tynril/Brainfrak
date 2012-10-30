solution "Brainfrak"
	configurations { "Debug", "Release" }
	location "project"
	
	project "Brainfrak"
		kind "ConsoleApp"
		language "C++"
		files { "src/**.cc", "src/**.h" }
		debugdir "scripts"
		debugargs { "mandelbrot.b" }
		
		configuration "Debug"
			defines { "DEBUG" }
			flags { "Symbols" }
			targetdir "bin/Debug"
			targetsuffix "d"
		
		configuration "Release"
			defines { "NDEBUG" }
			flags { "Optimize" }
			targetdir "bin/Release"
