#include "Listener.h"
#include "TileGame.h"
#include "Button.h"	

void ButtonListener::OnClick(void * userdata)
{
	auto b = static_cast<Button*>(userdata);
	data = b->getData();
}
