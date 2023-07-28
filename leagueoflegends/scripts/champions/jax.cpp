#include "../../stdafx.h"

using namespace scripts;

class JaxModule : public ChampionModule
{
private:
    std::string name = SP_STRING("Jax");

private:
    float gameTime = 0.0f;

public:
    JaxModule()
    {
        ChampionModuleManager::RegisterModule(name, this);
    }

    void Init() override
    {

    }

    void Update() override
    {
        gameTime = functions::GetGameTime();

        auto wBuff = globals::localPlayer->GetBuffByName("JaxEmpowerTwo");
        if (wBuff && wBuff->GetStacksAlt())
            orbwalker::lastAttackTime = gameTime - globals::localPlayer->GetAttackWindup();
    }

    void Attack() override
    {
        auto wBuff = globals::localPlayer->GetBuffByName("JaxEmpowerTwo");
        float windup = globals::localPlayer->GetAttackWindup();
        float windupTime = orbwalker::lastAttackTime + windup + SETTINGS_FLOAT("orbwalker", "windupbuffer");
        if ((!wBuff || !wBuff->GetStacksAlt()) &&
            gameTime > windupTime &&
            gameTime < windupTime + 0.3f &&
            globals::localPlayer->CanCastSpell(SpellIndex::W))
        {
            if (auto target = targetselector::GetEnemyChampionInRange(globals::localPlayer->GetRealAttackRange()))
            {
                actions::CastSpell(SpellIndex::W, globals::localPlayer);
                return;
            }
        }
    }

    void Render() override
    {

    }
};

JaxModule module;