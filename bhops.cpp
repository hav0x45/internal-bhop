#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <offsets/offsets.cpp>
#include <offsets/buttons.cpp>
#include <offsets/client_dll.cpp>
#include <cstdint>
#include <chrono>
#include <thread>

// Hack function
void BunnyHop(const HMODULE instance) noexcept
{
	const auto client = reinterpret_cast<std::uintptr_t>(GetModuleHandleA("client.dll"));
	
	// Hack loop
	while (!GetAsyncKeyState(VK_END))
	{
		const auto localPlayer = *reinterpret_cast<std::uintptr_t*>(client+cs2_dumper::offsets::client_dll::dwLocalPlayerPawn);
		const auto flags = localPlayer+cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags;
		bool OnGround = flags & (1 << 0);

		if (OnGround && GetAsyncKeyState(VK_SPACE)) {
			*reinterpret_cast<std::uintptr_t*>(client + cs2_dumper::buttons::jump) = 65537;
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
			*reinterpret_cast<std::uintptr_t*>(client + cs2_dumper::buttons::jump) = 256;
		}
	}
	// Uninject
	FreeLibraryAndExitThread(instance, 0);
}

// Entry point
int __stdcall DllMain(const HMODULE instance, const std::uintptr_t reason, const void* reserved) {
	
	// DLL_PROCESS_ATTACH
	if (reason == 1)
	{
		DisableThreadLibraryCalls(instance);

		// Create hack thread
		const auto thread = CreateThread(
			nullptr,
			0,
			reinterpret_cast<LPTHREAD_START_ROUTINE>(BunnyHop),
			instance,
			0,
			nullptr
		);

		if (thread) {
			CloseHandle(thread);
		}
	}

	return 1;
}