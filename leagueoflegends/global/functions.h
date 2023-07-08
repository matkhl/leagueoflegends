#pragma once

#include "../stdafx.h"

namespace functions
{
	void SaveSettings();
	void LoadSettings();

	template<typename Function> Function CallVirtual(PVOID base, QWORD index)
	{
		QWORD** VTablePointer = (QWORD**)base;
		QWORD* VTableFunctionBase = *VTablePointer;
		QWORD dwAddress = VTableFunctionBase[index];
		return (Function)(dwAddress);
	}

	Vector3 ReadVector3(QWORD offset);

	Vector3 GetBaseDrawPosition(Object* obj);
	Vector2 WorldToScreen(Vector3 in);

	bool IsGameFocused();
	float GetGameTime();
	void RefreshArrays();
}