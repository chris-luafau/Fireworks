#pragma once

#ifdef FZ_PLATFORM_WINDOWS
	#ifdef FZ_BUILD_DLL
		#define FIREWORKS_API __declspec(dllexport)
	#else
		#define FIREWORKS_API __declspec(dllimport)
	#endif
#else
	#error Fireworks only supports Windows :[
#endif

