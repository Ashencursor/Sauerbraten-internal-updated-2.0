#pragma once
#include "../pch.h"
#include <unordered_map>
#include <algorithm>
#include <ranges>
#include <type_traits>
#include "../globals/globals.h"

//WINAPI is defined as __stdcall, which indicates that the function uses the stdcall calling convention



union eflags {
	struct {
		uint32_t carry_flag : 1;
		uint32_t reserved1 : 1;
		uint32_t parity_flag : 1;
		uint32_t reserved2 : 1;
		uint32_t adjust_flag : 1;
		uint32_t reserved3 : 1;
		uint32_t zero_flag : 1;
		uint32_t sign_flag : 1;
		uint32_t trap_flag : 1;
		uint32_t interrupt_flag : 1;
		uint32_t direction_flag : 1;
		uint32_t overflow_flag : 1;
		uint32_t io_privilege_level : 2;
		uint32_t nested_task : 1;
		uint32_t reserved4 : 1;
		uint32_t resume : 1;
		uint32_t virtual_8086 : 1;
		uint32_t alignment_check : 1;
		uint32_t virtual_interrupt : 1;
		uint32_t virtual_interrupt_pending : 1;
		uint32_t cpuid : 1;
		uint32_t reserved5 : 10;
	};
	uint32_t value;
};

namespace Hook
{
	inline std::unordered_map<uintptr_t, std::pair<uintptr_t, bool>> hooks;
	inline void* m_handle;

	template<typename R, typename ...TS>
	inline R call(uintptr_t target, TS... args)
	{
		DWORD oldprotect;
		auto it = hooks.find(target);

		if (it == hooks.end()) {
			std::cout << "No hooks found\n";
		}
		it->second.second = true;// Check 

		if constexpr (std::is_void_v<R>) { 
			VirtualProtect(reinterpret_cast<void*>(target), 0x1000, PAGE_EXECUTE_READ, &oldprotect);
			reinterpret_cast<R(*)(TS...)>(target)(args...);
			VirtualProtect(reinterpret_cast<void*>(target), 0x1000, oldprotect, &oldprotect);
			it->second.second = false;
		} 
		else {
			VirtualProtect(reinterpret_cast<void*>(target), 0x1000, PAGE_EXECUTE_READ, &oldprotect);
			R buffer = reinterpret_cast<R(*)(TS...)>(target)(args...);
			VirtualProtect(reinterpret_cast<void*>(target), 0x1000, oldprotect, &oldprotect);
			it->second.second = false;
			return buffer;
		}
		
	}

	inline void hook(uintptr_t target, uintptr_t detour) {
		hooks.insert({ target, {detour,false} });// {key: value} { target: detour }

		DWORD oldprotect;
		VirtualProtect(reinterpret_cast<void*>(target), 0x1000, PAGE_EXECUTE_READ | PAGE_GUARD, &oldprotect);
	}

	inline void unhook(uintptr_t target) {
		DWORD oldprotect;
		VirtualProtect(reinterpret_cast<void*>(target), 0x1000, PAGE_EXECUTE_READ, &oldprotect);
		hooks.erase(target);//Specified entry is eraseed
	}

	// requires a global function pointer, not a class member function pointer.
	inline LONG CALLBACK MyVectoredExceptionHandler(_EXCEPTION_POINTERS* ExceptionInfo)
	{
		if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_GUARD_PAGE) {
			//std::cout << "if: " << ExceptionInfo->ExceptionRecord->ExceptionAddress << std::endl;
			auto it = hooks.find(reinterpret_cast<uintptr_t>(ExceptionInfo->ExceptionRecord->ExceptionAddress));
			if (it == hooks.end())
				return EXCEPTION_CONTINUE_EXECUTION;

			ExceptionInfo->ContextRecord->Rip = it->second.first;//.first is the adr of the detour func

			eflags flags{.value = ExceptionInfo->ContextRecord->EFlags};
			flags.trap_flag = true;
			ExceptionInfo->ContextRecord->EFlags = flags.value;
		}
		else if (ExceptionInfo->ExceptionRecord->ExceptionCode == EXCEPTION_SINGLE_STEP) {
			//std::cout << "else if: " << ExceptionInfo->ExceptionRecord->ExceptionAddress << std::endl;
			std::ranges::for_each(hooks, [](auto& p) {
				auto [target, detour] = p;
				auto [detourAddress, inuse] = detour;
				if (inuse)
					return;
				
				DWORD oldprotect;
				VirtualProtect(reinterpret_cast<void*>(target), 0x1000, PAGE_EXECUTE_READ | PAGE_GUARD, &oldprotect);
				});
		}
		return EXCEPTION_CONTINUE_EXECUTION;
	}


	
	//Constructor
	inline void Hook()
	{
		m_handle = AddVectoredExceptionHandler(1, MyVectoredExceptionHandler);
	}
	//Destructor
	inline void dHook()
	{
		RemoveVectoredExceptionHandler(m_handle);
		hooks.clear();//All map entries are cleared
	}
}




// Test function
inline void test(HDC Hdc) {
	std::cout << "Detour function\n";

	Hook::call<void>(Globals::Hook::swapBuffersPtr, Hdc);
}
