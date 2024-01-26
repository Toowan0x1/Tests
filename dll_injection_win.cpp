#include <iostream>
#include <windows.h>
#include <psapi.h>

int main()
{
    DWORD processes[1024], bytesReturned;
    if (!EnumProcesses(processes, sizeof(processes), &bytesReturned))
    {
        std::cerr << "Failed to get process information\n";
        return 1;
    }
    int nprocs = bytesReturned / sizeof(DWORD);
    for (int i = 0; i < nprocs; i++)
    {
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processes[i]);
        if (hProcess)
        {
            TCHAR processName[MAX_PATH] = TEXT("<unknown>");
            HMODULE hModule;
            DWORD cbNeeded;
            if (EnumProcessModules(hProcess, &hModule, sizeof(hModule), &cbNeeded))
            {
                GetModuleBaseName(hProcess, hModule, processName, sizeof(processName) / sizeof(TCHAR));
            }
            std::cout << processes[i] << "\t" << processName << std::endl;
            CloseHandle(hProcess);
        }
    }
    return 0;
}

