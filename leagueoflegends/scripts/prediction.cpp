#include "../stdafx.h"

namespace scripts::prediction
{
	bool CheckCollision(Vector3 sourcePos, Vector3 targetPos, Object* sourceObject, Object* targetObject, Skillshot &skillshot)
	{
		if (skillshot.IsCollidableWith(CollidableObjects::Objects) && IsAnyObjectInWay(sourcePos, targetPos, sourceObject, targetObject, skillshot.GetRadius()))
			return false;
		return true;
	}

	bool IsSpecificObjectInWay(Vector3 sourcePos, Vector3 targetPos, Object* collisionObject, float projectileRadius)
	{
		auto sourceToTarget = targetPos - sourcePos;
		sourceToTarget.y = 0.0f;
		auto distance = sourceToTarget.Length();

		auto objPos = collisionObject->GetPosition();
		auto sourceToObj = objPos - sourcePos;
		sourceToObj.y = 0.0f;
		if (sourceToObj.Length() > distance) return false;

		float dot1 = sourceToObj.DotProduct(sourceToTarget);
		float dot2 = sourceToTarget.DotProduct(sourceToTarget);

		if (dot1 < 0.0f) return false;

		float t = dot1 / dot2;

		Vector3 projection = sourcePos + (sourceToTarget * t);
		projection.y = 0.0;

		Vector3 distVector = objPos - projection;
		distVector.y = 0.0;

		if (distVector.Length() <= projectileRadius + collisionObject->GetBoundingRadius())
			return true;

		return false;
	}

	bool IsAnyObjectInWay(Vector3 sourcePos, Vector3 targetPos, Object* sourceObject, Object* targetObject, float projectileRadius)
	{
		auto objectInWay = [&](auto& objectManager) {
			auto sourceToTarget = targetPos - sourcePos;
			sourceToTarget.y = 0.0f;
			auto distance = sourceToTarget.Length();

			for (auto obj : objectManager)
			{
				if (obj == targetObject || obj == sourceObject) continue;
				if (!obj->IsValidTarget()) continue;

				if (IsSpecificObjectInWay(sourcePos, targetPos, obj, projectileRadius))
					return true;
			}
			return false;
		};

		return objectInWay(*globals::minionManager) || objectInWay(*globals::heroManager);
	}

	Vector3 GetObjectPositionAfterTime(Object* obj, float time, float distanceBuffer)
	{
		const auto aiManager = obj->GetAiManager();

		float speed = obj->GetMovementSpeed();
		if (aiManager->IsDashing())
		{
			speed = aiManager->GetDashSpeed();
		}
		
		std::vector<Vector3> waypoints = { obj->GetServerPosition() };
		auto futureWaypoints = aiManager->GetFutureSegments();
		for (auto waypoint : futureWaypoints)
			waypoints.push_back(waypoint);
		
		const int waypointsSize = (int)waypoints.size();

		if (!waypointsSize || !time || !aiManager->IsMoving())
			return obj->GetServerPosition();

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
		auto target = targetselector::GetEnemyChampionInRange(skillshot.GetMaxRange(), skillshot);
		if (!target) return false;

		return GetPrediction(globals::localPlayer, target, skillshot, out);
	}

	bool GetPrediction(Object* sourceObj, Object* targetObj, Skillshot &skillshot, PredictionOutput& out)
	{
		const auto sourcePos = sourceObj->GetServerPosition();
		const auto targetAiManager = targetObj->GetAiManager();
		const float spellRadius = skillshot.GetRadius();

		float distance = sourcePos.Distance(targetObj->GetServerPosition());
		float distanceBuffer = skillshot.GetType() == SkillshotType::SkillshotCircle ? max(spellRadius - 20.0f, 0.0f) : 0.0f;

		if (distance > skillshot.GetMaxRange())
			return false;

		if (!skillshot.GetSpeed())
		{
			out.position = GetObjectPositionAfterTime(targetObj, skillshot.GetCastTime(), distanceBuffer);
			return CheckCollision(sourcePos, out.position, sourceObj, targetObj, skillshot);
		}
		
		auto waypoints = targetAiManager->GetFutureSegments();
		const int waypointsSize = (int)waypoints.size();

		if (!waypointsSize || !targetAiManager->IsMoving())
		{
			out.position = targetObj->GetServerPosition();
			return CheckCollision(sourcePos, out.position, sourceObj, targetObj, skillshot);
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
		return CheckCollision(sourcePos, out.position, sourceObj, targetObj, skillshot);
	}
}