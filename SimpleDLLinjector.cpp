#include <iostream>
#include "Header.h"


int main()
{
    const char* dllPath = "D:\\GitRepos\\FinalFantasy-internal\\x64\\Debug\\FinalFantasy-internal.dll"; // you can change the path o your system
    const wchar_t* ProcessName = L"ff7remake_.exe";


	DWORD procId{ 0 };

	while (!procId)
	{
		procId = GetProcessId(ProcessName);
		Sleep(20);
	}
	
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, 0, procId);

	if (hProc && hProc != INVALID_HANDLE_VALUE)
	{
		void* aloc = VirtualAllocEx(hProc, 0, MAX_PATH, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);

		WriteProcessMemory(hProc, aloc, dllPath, strlen(dllPath) + 1, 0);

		HANDLE hThread = CreateRemoteThread(hProc, 0, 0, (LPTHREAD_START_ROUTINE)LoadLibraryA, aloc, 0, 0);

		if (hThread)
		{
			CloseHandle(hThread);
		}

	}if (hProc)
	{
		CloseHandle(hProc);
	}

}


