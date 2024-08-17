#include "pch.h"
#include "hacks/hacks.h"
#include "hook/hook.h"
// dllmain.cpp : Defines the entry point for the DLL application.




BOOL WINAPI newThread(HMODULE hModule) {
    // Attempt to send a message to the console
    AllocConsole(); // Allocate a console for this process
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout); // Redirect stdout to the console

    while (true) {

        Hacks::checkHack();

        
        Sleep(1);
    }

    fclose(f);//what
    FreeConsole();//Detach thread from process
    /*
    the FreeConsole() call at the end of the function is designed to detach the console from the process.
    This means that closing the console window will not immediately terminate the thread.
    Instead, the thread will continue running until it reaches the end of the function,
    at which point it will call FreeLibraryAndExitThread(hModule, 0).
    This function unloads the DLL from the process and terminates the thread.
    */
    FreeLibraryAndExitThread(hModule, 0);//Unloads dll from process and terminates the thread 

    return TRUE;
}

// Entry point for DLL
BOOL APIENTRY DllMain(HMODULE hModule,// Module that is loaded to address space of process. Basically the adr of the dll
    DWORD  ul_reason_for_call,
    void* lpReserved
)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        CreateThread(nullptr, 0, reinterpret_cast<PTHREAD_START_ROUTINE>(newThread), hModule, 0, nullptr);
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

