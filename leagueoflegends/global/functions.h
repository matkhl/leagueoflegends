#pragma once

namespace functions
{
	extern void* spoof_trampoline;

	template<typename Function> Function CallVirtual(PVOID base, QWORD index)
	{
		QWORD** VTablePointer = (QWORD**)base;
		QWORD* VTableFunctionBase = *VTablePointer;
		QWORD dwAddress = VTableFunctionBase[index];
		return (Function)(dwAddress);
	}

	void Init();

	std::string GetHexString(QWORD hexNumber);
	std::string CapitalizeFirstLetter(std::string str);

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

	Object* GetSelectedObject();
	unsigned int GetCollisionFlags(Vector3 pos);
	bool IsBrush(Vector3 pos);
	bool IsWall(Vector3 pos);
	bool IsAttackWindupSpell(int spellId);

	void TryRightClick(Vector2 pos);
	void IssueOrder(Vector2 pos);
	void IssueMove(Vector2 pos);
	void CastSpell(int spellId, Vector3 pos);

	bool CanSendInput();

	void AttackObject(Object* obj);
	void MoveToMousePos();
}