#pragma once
#include "GuiGameDatabase.h"
class IMediator
{
public:
	/**********************************/
	/*  Control Gui and Background    */
	virtual void OpenUpgradeMenu() = 0;
	virtual void UpgradeTower() = 0;
	virtual void ActiveWarningText(int newType) = 0;
	virtual void Clear() = 0;
	
	inline GuiGameDatabase* GetDatabase()
	{
		return &database;
	}
	inline const GuiGameDatabase& GetDatabase() const
	{
		return database;
	}
	virtual b2Vec2 GetCornerPoint(const b2Vec2& worldPos) const = 0;
	/**********************************/


	/**********************************/
	/*      Control World Bbject      */
	virtual void MakeTower(const b2Vec2& worldPos) = 0;
	virtual int GetGold() const = 0;
	virtual bool CanAffordTower() const = 0;
	virtual void DeleteTower() = 0;
	virtual void SwapTower(const VecI& trackingTile) = 0;
	virtual void MakeDirectionGuiding(const b2Vec2& worldPos) = 0;
	virtual bool SelectDirGuiding(const b2Vec2& worldPos) = 0;
	virtual void SetDirectionDG(const b2Vec2& worldPos) = 0;
	virtual void SetMousePos(const b2Vec2& worldPos) = 0;
	virtual void MakeBorder(const b2Vec2& p1, const b2Vec2& mouseWorldPos) = 0;
	/**********************************/
protected:
	GuiGameDatabase database;
};