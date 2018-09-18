#pragma once
#include "Spell.h"
#include "GameSettings.h"
#include <unordered_map>
#include <memory>
class SpellFactory
{
public:
	SpellFactory()
	{
		DameOverTime fireOverTime = { &effect01,Element::Fire,10.0f,3.0f };
		DameOverTime waterOverTime = { &effect02,Element::Water,10.0f,3.0f };
		DameOverTime natureOverTime = { &effect03,Element::Nature,10.0f,3.0f };
		
		SlowMovementSpeed slow01 = { &effect03,0.1f,5.0f };
		SlowMovementSpeed slow02 = { &effect03,0.3f,2.0f };
		SlowMovementSpeed slow03 = { &effect03,0.2f,3.0f };
		{
			auto spell = std::make_unique<Spell>();
			spell->AddSpellComponent(fireOverTime.Clone());
			spellFactory.emplace(Element::Fire, spell->Clone());
			spell->AddSpellComponent(slow01.Clone());
			spellFactory.emplace(Element::Fire + Element::Fire, std::move(spell));
		}
		{
			auto spell = std::make_unique<Spell>();
			spell->AddSpellComponent(waterOverTime.Clone());
			spellFactory.emplace(Element::Water, spell->Clone());
			spell->AddSpellComponent(slow02.Clone());
			spellFactory.emplace(Element::Water + Element::Water, std::move(spell));
		}
		{
			auto spell = std::make_unique<Spell>();
			spell->AddSpellComponent(natureOverTime.Clone());
			spellFactory.emplace(Element::Nature, spell->Clone());
			spell->AddSpellComponent(slow03.Clone());
			spellFactory.emplace(Element::Nature + Element::Nature, std::move(spell));
		}
		{
			auto spell = std::make_unique<Spell>();
			spell->AddSpellComponent(fireOverTime.Clone());
			spell->AddSpellComponent(slow02.Clone());
			spellFactory.emplace(Element::Fire + Element::Water, std::move(spell));
		}
		{
			auto spell = std::make_unique<Spell>();
			spell->AddSpellComponent(natureOverTime.Clone());
			spell->AddSpellComponent(slow01.Clone());
			spellFactory.emplace(Element::Fire + Element::Nature, std::move(spell));
		}
		{
			auto spell = std::make_unique<Spell>();
			spell->AddSpellComponent(waterOverTime.Clone());
			spell->AddSpellComponent(slow03.Clone());
			spellFactory.emplace(Element::Water + Element::Nature, std::move(spell));
		}
		
		
	}
	static std::unique_ptr<ISpell> MakeSpell(int spellID) 
	{ 
		return Get().spellFactory.at(spellID)->Clone();
	}
private:
	static SpellFactory& Get()
	{
		static SpellFactory s;
		return s;
	}
private:
	//effect animation data pm_effect03_20_20_28
	SharedAnimationData effect01 = { 0,0,20,20,10, Codex<Surface>::Retrieve(L"Images\\Effect\\pm_effect01_20_20_10.png"), 
		GameSettings::Get().GetData("[Animation Speed]"), Colors::Black };
	SharedAnimationData effect02 = { 0,0,20,20,35, Codex<Surface>::Retrieve(L"Images\\Effect\\pm_effect02_20_20_35.png"), 
		0.35f * GameSettings::Get().GetData("[Animation Speed]"), Colors::Black };
	SharedAnimationData effect03 = { 0,0,20,20,28, Codex<Surface>::Retrieve(L"Images\\Effect\\pm_effect03_20_20_28.png"), 
		0.35f * GameSettings::Get().GetData("[Animation Speed]"), Colors::Black };
	std::unordered_map<int, std::unique_ptr<ISpell>> spellFactory;
};