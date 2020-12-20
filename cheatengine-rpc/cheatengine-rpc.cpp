#include "discord.hpp"

bool keep_update = true;
Discord* g_Discord;
ExportedFunctions Exported;

void UpdateThread()
{
    while(keep_update)
    {
        g_Discord->Update(Exported);
        Sleep(1000);
    }
}

BOOL __stdcall CEPlugin_GetVersion(PPluginVersion pv, int sizeofpluginversion)
{
    pv->version = CESDK_VERSION;
    pv->pluginname = const_cast<char*>("cheatengine-rpc plugin by he4rtbleed [https://github.com/he4rtbleed]");
    return TRUE;
}

BOOL __stdcall CEPlugin_InitializePlugin(PExportedFunctions ef, int pluginid)
{
    Exported = *ef;
    if (Exported.sizeofExportedFunctions != sizeof(Exported))
        return FALSE;

    g_Discord->Initialize();

    CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)UpdateThread, nullptr, 0, nullptr);

	return TRUE;
}

BOOL __stdcall CEPlugin_DisablePlugin(void)
{
    keep_update = false;
    return TRUE;
}

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

