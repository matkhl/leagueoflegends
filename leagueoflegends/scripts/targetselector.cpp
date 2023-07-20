#include "../stdafx.h"

namespace scripts::targetselector
{
	bool ChooseSelectedObject(Object* selectedObject, Object* checkObj)
	{
		return selectedObject == checkObj && SETTINGS_BOOL("targetselector", "always focus selected");
	}

	Object* GetEnemyChampionInRange(float range)
	{
		return GetEnemyChampionInRange(range, max(globals::localPlayer->GetAttackDamage(), globals::localPlayer->GetAbilityPower()));
	}

	Object* GetEnemyChampionInRange(float range, int damageType)
	{
		Object* selectedObject = functions::GetSelectedObject();
		Object* best = 0;
		for (Object* obj : *globals::heroManager)
		{
			if (!obj->IsValidTarget()) continue;

			Vector3 playerPos = globals::localPlayer->GetPosition();

			if (!obj->IsInRange(playerPos, range)) continue;

			if (ChooseSelectedObject(selectedObject, obj)) return obj;
				
			if (!best) {
				best = obj;
				continue;
			}

			if (damageType == DamageType::True) {
				if (best->GetHealth() > obj->GetHealth()) {
					best = obj;
					continue;
				}
			} else {
				if (best->GetEffectiveHealth(damageType) > obj->GetEffectiveHealth(damageType)) {
					best = obj;
					continue;
				}
			}
		}

		return best;
	}

	void Init()
	{
		ADD_SETTING("targetselector", "always focus selected", true);
	}
}