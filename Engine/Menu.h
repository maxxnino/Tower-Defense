#pragma once
#include "IGui.h"
#include "Board.h"
class Menu : public IGui
{
public:
	Menu(VecF pos, float width, float height, Color color)
		:
		IGui(pos, width, height, color),
		board(pos, width, height)
	{}
	void Draw(Graphics& gfx) const override;
	void Update(float dt, Mouse& mouse) override;
	void AddItem(std::shared_ptr<IGui> item) override;
	void OnNotify() override;
	
private:
	std::vector<std::shared_ptr<IGui>> items;
	Board board;
};