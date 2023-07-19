#pragma once

typedef unsigned long long QWORD;

#define IsValidPtr(addr) ((QWORD)(addr) > 0x100 && (QWORD)(addr) < 0x00007fffffffffff  && !IsBadReadPtr(addr, sizeof(PVOID)))

#define NOP 0x90

#define PI 3.1415927f

#define CHAT_COLOR(color, text) std::string(SP_STRING("<font color='") + std::string(SP_STRING(color)) + SP_STRING("'>") + std::string(SP_STRING(text)) + SP_STRING("</font>"))
#define CHAT_COLOR_DT(color, text) std::string(SP_STRING("<font color='") + std::string(SP_STRING(color)) + SP_STRING("'>") + std::string(text) + SP_STRING("</font>"))