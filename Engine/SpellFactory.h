#pragma once
#include "Spell.h"
class SpellFactory
{
public:
	static std::unique_ptr<ISpell> MakeSpell(int spellID) { return std::make_unique<Spell>(); };
};