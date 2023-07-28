#include "../../stdafx.h"

using namespace scripts;

class BrandModule : public ChampionModule
{
private:
    std::string name = SP_STRING("Brand");

    Skillshot q = SkillshotManager::RegisterSpell(name, SpellIndex::Q, Skillshot(1040.0f, 60.0f, 1600.0f, 0.25f, SkillshotType::SkillshotLine, { CollidableObjects::Objects }));
    Skillshot w = SkillshotManager::RegisterSpell(name, SpellIndex::W, Skillshot(900.0f, 260.0f, 0.0f, 0.9f, SkillshotType::SkillshotCircle));

private:
    float gameTime = 0.0f;

public:
    BrandModule()
    {
        ChampionModuleManager::RegisterModule(name, this);
    }

    void Init() override
    {

    }

    void Update() override
    {
        gameTime = functions::GetGameTime();
    }

    void Attack() override
    {
        prediction::PredictionOutput wPrediction;
        if (w.IsCastable() && prediction::GetPrediction(w, wPrediction))
        {
            actions::CastSpell(SpellIndex::W, wPrediction.position);
            return;
        }

        auto target = targetselector::GetEnemyChampionInRange(675.0f);
        if (target && globals::localPlayer->CanCastSpell(SpellIndex::E))
        {
            actions::CastSpell(SpellIndex::E, target);
            return;
        }

        prediction::PredictionOutput qPrediction;
        if (q.IsCastable() && prediction::GetPrediction(q, qPrediction))
        {
            actions::CastSpell(SpellIndex::Q, qPrediction.position);
            return;
        }
    }

    void Render() override
    {

    }
};

BrandModule module;