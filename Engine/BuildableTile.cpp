#include "BuildableTile.h"
#include "MenuItem.h"
void BuildableTile::OnNotify(void * userData)
{
	static_cast<MenuItem*>(userData)->GetCommand().execute(this);
}
