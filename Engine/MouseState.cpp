#include "MouseState.h"
#include "MenuItem.h"
void MouseState::OnNotify(Observer * datauser)
{
	typeDame = static_cast<MenuItem*>(datauser)->getData();
}
