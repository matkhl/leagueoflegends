#include "../stdafx.h"

namespace functions
{
	float lastRefreshTime = 0.0f;
	
	void* spoof_trampoline = 0x0;

	void Init()
	{
		spoof_trampoline = (void*)mem::ScanModInternal((char*)"\xFF\x23", (char*)"xx", (char*)globals::moduleBase);
	}

	std::string GetHexString(QWORD hexNumber)
	{
		std::stringstream ss;
		ss << std::hex << hexNumber;
		return ss.str();
	}

	Vector3 ReadVector3(QWORD offset)
	{
		Vector3 result;
		result.x = *(float*)(offset);
		result.y = *(float*)(offset + 0x4);
		result.z = *(float*)(offset + 0x8);
		return result;
	}

	void WriteVector3(QWORD offset, Vector3 vector)
	{
		*(float*)(offset) = vector.x;
		*(float*)(offset + 0x4) = vector.y;
		*(float*)(offset + 0x8) = vector.z;
	}

	void PrintChat(std::string text)
	{
		typedef void(__thiscall* fnPrintChat)(QWORD* chatClient, const char* message, int colorId);
		fnPrintChat _fnSendChat = (fnPrintChat)(globals::moduleBase + oPrintChat);
		std::string formattedText = "[" + ConvertTime(GetGameTime()) + "] " + text;
		std::string coloredText = CHAT_COLOR_("#" + GetHexString((DWORD)COLOR_GREEN >> 2), formattedText);
		_fnSendChat((QWORD*)(*(QWORD*)(globals::moduleBase + oChatInstance)), coloredText.c_str(), 0);
	}

	void PrintChat(int number)
	{
		PrintChat(std::to_string(number));
	}

	void PrintChat(float number)
	{
		PrintChat(std::to_string(number));
	}

	void PrintChat(void* address)
	{
		PrintChat(GetHexString((QWORD)address));
	}

	float GetGameTime()
	{
		return *(float*)(globals::moduleBase + oGameTime);
	}

	std::string ConvertTime(float seconds) {
		int minutes = (int)(seconds / 60);
		seconds = fmod(seconds, 60);
		int secs = (int)seconds;
		int milliseconds = round((seconds - secs) * 1000);

		std::stringstream ss;
		ss << std::setw(2) << std::setfill('0') << minutes << ":";
		ss << std::setw(2) << std::setfill('0') << secs << ".";
		ss << std::setw(3) << std::setfill('0') << milliseconds;

		return ss.str();
	}

	bool IsGameFocused()
	{
		return GetActiveWindow() == hooks::impl::windowDX;
	}

	bool IsChatOpen()
	{
		return *(bool*)(*(QWORD*)(globals::moduleBase + oChatClient) + oChatClientChatOpen);
	}

	Vector2 GetMousePos()
	{
		if (!IsGameFocused()) return Vector2();
		POINT curMouse;
		bool getMouse = GetCursorPos(&curMouse);
		return Vector2(curMouse.x, curMouse.y);
	}

	Vector3 GetMouseWorldPos()
	{
		return ReadVector3((QWORD)(*(QWORD*)(*(QWORD*)(globals::moduleBase + oHudInstance) + oHudInstanceInput) + oHudInstanceInputMouseWorldPos));
	}

	Vector2 WorldToScreen(Vector3 in)
	{
		typedef bool(__fastcall* fnWorldToScreen)(QWORD* viewport, Vector3* in, Vector3* out);
		fnWorldToScreen _fnWorldToScreen = (fnWorldToScreen)(globals::moduleBase + oWorldToScreen);
		QWORD* viewport = *(QWORD**)(globals::moduleBase + oViewport);
		Vector3 out;
		_fnWorldToScreen((QWORD*)((QWORD)viewport + oViewportW2S), &in, &out);
		return Vector2(out.x, out.y);
	}

	Vector3 GetBaseDrawPosition(Object* obj)
	{
		typedef bool(__fastcall* fnGetBaseDrawPosition)(QWORD* obj, Vector3* out);
		fnGetBaseDrawPosition _fnGetBaseDrawPosition = (fnGetBaseDrawPosition)(globals::moduleBase + oGetBaseDrawPosition);
		Vector3 out;
		_fnGetBaseDrawPosition((QWORD*)obj, &out);
		return out;
	}
	
	Vector2 GetHpBarPosition(Object* obj)
	{
		Vector3 hpBarPos = obj->GetPosition();
		const float hpBarHeight = *(float*)(obj->GetCharacterData() + oObjCharDataDataSize) * obj->GetScale();
		hpBarPos.y += hpBarHeight;

		auto screenPos = WorldToScreen(hpBarPos);
		const auto zoomInstance = *(QWORD*)(globals::moduleBase + oZoomInstance);
		const float maxZoom = *(float*)(zoomInstance + oZoomInstanceMaxZoom);
		float currentZoom = *(float*)(*(QWORD*)(*(QWORD*)(globals::moduleBase + oHudInstance) + oHudInstanceCamera) + oHudInstanceCameraZoom);
		float zoomDelta = maxZoom / currentZoom;

		screenPos.y -= (((globals::windowHeight) * 0.00083333335f * zoomDelta) * hpBarHeight);
		 
		return screenPos;
	}

