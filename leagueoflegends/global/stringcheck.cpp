#include "../stdafx.h"

namespace functions::stringcheck
{
	static std::vector<std::string> attackWindupSpells = {
		ATTACK_WINDUP_SPELL_ASHE,
		ATTACK_WINDUP_SPELL_KOGMAW
	};

	bool VectorContains(std::vector<std::string> vector, std::string string)
	{
		return std::find(vector.begin(), vector.end(), string) != vector.end();
	}

	bool IsAttackWindupSpell(std::string spellName)
	{
		return VectorContains(attackWindupSpells, spellName);
	}
}