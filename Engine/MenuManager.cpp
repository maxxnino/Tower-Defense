#include "MenuManager.h"
#include "BuildableTile.h"

void MenuManager::OnNotify(Observer * dataUser)
{
	if (activeMenu == &mainMenu)
	{
		//call from buildableTile if that tile have tower and MouseState have nothing -> open Upgrade menu
		auto obs = static_cast<BuildableTile*>(dataUser);
		activeMenu = &upgradeMenu;
		activeMenu->ResetItem();
		upgradeMenuBtn01.Clear();
		upgradeMenuBtn02.Clear();
		upgradeMenuBtn03.Clear();
		upgradeMenuBtn01.AddObs(obs);
		upgradeMenuBtn01.AddObs(this);
		upgradeMenuBtn02.AddObs(obs);
		upgradeMenuBtn02.AddObs(this);
		upgradeMenuBtn03.AddObs(obs);
		upgradeMenuBtn03.AddObs(this);
	}
	else
	{
		activeMenu = &mainMenu;
		activeMenu->ResetItem();
	}
}
