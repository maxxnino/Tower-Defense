#pragma once
#include "TileType.h"
#include "Graphics.h"
class GuiGameDatabase;
class IStateGameDatabase
{
public:
	virtual void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const {};
	virtual bool CanOpenSelectMode()
	{
		return false;
	}
	virtual void Update(GuiGameDatabase* database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType) {};
};
class IStateNormal : public IStateGameDatabase
{
public:
	bool CanOpenSelectMode() final
	{
		return true;
	}
	void Update(GuiGameDatabase* database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType) final;
};

class StateSellTower : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const override;
	void Update(GuiGameDatabase* database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType) final;
};

class StateSwapTower : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const override;
	void Update(GuiGameDatabase* database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType) final;
};

class StateSelectDirGui : public IStateGameDatabase
{
public:
	void Update(GuiGameDatabase* database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType) final;
};
class StateHoldDirGui : public IStateGameDatabase
{
public:
	void Update(GuiGameDatabase* database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType) final;
};

class StateBuildTower : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const final;
	void Update(GuiGameDatabase* database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType) final;
};

class StateBuildGirGui : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const final;
	void Update(GuiGameDatabase* database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType) final;
};

class StateBuildBorder : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const VecI& drawPos) const final;
	void Update(GuiGameDatabase* database, const b2Vec2 & worldTilePos, const VecI & trackingTile, const b2Vec2 & mouseWorldPos, TileType tileType) final;
};