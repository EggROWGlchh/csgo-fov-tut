#include <iostream>
#include "proc.hpp"

int main()
{
	int newFov = 120; //what we are changing our fov to

	DWORD dwLocalPlayer = 0xDBF4BC; //local player offset
	DWORD m_iDefaultFOV = 0x333C; //fov offset


	DWORD procId = GetProcId(L"csgo.exe"); //get process id of csgo
	uintptr_t clientBase = GetModBase(procId, L"client.dll"); //gets base address of the client.dll module
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, NULL, procId); //get a handle to csgo

	uintptr_t localPlayer; //where we store a pointer to our localplayer address
	ReadProcessMemory(hProc, (LPVOID)(clientBase + dwLocalPlayer), &localPlayer, sizeof(localPlayer), nullptr); //reads the address of localplayer

	WriteProcessMemory(hProc, (LPVOID)(localPlayer + m_iDefaultFOV), &newFov, sizeof(newFov), nullptr); //changes our fov
}