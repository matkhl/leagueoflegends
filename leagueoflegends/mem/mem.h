#pragma once

#include "../stdafx.h"

void Patch(BYTE* dst, BYTE* src, unsigned int size);
void Nop(BYTE* dst, unsigned int size);

uintptr_t FindDMAAddy(uintptr_t ptr, std::vector<unsigned int> offsets);