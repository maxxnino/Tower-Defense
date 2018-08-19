#pragma once
#include "Observer.h"
#include "Tower.h"
class TowerManager : public IObervable
{
public:
	void OnNotify(void* datauser) override;
	void changeToFireTower() { activeTower = &fireTower; }
	void changeToWaterTower() { activeTower = &waterTower; }
	void changeToNatureTower() { activeTower = &natureTower; }
	void changeToNullptr() { activeTower = nullptr; }
	bool isEmpty() { return activeTower == nullptr; }
	const Tower* const GetTower() const { return activeTower; }
private:
	Tower* activeTower = nullptr;
	FireTower fireTower;
	WaterTower waterTower;
	NatureTower natureTower;
};