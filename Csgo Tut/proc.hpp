#pragma once 

#include "Windows.h"
#include "TlHelp32.h"
#include <vector>

uintptr_t GetModBase(DWORD procId, const wchar_t* modName); //creating our function


DWORD GetProcId(const wchar_t* procName); //creating our function
