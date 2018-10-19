#pragma once
#include "Box2D/Box2D.h"
#include "Graphics.h"
class GuiGameDatabase;
class IStateGameDatabase
{
public:
	virtual void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) {};
	virtual bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) { return true; };
	virtual bool UpdateNoBuildTile(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) { return true; };
	virtual void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const {};
	virtual bool IsSelectMode()
	{
		return false;
	}
};
class IStateNormal : public IStateGameDatabase
{
public:
	void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	bool IsSelectMode() override
	{
		return true;
	}
};


class StateBuildTower : public IStateGameDatabase
{
public:
	void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const override;
};

class StateSellTower : public IStateGameDatabase
{
public:
	void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const override;
};

class StateSwapTower : public IStateGameDatabase
{
public:
	void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const override;
	void ResetSwapSlot()
	{
		swapSlot01 = std::make_pair(VecI(-1, -1), -1);
	}
private:
	std::pair<VecI, int> swapSlot01 = std::make_pair(VecI(-1, -1), -1);
};

class StateBuildDirGui : public IStateGameDatabase
{
public:
	void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	bool UpdateNoBuildTile(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
};

class StateSelectDirGui : public IStateGameDatabase
{
public:
	void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	bool UpdateNoBuildTile(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
};
class StateHoldDirGui : public IStateGameDatabase
{
public:
	void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	bool UpdateNoBuildTile(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
};