#include "../stdafx.h"

namespace scripts::prediction
{
	Vector3 GetObjectPositionAfterTime(Object* obj, float time, float distanceBuffer)
	{
		const auto aiManager = obj->GetAiManager();

		float speed = obj->GetMovementSpeed();
		if (aiManager->IsDashing())
		{
			speed = aiManager->GetDashSpeed();
		}

		const auto waypoints = aiManager->GetFutureSegments();
		const int waypointsSize = (int)waypoints.size();

		if (!waypointsSize)
			return obj->GetServerPosition();

		if (!time || waypointsSize == 1 || !aiManager->IsMoving())
			return waypoints.front();

		float distance = (speed * time) - distanceBuffer;

		for (int i = 1; i < waypointsSize; i++)
		{
			const float waydistance = waypoints[i - 1].Distance(waypoints[i]);
			if (waydistance >= distance)
			{
				return waypoints[i - 1].Extend(waypoints[i], distance);
			}
			if (i == waypointsSize - 1)
				return waypoints[i];
			distance = distance - waydistance;
		}
		
		return waypoints.front();
	}

	bool GetPrediction(Skillshot& skillshot, PredictionOutput &out)
	{
		auto target = targetselector::GetEnemyChampionInRange(skillshot.GetMaxRange());
		if (!target) return false;

		return GetPrediction(globals::localPlayer, target, skillshot, out);
	}

	bool GetPrediction(Object* sourceObj, Object* targetObj, Skillshot &skillshot, PredictionOutput& out)
	{
		const auto sourcePos = sourceObj->GetServerPosition();
		const auto targetAiManager = targetObj->GetAiManager();
		const float spellRadius = skillshot.GetRadius();

		float distance = sourcePos.Distance(targetObj->GetServerPosition());
		float distanceBuffer = skillshot.GetType() == SkillshotType::SkillshotCircle ? max(spellRadius - 70.0f, 0.0f) : 0.0f;

		if (distance > skillshot.GetMaxRange())
			return false;

		if (!skillshot.GetSpeed())
		{
			out.position = GetObjectPositionAfterTime(targetObj, skillshot.GetCastTime(), 0.0f);
			return true;
		}
		
		auto waypoints = targetAiManager->GetFutureSegments();
		const int waypointsSize = (int)waypoints.size();

		if (!waypointsSize)
		{
			out.position = targetObj->GetServerPosition();
			return true;
		}

		if (waypointsSize == 1 || !targetAiManager->IsMoving())
		{
			out.position = waypoints.front();
			return true;
		}

		float travelTime = (distance / skillshot.GetSpeed()) + skillshot.GetCastTime();
		auto predictedPos = GetObjectPositionAfterTime(targetObj, travelTime, distanceBuffer);

		distance = predictedPos.Distance(sourcePos);
		float missileTime = (distance / skillshot.GetSpeed()) + skillshot.GetCastTime();

		while (std::abs(travelTime - missileTime) > 0.01f)
		{
			travelTime = missileTime;
			predictedPos = GetObjectPositionAfterTime(targetObj, travelTime, distanceBuffer);

			distance = predictedPos.Distance(sourcePos);
			if (distance > skillshot.GetMaxRange())
			{
				return false;
			}

			missileTime = (distance / skillshot.GetSpeed()) + skillshot.GetCastTime();
		}

		out.position = predictedPos;
		return true;
	}
}