#include "../../stdafx.h"

using namespace scripts;

class Module : public ChampionModule
{
private:
    std::string name = SP_STRING("Syndra");

    Skillshot q = SkillshotManager::RegisterSpell(name, SpellIndex::Q, { 800.0f, 210.0f, 9999.0f, 0.0f, SkillshotType::SkillshotCircle, {} });

public:
    Module()
    {
        ChampionModuleManager::RegisterModule(name, this);
    }

    void Init() override
    {
        
    }

    void Update() override
    {
        
    }

    void Attack() override
    {
        if (!globals::localPlayer->CanCastSpell(SpellIndex::Q))
            return;

        prediction::PredictionOutput qPrediction;
        if (prediction::GetPrediction(q, qPrediction))
        {
            functions::CastSpell(SpellIndex::Q, nullptr, qPrediction.position);
        }
    }
};

Module module;