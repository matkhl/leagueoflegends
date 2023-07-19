#include "../stdafx.h"

namespace scripts
{
	namespace targetselector
	{
		bool ShouldChooseSelectedObject(Object* selectedObject, Object* checkObj)
		{
			return selectedObject == checkObj && SETTINGS_BOOL("targetselector", "always focus selected");
		}

		Object* GetEnemyChampionInRange(float range)
		{
			Object* selectedObject = functions::GetSelectedObject();
			Object* best = 0;
			for (Object* obj : *globals::heroManager)
			{
				if (!obj->IsValidTarget()) continue;

				Vector3 playerPos = globals::localPlayer->GetPosition();

				if (!obj->IsInRange(playerPos, range)) continue;

				if (ShouldChooseSelectedObject(selectedObject, obj)) return obj;
				
				if (!best) {
					best = obj;
					continue;
				}

				if (best->GetHealth() > obj->GetHealth()) {
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
}