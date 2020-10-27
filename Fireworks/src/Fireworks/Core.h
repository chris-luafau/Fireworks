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

#ifdef FZ_ENABLE_ASSERTS
	#define FZ_ASSERT(x, ...) { if(!(x)) { FZ_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FZ_CORE_ASSERT(x, ...) { if(!(x)) { FZ_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FZ_ASSERT(x, ...)
	#define FZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

