#include "Tower.h"

std::shared_ptr<Tower> Tower::Upgrade(int typeID)
{
	switch (typeID)
	{ 
	case 1:
		return std::make_shared<FireTower>();
		break;
	case 2:
		return std::make_shared<WaterTower>();
		break;
	case 3:
		return std::make_shared<NatureTower>();
		break;
	default:
		return std::make_shared<Tower>(Colors::Red);
		break;
	}
}
