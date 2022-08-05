#include "proc.hpp"

DWORD GetProcId(const wchar_t* modName) //defining our function
{
	DWORD procId = 0; //declaring procid
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0); //takes a "snapshot" or list of every proccess running on your computer
	if (hSnap != INVALID_HANDLE_VALUE) //makes sure that the snapshot completed
	{
		PROCESSENTRY32 procEntry; //creates an entry into our list of procceses
		procEntry.dwSize = sizeof(procEntry); //gets the size in bytes of our proccess entry
		if (Process32First(hSnap, &procEntry)) //gets the first process in our list
		{
			do
			{
				if (!_wcsicmp(procEntry.szExeFile, modName)) //checks if the name of the process is the one we want
				{
					procId = procEntry.th32ProcessID; //if it is we get the proccess id of it and store it in procId
					break;
				}
			} while (Process32Next(hSnap, &procEntry)); //loops through processes until we find the one we want
		}
	}
	CloseHandle(hSnap); //closes the handle to provent memory leaks
	return procId; //returns the proccess id
}

uintptr_t GetModBase(DWORD procId, const wchar_t* modName) //defining our function
{
	uintptr_t modBase = 0; //declaring modBase
	HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId); // takes a snapshot of all the modules contained in assault cube
	if (hSnap != INVALID_HANDLE_VALUE) //checks if snapshot worked
	{
		MODULEENTRY32 modEntry; //creates an entry into our list of modules
		modEntry.dwSize = sizeof(modEntry); //gets the size in bytes of our module entry
		if (Module32First(hSnap, &modEntry)) //gets the first module in the list
		{
			do
			{
				if (!_wcsicmp(modEntry.szModule, modName)) //compares the name of the module to the one we want
				{
					modBase = (uintptr_t)(modEntry.modBaseAddr); //if its the same name as the one we want it will store the address of the module in modBase
					break;
				}
			} while (Module32Next(hSnap, &modEntry)); //continues to loop through our modules until we find the one we want
		}
	}
	CloseHandle(hSnap); //closes handle to provent memory leak
	return modBase; //returns modBase
}