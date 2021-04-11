#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

#define WINVER 0x0601
#define _WIN32_WINNT 0x0601

#include <Shlwapi.h>

#pragma comment(lib, "Shlwapi.lib")

#include "Utils/MemoryMgr.h"
#include "Utils/Trampoline.h"
#include "Utils/Patterns.h"

#include <string>
#include <vector>

static HMODULE hDLLModule;

using namespace std;

void OnInitializeHook()
{
    std::unique_ptr<ScopedUnprotect::Unprotect> Protect = ScopedUnprotect::UnprotectSectionOrFullModule( GetModuleHandle( nullptr ), ".text" );

    using namespace Memory;
    using namespace hook;
    
    // Patterns for all default songs
    vector<pair<string, void*>> songs({
        {"brandnewstage", get_pattern("9C 44 50 42 9C 44 50 42 00 00 82 42", 4)},
        {"butterfly",     get_pattern("9C 44 50 42 00 00 82 42 02 AB 76 42", 4)},
        {"diamond",       get_pattern("00 00 82 42 02 AB 76 42 00 00 80 42", 4)},
        {"hands",         get_pattern("00 00 16 43 A6 BB 16 43 3D 0A 17 43", 4)},
        {"tonight",       get_pattern("00 00 30 42 02 AB 30 42 00 00 34 42", 4)},
        {"yji",           get_pattern("00 00 8C 42 1B EF 8F 42 00 00 96 42", 4)}
    });

    // Obtain a path to the ASI
    wchar_t wcModulePath[MAX_PATH];
    GetModuleFileNameW(hDLLModule, wcModulePath, _countof(wcModulePath) - 3); // Minus max required space for extension
    PathRenameExtensionW(wcModulePath, L".ini");

    LPWSTR INIvalue = (LPWSTR)malloc(32 * sizeof(*INIvalue));

    for (int i = 0; i < songs.size(); i++)
    {
        // Get the replay offsets from INI
        wstring INIoption(songs[i].first.begin(), songs[i].first.end());
        GetPrivateProfileStringW(L"Replay", (LPCWSTR)INIoption.c_str(), L"-1", INIvalue, 32, wcModulePath);

        float value = (float)wcstod((wchar_t*)INIvalue, NULL);

        if (value >= 0)
        {
            VP::Patch<float>(songs[i].second, value);
        }
            
    }
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved)
{
    UNREFERENCED_PARAMETER(lpvReserved);

    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        hDLLModule = hinstDLL;
    }
    return TRUE;
}