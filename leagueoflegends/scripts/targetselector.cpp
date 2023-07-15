#include "../stdafx.h"

namespace scripts
{
	namespace targetselector
	{
		Object* GetEnemyChampionInRange(float range)
		{
			Object* best = 0;
			for (Object* obj : *globals::heroManager)
			{
				if (!obj->IsValidTarget()) continue;

				Vector3 playerPos = globals::localPlayer->GetPosition();

				if (!obj->IsInRange(playerPos, range)) continue;
				
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
	}
}