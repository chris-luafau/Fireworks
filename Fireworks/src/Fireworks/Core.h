#pragma once

#include <memory>

#ifdef FZ_PLATFORM_WINDOWS
#if FZ_DYNAMIC_LINK
	#ifdef FZ_BUILD_DLL
		#define FIREWORKS_API __declspec(dllexport)
	#else
		#define FIREWORKS_API __declspec(dllimport)
	#endif
#else
	#define FIREWORKS_API
#endif
#else
	#error Fireworks only supports Windows :[
#endif

#ifdef FZ_DEBUG
	#define FZ_ENABLE_ASSERTS
#endif

#ifdef FZ_ENABLE_ASSERTS
	#define FZ_ASSERT(x, ...) { if(!(x)) { FZ_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FZ_CORE_ASSERT(x, ...) { if(!(x)) { FZ_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FZ_ASSERT(x, ...)
	#define FZ_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define FZ_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace Fireworks {
	template<typename T>
	using Scope = std::unique_ptr<T>;

	template<typename T>
	using Ref = std::shared_ptr<T>;
}