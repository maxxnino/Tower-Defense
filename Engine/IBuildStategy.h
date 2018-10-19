#pragma once
#include "Box2D/Box2D.h"
#include "Graphics.h"
class GuiGameDatabase;
class IBuildStategy
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

class BuildTowerStategy : public IBuildStategy
{
	void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const override;
};

class BuildDirGuiStategy : public IBuildStategy
{
	void UpdateHaveTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const VecI& trackingTile, const b2Vec2& mouseWorldPos, int towerIndex) override;
	bool UpdateNoTower(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
	bool UpdateNoBuildTile(GuiGameDatabase* database, const b2Vec2& worldTilePos, const b2Vec2& mouseWorldPos) override;
};