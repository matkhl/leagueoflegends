#include "../../stdafx.h"

using namespace scripts;

class Module : public ChampionModule
{
private:
    std::string name = "Syndra";

public:
    Module() {
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
        
    }
};

Module module;