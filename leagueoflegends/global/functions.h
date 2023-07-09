#pragma once

namespace functions
{
	extern void* spoof_trampoline;

	void Init();

	void SaveSettings();
	void LoadSettings();

	template<typename Function> Function CallVirtual(PVOID base, QWORD index)
	{
		QWORD** VTablePointer = (QWORD**)base;
		QWORD* VTableFunctionBase = *VTablePointer;
		QWORD dwAddress = VTableFunctionBase[index];
		return (Function)(dwAddress);
	}

	void RefreshArrays();
	bool IsGameFocused();
	float GetGameTime();

	Vector3 ReadVector3(QWORD offset);

	Vector2 GetMousePos();

	Vector3 GetBaseDrawPosition(Object* obj);
	Vector2 WorldToScreen(Vector3 in);

	void IssueOrder();
}