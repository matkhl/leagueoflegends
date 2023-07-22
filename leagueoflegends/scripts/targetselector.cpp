#include "../stdafx.h"

namespace scripts::targetselector
{
	bool ChooseSelectedObject(Object* selectedObject, Object* checkObj)
	{
		return selectedObject == checkObj && SETTINGS_BOOL("targetselector", "always focus selected");
	}

	Object* GetEnemyChampionInRange(float range)
	{
		return GetEnemyChampionInRange(range,
			(globals::localPlayer->GetAttackDamage() > globals::localPlayer->GetAbilityPower()) ? DamageType::Physical : DamageType::Magical);
	}

	Object* GetEnemyChampionInRange(float range, int damageType)
	{
		Object* selectedObject = functions::GetSelectedObject();
		Object* best = nullptr;
		for (Object* obj : *globals::heroManager)
		{
			if (!obj->IsValidTarget()) continue;

			if (!obj->IsInRange(globals::localPlayer->GetPosition(), range)) continue;

			if (ChooseSelectedObject(selectedObject, obj)) return obj;
				
			if (!best) {
				best = obj;
				continue;
			}

			if (best->GetEffectiveHealth(damageType) > obj->GetEffectiveHealth(damageType)) {
				best = obj;
				continue;
			}
		}

		return best;
	}

	Object* GetObjectInRange(float range, std::string name, std::vector<QWORD> includeFilterTypeHashes, std::vector<QWORD> excludeFilterTypeHashesDetailed, bool isSpecial)
	{
		Object* selectedObject = functions::GetSelectedObject();
		Object* best = nullptr;
		for (Object* obj : *globals::minionManager)
		{
			if (!(isSpecial || obj->IsValidTarget())) continue;

			bool excludeHashMatched = false;
			for (auto hash : excludeFilterTypeHashesDetailed)
			{
				if (obj->GetCharacterData()->GetObjectTypeHashDetailed() == hash)
				{
					excludeHashMatched = true;
					break;
				}
			}
			if (excludeHashMatched) continue;

			bool includeHashMatched = false;
			for (auto hash : includeFilterTypeHashes)
			{
				if (obj->GetCharacterData()->GetObjectTypeHash() == hash)
				{
					includeHashMatched = true;
					break;
				}
			}
			if (includeFilterTypeHashes.size() && !includeHashMatched) continue;

			if (name != "" && obj->GetName() != name) continue;
			if (!obj->IsInRange(globals::localPlayer->GetPosition(), range)) continue;

			if (ChooseSelectedObject(selectedObject, obj)) return obj;

			if (!best) {
				best = obj;
				continue;
			}

			if (best->GetDistanceTo(globals::localPlayer) > best->GetDistanceTo(globals::localPlayer)) {
				best = obj;
				continue;
			}
		}

		return best;
	}

	void Init()
	{
		ADD_SETTING("targetselector", "always focus selected", true);
	}
}