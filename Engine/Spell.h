#pragma once
#include "ISpell.h"
#include "ISpellStategy.h"
#include <memory>
class Spell : public ISpell
{
public:
	void Update(float dt, PhysicObject& entity) override
	{
		if (spellMgr.size() != 0)
		{
			for (int i = 0; i < spellMgr.size();)
			{
				spellMgr[i]->Update(dt, entity);
				if (spellMgr[i]->IsRemove())
				{
					std::swap(spellMgr[i], spellMgr.back());
					spellMgr.pop_back();
				}
				else
				{
					i++;
				}
			}
		}
		else
		{
			MarkRemove();
		}
		
	}
	void AddSpellComponent(std::unique_ptr<ISpellStategy> spellComponent)
	{
		spellMgr.emplace_back(std::move(spellComponent));
	}
	void EntityChangeData(PhysicObject& entity) override
	{
		for (auto& s : spellMgr)
		{
			s->EntityChangeData(entity);
		}
	}
	void Draw(Graphics& gfx, const VecI& pos) const override
	{
		for (auto& s : spellMgr)
		{
			s->Draw(gfx, offSet);
		}
	}
	void MarkRemove()
	{
		isRemove = true;
	}
	bool GetIsRemove() const override
	{
		return isRemove;
	}
	void AddOffSet(const b2Vec2& pos)
	{
		offSet = pos;
	}
private:
	b2Vec2 offSet;
	int enemyID = 0;
	bool isRemove = false;
	std::vector<std::unique_ptr<ISpellStategy>> spellMgr;
};