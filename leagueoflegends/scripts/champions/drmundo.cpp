#include "../../stdafx.h"

using namespace scripts;

class DrMundoModule : public ChampionModule
{
private:
    std::string name = SP_STRING("DrMundo");

    Skillshot q = SkillshotManager::RegisterSpell(name, SpellIndex::Q, Skillshot(1000.0f, 70.0f, 2000.0f, 0.25f, SkillshotType::SkillshotLine, { CollidableObjects::Objects }));

private:
    float gameTime = 0.0f;

public:
    DrMundoModule()
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

DrMundoModule module;