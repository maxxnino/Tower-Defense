#pragma once
#include "IGui.h"
class Menu : public IGui
{
public:
	Menu(int id, VecF pos, float width, float height, Color color)
		:
		IGui(id, pos, width, height, color)
	{}
	void Draw(Graphics& gfx) const override;
	void Update(float dt) override;
	void AddItem(std::shared_ptr<IGui> item) override;
	void OnNotify() override;
	
private:
	std::unordered_map<int ,std::shared_ptr<IGui>> items;
};