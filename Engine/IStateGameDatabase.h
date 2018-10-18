#pragma once
#include "Box2D/Box2D.h"
#include "Graphics.h"
class GuiGameDatabase;
class IStateGameDatabase
{
public:
	virtual void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex);
	virtual bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) { return true; };
	virtual bool UpdateNoBuildTile(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) { return true; };
	virtual void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const {};
	bool IsSelectMode()
	{
		return isSelectMode;
	}
protected:
	bool isSelectMode = false;
};

class StateBuildTower : public IStateGameDatabase
{
public:
	virtual void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	virtual bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	virtual void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const override;
};

class StateSellTower : public IStateGameDatabase
{
public:
	virtual void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	virtual bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	virtual void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const override;
};

class StateSwapTower : public IStateGameDatabase
{
public:
	virtual void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	virtual bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	virtual void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const override;
private:
	std::pair<VecI, int> swapSlot01 = std::make_pair(VecI(-1, -1), -1);
};

class StateBuildDirGui : public IStateGameDatabase
{
public:
	virtual void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	virtual bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	virtual bool UpdateNoBuildTile(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
};

class StateSelectDirGui : public IStateGameDatabase
{
public:
	StateSelectDirGui()
	{
		IStateGameDatabase::isSelectMode = true;
	}
	virtual void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	virtual bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	virtual bool UpdateNoBuildTile(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
};
class HoldDirGui : public IStateGameDatabase
{
public:
	virtual void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	virtual bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	virtual bool UpdateNoBuildTile(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
};