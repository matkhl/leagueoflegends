#pragma once

#include "../stdafx.h"

class ChampionModule
{
public:
	virtual ~ChampionModule() {}
	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Attack() = 0;
	virtual void Render() = 0;
};

class ChampionModuleManager
{
private:
	std::map<std::string, ChampionModule*> modules;

	static ChampionModuleManager& GetInstance() {
		static ChampionModuleManager instance;
		return instance;
	}

	ChampionModuleManager() {}

public:
	static void RegisterModule(const std::string& name, ChampionModule* module) {
		GetInstance().modules[name] = module;
	}

	static ChampionModule* GetModule(const std::string& name) {
		auto& instance = GetInstance();
		auto it = instance.modules.find(name);
		if (it != instance.modules.end()) {
			return it->second;
		}
		else {
			return nullptr;
		}
	}
};