#pragma once

namespace functions
{
	template<typename Function> Function CallVirtual(PVOID base, QWORD index)
	{
		QWORD** VTablePointer = (QWORD**)base;
		QWORD* VTableFunctionBase = *VTablePointer;
		QWORD dwAddress = VTableFunctionBase[index];
		return (Function)(dwAddress);
	}

	void Init();

	std::string GetHexString(QWORD hexNumber);

	Vector3 ReadVector3(QWORD offset);
	void WriteVector3(QWORD offset, Vector3 vector);

	void PrintChat(std::string text);
	void PrintChat(int number);
	void PrintChat(float number);
	void PrintChat(void* address);

	float GetGameTime();
	std::string ConvertTime(float seconds);

	bool IsGameFocused();
	bool IsChatOpen();

	Vector2 GetMousePos();
	Vector3 GetMouseWorldPos();

	Vector2 WorldToScreen(Vector3 in);
	Vector3 GetBaseDrawPosition(Object* obj);
	Vector2 GetHpBarPosition(Object* obj);

	void IssueOrder(Vector2 pos);
	void IssueMove(Vector2 pos);
	void CastSpell(int spellId, Object* target, Vector3 pos);

	bool CanSendInput();

	void AttackObject(Object* obj);
	void MoveToMousePos();
}