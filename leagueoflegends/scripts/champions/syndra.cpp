#include "../../stdafx.h"

using namespace scripts;

class SyndraModule : public ChampionModule
{
private:
    std::string name = SP_STRING("Syndra");

    Skillshot q = SkillshotManager::RegisterSpell(name, SpellIndex::Q, Skillshot(800.0f, 105.0f, 0.0f, 0.6f, SkillshotType::SkillshotCircle));
    Skillshot w = SkillshotManager::RegisterSpell(name, SpellIndex::W, Skillshot(950.0f, 110.0f, 1900.0f, 0.4f, SkillshotType::SkillshotCircle));
    Skillshot e = SkillshotManager::RegisterSpell(name, SpellIndex::E, Skillshot(1300.0f, 90.0f, 2200.0f, 0.25f, SkillshotType::SkillshotLine));

private:
    float gameTime = 0.0f;

    float lastQForECastTime = 0.0f;
    float lastW1CastTime = 0.0f;
    float lastECastTime = 0.0f;

    Object* lastESphere = nullptr;

    Vector3 lastEObjPos = {};
    Vector3 lastEProjectionPos = {};
    Vector3 lastETargetPos = {};

public:
    SyndraModule()
    {
        ChampionModuleManager::RegisterModule(name, this);
    }

    bool CanCastW1()
    {
        return gameTime > lastW1CastTime + 0.1f;
    }

    bool SphereForEExists(Vector3 targetPos)
    {
        auto playerPos = globals::localPlayer->GetPosition();
        playerPos.y = 0.0f;
        targetPos.y = 0.0f;

        std::vector<QWORD> includeFilterTypeHashes = { ObjectType::Special, ObjectType::Less };

        for (Object* obj : *globals::minionManager)
        {
            float dist = obj->GetPosition().Distance(playerPos);
            if (dist > 800.0f || dist < 150.0f) continue;
            
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

            if (obj->GetName() != SP_STRING("SyndraSphere") &&
                (obj->GetName() != SP_STRING("TestCubeRender10Vision") || gameTime - lastQForECastTime > 0.5f)) continue;
            if (!obj->IsAlive()) continue;
            if ((obj->GetActionState() & 0x400) != 0) continue;

            auto objPos = obj->GetPosition();
            objPos.y = 0.0f;

            auto playerToObj = objPos - playerPos;
            auto playerToTarget = targetPos - playerPos;

            if (playerToObj.Length() >= playerToTarget.Length() + 500.0f) continue;

            float dot1 = playerToTarget.DotProduct(playerToObj);
            float dot2 = playerToObj.DotProduct(playerToObj);

            if (dot1 < 0.0f) continue;

            float t = dot1 / dot2;

            Vector3 projection = playerPos + (playerToObj * t);
            projection.y = 0.0;

            Vector3 distVector = targetPos - projection;
            distVector.y = 0.0;

            lastEObjPos = objPos;
            lastEProjectionPos = projection;
            lastETargetPos = targetPos;

            float objY = obj->GetPosition().y;
            lastEObjPos.y = objY;
            lastEProjectionPos.y = objY;
            lastETargetPos.y = objY;

            if (distVector.Length() <= e.GetRadius())
            {
                lastESphere = obj;
                return true;
            }
        }
        lastESphere = nullptr;
        return false;
    }

    void Init() override
    {
        ADD_SETTING("Syndra", "draw Q-E range", false);
        ADD_SETTING("Syndra", "draw E calculation", false);
    }

    void Update() override
    {
        gameTime = functions::GetGameTime();
    }

