#pragma once
class IMediator
{
public:
	virtual void OpenUpgradeMenu(int index) = 0;
	virtual void UpgradeTower(int index) = 0;
	virtual void ChangeToFire() = 0;
	virtual void ChangeToIce() = 0;
	virtual void ChangeToLighting() = 0;
};