	void TryRightClick(Vector2 pos)
	{
		*(float*)((QWORD)globals::localPlayer + oObjIssueOrderFloatCheck1) = 0.0f;
		*(float*)((QWORD)globals::localPlayer + oObjIssueOrderFloatCheck2) = 0.0f;
		*(DWORD*)((QWORD)globals::localPlayer + oObjIssueOrderCheck) = 0x0;

		typedef bool(__fastcall* fnTryRightClick)(QWORD* player, unsigned int* params);
		fnTryRightClick _fnTryRightClick = (fnTryRightClick)(globals::moduleBase + oTryRightClick);

		unsigned int* params = new unsigned int[20];
		params[17] = (int)pos.x;
		params[18] = (int)pos.y;
		params[19] = 2;

		spoof_call(spoof_trampoline, _fnTryRightClick, (QWORD*)globals::localPlayer, params);
	}

	void IssueOrder(Vector2 pos)
	{
		*(float*)((QWORD)globals::localPlayer + oObjIssueOrderFloatCheck1) = 0.0f;
		*(float*)((QWORD)globals::localPlayer + oObjIssueOrderFloatCheck2) = 0.0f;
		*(DWORD*)((QWORD)globals::localPlayer + oObjIssueOrderCheck) = 0x0;

		typedef bool(__fastcall* fnIssueOrder)(QWORD* player, int order, bool isAttackMove, bool isMinion, int screenX, int screenY, int unknown);
		fnIssueOrder _fnIssueOrder = (fnIssueOrder)(globals::moduleBase + oIssueOrder);
		spoof_call(spoof_trampoline, _fnIssueOrder, (QWORD*)globals::localPlayer, 2, false, false, (int)pos.x, (int)pos.y, 0);
	}

	void IssueMove(Vector2 pos)
	{
		typedef bool(__fastcall* fnIssueMove)(QWORD* hudInput, int screenX, int screenY, bool isAttackMove, int zeroOrOne, int order);
		fnIssueMove _fnIssueMove = (fnIssueMove)(globals::moduleBase + oIssueMove);

		spoof_call(spoof_trampoline, _fnIssueMove, (QWORD*)(*(QWORD*)(*(QWORD*)(globals::moduleBase + oHudInstance) + oHudInstanceInput)), (int)pos.x, (int)pos.y, false, 0, 0);
	}

	void CastSpell(int spellId, Object* target, Vector3 pos)
	{
		typedef bool(__fastcall* fnCastSpellWrapper)(QWORD* hudSpellInfo, QWORD* spellInfo);
		fnCastSpellWrapper _fnCastSpellWrapper = (fnCastSpellWrapper)(globals::moduleBase + oCastSpellWrapper);

		if (spellId < 0 || spellId >= 14) return;
		Spell* spell = globals::localPlayer->GetSpellById(spellId);
		SpellInfo* spellInfo = spell->GetSpellInfo();

		if (target && target->GetNetId())
			*(int*)((QWORD)spell->GetSpellInput() + oSpellInputTargetNetId) = target->GetNetId();

		if (pos.x || pos.y || pos.z)
		{
			WriteVector3(((QWORD)spell->GetSpellInput() + oSpellInputStartPos), globals::localPlayer->GetPosition());
			WriteVector3(((QWORD)spell->GetSpellInput() + oSpellInputEndPos), pos);
			WriteVector3(((QWORD)spell->GetSpellInput() + oSpellInputEndPos + sizeof(Vector3)), pos);
			WriteVector3(((QWORD)spell->GetSpellInput() + oSpellInputEndPos + sizeof(Vector3) * 0x2), pos);
		}

		spoof_call(spoof_trampoline, _fnCastSpellWrapper, (QWORD*)(*(QWORD*)(*(QWORD*)(globals::moduleBase + oHudInstance) + oHudInstanceSpellInfo)), (QWORD*)spellInfo);
	}

	bool CanSendInput()
	{
		return globals::localPlayer->IsAlive() && IsGameFocused() && !IsChatOpen();
	}

	void AttackObject(Object* obj)
	{
		if (!CanSendInput()) return;

		Vector3 headPos = obj->GetPosition();
		const float objectHeight = *(float*)(obj->GetCharacterData() + oObjCharDataDataSize) * obj->GetScale();
		headPos.y += objectHeight;

		auto screenPos = WorldToScreen(headPos);
		TryRightClick(screenPos);
	}

	void MoveToMousePos()
	{
		if (!CanSendInput()) return;
		IssueMove(GetMousePos());
	}
}