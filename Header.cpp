#include "Header.h"

DWORD GetProcessId(const wchar_t* ProcName)
{
    DWORD ProcId{ 0 };
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

    if (hSnap != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 procEntry;
        procEntry.dwSize = sizeof(procEntry);

        if (Process32First(hSnap, &procEntry))
        {
            do
            {
                if (!_wcsicmp (procEntry.szExeFile, ProcName) )
                {
                    ProcId = procEntry.th32ProcessID;
                    break;
                }
            } while (Process32Next(hSnap, &procEntry));
        }
    }
    CloseHandle(hSnap);
    return ProcId;
}