    void Attack() override
    {
        prediction::PredictionOutput qPrediction;
        prediction::PredictionOutput wPrediction;
        prediction::PredictionOutput ePrediction;

        auto spellCast = globals::localPlayer->GetActiveSpellCast();
        if (spellCast && spellCast->GetSpellId() == SpellIndex::E) return;

        if (e.IsCastable() && prediction::GetPrediction(e, ePrediction))
        {
            if (q.IsCastable() && (q.GetStacks() > 0 || q.GetName().size() == 7) &&
                globals::localPlayer->GetSpellBySlotId(SpellIndex::E)->GetManaCost() +
                globals::localPlayer->GetSpellBySlotId(SpellIndex::Q)->GetManaCost() <= globals::localPlayer->GetMana())
            {
                actions::CastSpell(SpellIndex::Q, ePrediction.position);
                lastQForECastTime = gameTime;
                return;
            }

            if (lastQForECastTime > gameTime + 0.1f ||  SphereForEExists(ePrediction.position))
            {
                actions::CastSpell(SpellIndex::E, ePrediction.position);
                lastECastTime = gameTime;
                return;
            }
        }
        else
        {
            lastEObjPos = {};
            lastEProjectionPos = {};
            lastETargetPos = {};
        }
        
        if (w.IsCastable() && (int)w.GetName().size() == 11 && prediction::GetPrediction(w, wPrediction))
        {
            actions::CastSpell(SpellIndex::W, wPrediction.position);
            return;
        }

        if (q.IsCastable() && (q.GetStacks() > 0 || q.GetName().size() == 7) && prediction::GetPrediction(q, qPrediction))
        {
            actions::CastSpell(SpellIndex::Q, qPrediction.position);
            return;
        }

        if (CanCastW1() && w.IsCastable() && (int)w.GetName().size() == 7 && prediction::GetPrediction(w, wPrediction))
        {
            auto monster = targetselector::GetObjectInRange(w.GetRange(), "",
                { ObjectType::Minion_Lane, ObjectType::Monster },
                { ObjectType::Monster_Epic, ObjectType::Monster_Dragon });
            if (monster && monster == functions::GetSelectedObject())
            {
                actions::CastSpell(SpellIndex::W, monster->GetPosition());
                lastW1CastTime = gameTime;
                return;
            }

            auto sphere = targetselector::GetObjectInRange(w.GetRange(), SP_STRING("SyndraSphere"), { ObjectType::Special }, {}, true);
            if (sphere && (sphere != lastESphere || gameTime > lastECastTime + 0.4f))
            {
                actions::CastSpell(SpellIndex::W, sphere->GetPosition());
                lastW1CastTime = gameTime;
                return;
            }

            if (monster)
            {
                actions::CastSpell(SpellIndex::W, monster->GetPosition());
                lastW1CastTime = gameTime;
                return;
            }
        }
    }

    void Render() override
    {
        if (e.IsCastable() && SETTINGS_BOOL("Syndra", "draw Q-E range"))
        {
            render::RenderCircleWorld(globals::localPlayer->GetPosition(), 40, e.GetRange(), COLOR_PURPLE, 1.0f);
        }

        if (lastEObjPos.IsValid() && lastEProjectionPos.IsValid() && lastETargetPos.IsValid() && SETTINGS_BOOL("Syndra", "draw E calculation"))
        {
            render::RenderCircleWorld(lastEObjPos, 20, 30.0f, COLOR_BLUE, 3.0f);
            render::RenderCircleWorld(lastETargetPos, 20, 30.0f, COLOR_RED, 3.0f);

            auto projectionDirection = lastEProjectionPos - lastETargetPos;
            auto projectionDirectionN = projectionDirection.Normalized();
            auto projectionSuccess = lastETargetPos + ((projectionDirection.Length() > e.GetRadius()) ? projectionDirectionN * e.GetRadius() : projectionDirection);

            auto objScreen = functions::WorldToScreen(lastEObjPos).ToImVec();
            auto projectionScreen = functions::WorldToScreen(lastEProjectionPos).ToImVec();
            auto targetScreen = functions::WorldToScreen(lastETargetPos).ToImVec();
            auto projectionSuccessScreen = functions::WorldToScreen(projectionSuccess).ToImVec();

            render::RenderLine(objScreen, projectionScreen, COLOR_WHITE, 3.0f);
            render::RenderLine(projectionSuccessScreen, projectionScreen, COLOR_RED, 3.0f);
            render::RenderLine(targetScreen, projectionSuccessScreen, COLOR_GREEN, 3.0f);
        }
    }
};

SyndraModule module;