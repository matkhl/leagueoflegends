#pragma once

typedef unsigned long long QWORD;

#define IsValidPtr(addr) ((QWORD)(addr) > 0x100 && (QWORD)(addr) < 0x00007fffffffffff  && !IsBadReadPtr(addr, sizeof(PVOID)))

#define NOP 0x90

#define PI 3.1415927f

#define SCREENWIDTH ::GetSystemMetrics(SM_CXSCREEN)
#define SCREENHEIGHT ::GetSystemMetrics(SM_CYSCREEN)