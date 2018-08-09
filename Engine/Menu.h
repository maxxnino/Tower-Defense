#pragma once
#include "IGui.h"
#include "Board.h"
class Menu : public IGui
{
public:
	Menu(VecF pos, float width, float height, Color color)
		:
		IGui(pos, width, height, color)
	{}
	void Draw(Graphics& gfx) const override;
	void Update(float dt, Mouse& mouse) override;
	void AddItem(std::shared_ptr<IGui> item) override;
	void MouseClick() override {}
	void MouseLeave() override {}
	void MouseIn() override {}
	
private:
	std::vector<std::shared_ptr<IGui>> items;
};