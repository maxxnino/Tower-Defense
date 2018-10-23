#pragma once
#include "IMediator.h"
#include "Background.h"
#include "MenuManager.h"
#include "World.h"
#include "GameSettings.h"
class ControlGuiAndBoard : public IMediator
{
public:
	ControlGuiAndBoard(Background* bg, MenuManager* menuMgr, World* world)
		:
		bg(*bg),
		menuMgr(*menuMgr),
		world(*world)
	{
		this->bg.AddMediator(this);
		this->menuMgr.AddMediator(this);
		this->world.AddMediator(this);
		this->database.AddMediator(this);
	}
	/**********************************/
	/*  Control Gui and Background    */
	void OpenUpgradeMenu() final
	{
		auto towerIndex = bg.GetTowerIndex();
		assert(towerIndex != -1);
		if (!menuMgr.isUpgradeMenuOpen() && !world.IsTowerMaxLv(towerIndex))
		{
			towerIndexInWorld = towerIndex;
			menuMgr.ChangeUpgradeMenu();
		}
	}
	void UpgradeTower() final
	{
		world.UpgradeTower(database.getElement(), towerIndexInWorld);
		towerIndexInWorld = -1;
		database.Clear();
	}
	void ActiveWarningText(int newType) final
	{
		menuMgr.ActiveWarningText(newType);
	}
	void Clear() final
	{
		database.Clear();
		menuMgr.ChangeMainMenu();
		towerIndexInWorld = -1;
		for (size_t i = 0; i < dirGuildingSelect.size(); i++)
		{
			dirGuildingSelect[i]->OnRelease();
		}
		if (swapSlot.second != -1)
		{
			swapSlot = std::make_pair(VecI(-1, -1), -1);
		}
	}
	void ActiveSelectMode()
	{
		database.ActiveSelectMode();
	}
	void DeactivateSelectMode()
	{
		database.DeactivateSelectMode();
	}
	void DeleteIsPress()
	{
		if (!dirGuildingSelect.empty())
		{
			dirGuildingSelect[0]->MarkDead();
			Clear();
			world.DeleteDirectionGuiding();
		}
	}
	/**********************************/


	/**********************************/
	/*      Control World Object      */
	void MakeTower(const b2Vec2& worldPos) final
	{
		bg.AddTower(world.MakeTower(database.getElement(), database.getElement()->getColor(), worldPos));
	}
	int GetGold() const final
	{
		return world.GetGold();
	}
	bool CanAffordTower() const final
	{
		return world.CanAffordTower(GetDatabase());
	}
	void DeleteTower() final
	{
		world.SellTower(bg.GetTowerIndex());
		bg.DeleteTower();
	}
	void SwapTower(const VecI& trackingTile) final
	{
		if(swapSlot.second == -1)
		{
			swapSlot.first = trackingTile;
			swapSlot.second = bg.GetTowerIndex();
		}
		else
		{
			const int index02 = bg.GetTowerIndex();
			if (swapSlot.second != index02)
			{
				world.DoSwapTower(swapSlot.second, index02);
				bg.SwapTower(swapSlot.first, index02, trackingTile, swapSlot.second);
				Clear();
			}
			else
			{
				ActiveWarningText(3);
			}
		}
	}
	void MakeDirectionGuiding(const b2Vec2& worldPos) final
	{
		world.MakeDirectionGuiding(worldPos);
		Clear();
	}
	bool SelectDirGuiding(const b2Vec2& worldPos) final
	{
		dirGuildingSelect.clear();
		dirGuildingSelect = world.GetBodyList<DirectionGuiding>(worldPos);
		if (dirGuildingSelect.size() > 0)
		{
			for (size_t i = 0; i < dirGuildingSelect.size(); i++)
			{
				dirGuildingSelect[i]->OnClick();
			}
			return true;
		}
		return false;
	}
	void SetDirectionDG(const b2Vec2& worldPos) final
	{
		if (!dirGuildingSelect.empty())
		{
			if (dirGuildingSelect[0]->SetDirection(worldPos))
			{
				Clear();
			}
		}
		else
		{
			Clear();
		}
	}
	void SetMousePos(const b2Vec2& worldPos) final
	{
		if (!dirGuildingSelect.empty())
		{
			dirGuildingSelect[0]->SetMousePos(worldPos);
		}
	}
	/**********************************/
private:
	MenuManager& menuMgr;
	World& world;
	Background& bg;
	int towerIndexInWorld = -1;
	std::pair<VecI, int> swapSlot = std::make_pair(VecI(-1,-1 ), -1);
	float mouseQuerySize = 0.1f;
	std::vector<DirectionGuiding*> dirGuildingSelect;
};