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
	void OpenUpgradeMenu(int towerIndex) override
	{
		assert(towerIndex != -1);
		if (!menuMgr.isUpgradeMenuOpen() && !world.IsTowerMaxLv(towerIndex))
		{
			towerIndexInWorld = towerIndex;
			menuMgr.ChangeUpgradeMenu();
		}
	}
	void UpgradeTower() override
	{
		world.UpgradeTower(database.getElement(), towerIndexInWorld);
		towerIndexInWorld = -1;
		database.Clear();
	}
	void ActiveWarningText(int newType) override
	{
		menuMgr.ActiveWarningText(newType);
	}
	void OnRightClickFromGUI() override
	{
		database.Clear();
		if (menuMgr.isUpgradeMenuOpen())
		{
			menuMgr.ChangeMainMenu();
			towerIndexInWorld = -1;
		}
		else
		{
			menuMgr.EnableButton();
		}
		for (size_t i = 0; i < dirGuildingSelect.size(); i++)
		{
			dirGuildingSelect[i]->OnRelease();
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
			OnRightClickFromGUI();
			world.DeleteDirectionGuiding();
		}
	}
	/**********************************/


	/**********************************/
	/*      Control World Object      */
	void MakeTower(const b2Vec2& worldPos) override
	{
		bg.AddTower(world.MakeTower(database.getElement(), database.getElement()->getColor(), worldPos));
	}
	int GetGold() const override
	{
		return world.GetGold();
	}
	bool CanAffordTower() const override
	{
		return world.CanAffordTower(GetDatabase());
	}
	void DeleteTower(int towerIndex) override
	{
		world.SellTower(towerIndex);
	}
	bool DoSwapTower(const VecI& tilePos01, int index01, const VecI& tilePos02, int index02) override
	{
		if (world.DoSwapTower(index01, index02))
		{
			bg.SwapTower(tilePos01, index02, tilePos02, index01);
			OnRightClickFromGUI();
			return true;
		}
		return false;
	}
	void MakeDirectionGuiding(const b2Vec2& worldPos) override
	{
		world.MakeDirectionGuiding(worldPos);
		OnRightClickFromGUI();
	}
	bool SelectDirGuiding(const b2Vec2& worldPos) override
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
	void SetDirectionDG(const b2Vec2& worldPos) override
	{
		if (!dirGuildingSelect.empty())
		{
			if (dirGuildingSelect[0]->SetDirection(worldPos))
			{
				OnRightClickFromGUI();
			}
		}
		else
		{
			OnRightClickFromGUI();
		}
	}
	void SetMousePos(const b2Vec2& worldPos) override
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
	float mouseQuerySize = 0.1f;
	std::vector<DirectionGuiding*> dirGuildingSelect;
};