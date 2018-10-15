#pragma once
#include "GuiGameDatabase.h"
class IMediator
{
public:
	/**********************************/
	/*  Control Gui and Background    */
	virtual void OpenUpgradeMenu(int towerIndex) = 0;
	virtual void UpgradeTower() = 0;
	virtual void ActiveWarningText(int newType) = 0;
	virtual void OnRightClickFromGUI() = 0;
	
	inline GuiGameDatabase* GetDatabase()
	{
		return &database;
	}
	inline const GuiGameDatabase& GetDatabase() const
	{
		return database;
	}
	/**********************************/


	/**********************************/
	/*      Control World Bbject      */
	virtual void MakeTower(const b2Vec2& worldPos) = 0;
	virtual int GetGold() const = 0;
	virtual bool CanAffordTower() const = 0;
	virtual void DeleteTower(int towerIndex) = 0;
	virtual bool DoSwapTower(const VecI& tilePos01, int index01, const VecI& tilePos02, int index02) = 0;
	virtual void MakeDirectionGuiding(const b2Vec2& worldPos) = 0;
	/**********************************/
protected:
	GuiGameDatabase database;
};