#include "TowerManager.h"
#include "MenuItem.h"
void TowerManager::OnNotify(void * datauser)
{
	static_cast<MenuItem*>(datauser)->GetCommand().execute(this);
}