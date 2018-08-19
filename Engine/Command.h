#pragma once
#include "TowerManager.h"
#include "BuildableTile.h"
class Command
{
public:
	virtual void execute(void* executed) = 0;
};

class ChangeFireTower : public Command
{
public:
	void execute(void* executed) override
	{
		static_cast<TowerManager*>(executed)->changeToFireTower();
	}
};
class ChangeWaterTower : public Command
{
public:
	void execute(void* executed) override
	{
		static_cast<TowerManager*>(executed)->changeToWaterTower();
	}
};
class ChangeNatureTower : public Command
{
public:
	void execute(void* executed) override
	{
		static_cast<TowerManager*>(executed)->changeToNatureTower();
	}
};

class UpgradeToFireTower : public Command
{
public:
	void execute(void* executed) override
	{
		auto tower = static_cast<BuildableTile*>(executed)->GetTower();
		tower = tower->Upgrade(1);
	}
};
class UpgradeToWaterTower : public Command
{
public:
	void execute(void* executed) override
	{
		auto tower = static_cast<BuildableTile*>(executed)->GetTower();
		tower = tower->Upgrade(2);
	}
};
class UpgradeToNatureTower : public Command
{
public:
	void execute(void* executed) override
	{
		auto tower = static_cast<BuildableTile*>(executed)->GetTower();
		tower = tower->Upgrade(3);
	}
};