#pragma once
#include "TileType.h"
#include "Graphics.h"
#include "Camera.h"
class GuiGameDatabase;
class IStateGameDatabase
{
public:
	virtual void Draw(const GuiGameDatabase* database, Graphics& gfx, const Camera& cam) const {};
	virtual bool CanOpenSelectMode()
	{
		return false;
	}
	virtual void OnClick(GuiGameDatabase* database) {};
	void UpdateOutsideBoard(const b2Vec2 & mouseWorldPos)
	{
		this->mouseWorldPos = mouseWorldPos;
	}
	void UpdateInsideBoard(const b2Vec2 & worldTilePos, const VecI & trackingTile, TileType tileType)
	{
		this->worldTilePos = worldTilePos;
		this->trackingTile = trackingTile;
		this->tileType = tileType;
	}
	void Reset()
	{
		isBegin = true;
	}
protected:
	bool isBegin = true;
	b2Vec2 mouseWorldPos;
	b2Vec2 worldTilePos;
	VecI trackingTile;
	TileType tileType;
};
class IStateNormal : public IStateGameDatabase
{
public:
	bool CanOpenSelectMode() final
	{
		return true;
	}
	void OnClick(GuiGameDatabase* database) final;
};

class StateSellTower : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const Camera& cam) const final;
	void OnClick(GuiGameDatabase* database) final;
};

class StateSwapTower : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const Camera& cam) const final;
	void OnClick(GuiGameDatabase* database) final;
};

class StateSelectDirGui : public IStateGameDatabase
{
public:
	void OnClick(GuiGameDatabase* database) final;
};

class StateHoldDirGui : public IStateGameDatabase
{
public:
	void OnClick(GuiGameDatabase* database) final;
};

class StateBuildTower : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const Camera& cam) const final;
	void OnClick(GuiGameDatabase* database) final;
};

class StateBuildGirGui : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const Camera& cam) const final;
	void OnClick(GuiGameDatabase* database) final;
private:
	b2Vec2 pos = { 0.0f,0.0f };
};

class StateBuildBorder : public IStateGameDatabase
{
public:
	void Draw(const GuiGameDatabase* database, Graphics& gfx, const Camera& cam) const final;
	void OnClick(GuiGameDatabase* database) final;
private:
	b2Vec2 p1 = { 0.0f,0.0f };
	b2Vec2 p2 = { 0.0f,0.0f };
};