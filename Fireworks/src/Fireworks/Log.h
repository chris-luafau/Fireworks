#pragma once
#pragma warning(disable : 26495 26812 6387 26451 26812)

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Fireworks {

	class FIREWORKS_API Log {
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }

	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

// Core log macros
#define FZ_CORE_TRACE(...)    ::Fireworks::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FZ_CORE_INFO(...)     ::Fireworks::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FZ_CORE_WARN(...)     ::Fireworks::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FZ_CORE_ERROR(...)    ::Fireworks::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FZ_CORE_CRITICAL(...) ::Fireworks::Log::GetCoreLogger()->critical(__VA_ARGS__)

// Client log macros
#define FZ_TRACE(...)         ::Fireworks::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FZ_INFO(...)          ::Fireworks::Log::GetClientLogger()->info(__VA_ARGS__)
#define FZ_WARN(...)          ::Fireworks::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FZ_ERROR(...)         ::Fireworks::Log::GetClientLogger()->error(__VA_ARGS__)
#define FZ_CRITICAL(...)      ::Fireworks::Log::GetClientLogger()->critical(__VA_ARGS__)
