#pragma once
#include "../pch.h"
#include <cstring> // For memcpy


namespace mem
{
	template <size_t N>
	void Patch(uintptr_t target, uint8_t(&originalBytes)[N]) {
		DWORD oldProtect;
		VirtualProtect(reinterpret_cast<void*>(target), N, PAGE_EXECUTE_READWRITE, &oldProtect);

		// Makes OGbytes adr intructions the same as the adr passed before being nopped
		memcpy(originalBytes, reinterpret_cast<void*>(target), N);

		for (int i = 0; i < N; ++i) {
			*reinterpret_cast<uint8_t*>(target + i) = 0x90;
		}

		VirtualProtect(reinterpret_cast<void*>(target), N, oldProtect, &oldProtect);
	}

	template <size_t N>
	void UnPatch(uintptr_t target, const uint8_t(&originalBytes)[N]) {
		DWORD oldProtect;
		VirtualProtect(reinterpret_cast<void*>(target), N, PAGE_EXECUTE_READWRITE, &oldProtect);

		// Makes OGbytes adr intructions the same as the adr passed before being nopped
		memcpy(reinterpret_cast<void*>(target), originalBytes, N);


		VirtualProtect(reinterpret_cast<void*>(target), N, oldProtect, &oldProtect);
	}
}