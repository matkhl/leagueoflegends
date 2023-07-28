#include "../../stdafx.h"

using namespace scripts;

class GarenModule : public ChampionModule
{
private:
    std::string name = SP_STRING("Garen");

private:
    float gameTime = 0.0f;

public:
    GarenModule()
    {
        ChampionModuleManager::RegisterModule(name, this);
    }

    void Init() override
    {
        ADD_SETTING("Garen", "auto R", true);
    }

    void Update() override
    {
        gameTime = functions::GetGameTime();

        if (SETTINGS_BOOL("Garen", "auto R") && globals::localPlayer->CanCastSpell(SpellIndex::R))
        {
            if (auto target = targetselector::GetEnemyChampionInRange(400.0f, DamageType::True, Skillshot()))
            {
                float targetHealth = target->GetHealth();

                auto rSpell = globals::localPlayer->GetSpellBySlotId(SpellIndex::R);
                int rSpellLevel = rSpell->GetLevel();
                float trueDamage = (150.0f * rSpellLevel) + (target->GetMaxHealth() - targetHealth) * (0.20f + 0.05f * rSpellLevel);

                if (targetHealth < trueDamage * 0.95f)
                {
                    actions::CastSpell(SpellIndex::R, target);
                    return;
                }
            }
        }
    }

    void Attack() override
    {
        
    }

    void Render() override
    {

    }
};

GarenModule module;