#pragma once
#include <Windows.h>
#include <TlHelp32.h>
#include <time.h>

#include <discord_register.h>
#include <discord_rpc.h>
#pragma comment (lib, "library/discord-rpc/lib/discord-rpc.lib")

#include "library/cepluginsdk.h"

class Discord
{
private:
	char* get_procname(DWORD pid)
	{
        static char* idle_str = (char*)"Idle";
        if (!pid)
            return idle_str;

        HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
        if (hSnapshot) {
            PROCESSENTRY32 pe32;
            pe32.dwSize = sizeof(PROCESSENTRY32);
            if (Process32First(hSnapshot, &pe32)) {
                do {
                    if (pe32.th32ProcessID == pid)
                        return pe32.szExeFile;
                } while (Process32Next(hSnapshot, &pe32));
            }
            CloseHandle(hSnapshot);
        }
	}

    static int StartTime;
public:
	void Initialize();
	void Update(ExportedFunctions ex);
};