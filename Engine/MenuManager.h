#pragma once
#include "Menu.h"
#include "Button.h"
#include <algorithm>
class MenuManager
{
public:
	MenuManager()
	{
		//bottom menu
		{
			const VecF menuPos = { 100.0f,500.0f };
			MakeMenu(menuPos, 600.0f, 75.0f);
			for (int i = 0; i < 5; i++)
			{
				const float paddingLeft = 70.0f;
				const float paddingTop = 7.0f;
				const float spaceBetweenBtn = 100.0f;
				const float btwWidth = 60.0f;
				const float btnHeight = 60.0f;
				auto b = std::make_shared<Button>(menuPos + VecF(paddingLeft + (float)i * spaceBetweenBtn, paddingTop), btwWidth, btnHeight, Colors::Red);
				menus.back()->AddItem(b);
			}
		}
		//left menu
		{
			const VecF menuPos = { 100.0f,50.0f };
			MakeMenu(menuPos, 75.0f, 400.0f);
			for (int i = 0; i < 3; i++)
			{
				const float paddingLeft = 7.0f;
				const float paddingTop = 70.0f;
				const float spaceBetweenBtn = 100.0f;
				const float btwWidth = 60.0f;
				const float btnHeight = 60.0f;
				auto b = std::make_shared<Button>(menuPos + VecF(paddingLeft, paddingTop + (float)i * spaceBetweenBtn), btwWidth, btnHeight, Colors::Red);
				menus.back()->AddItem(b);
			}
		}
		//right menu
		{
			const VecF menuPos = { 650.0f,50.0f };
			MakeMenu(menuPos, 75.0f, 400.0f);
			for (int i = 0; i < 3; i++)
			{
				const float paddingLeft = 7.0f;
				const float paddingTop = 70.0f;
				const float spaceBetweenBtn = 100.0f;
				const float btwWidth = 60.0f;
				const float btnHeight = 60.0f;
				auto b = std::make_shared<Button>(menuPos + VecF(paddingLeft, paddingTop + (float)i * spaceBetweenBtn), btwWidth, btnHeight, Colors::Red);
				menus.back()->AddItem(b);
			}
		}
	}
	void Update(float dt, Mouse& mouse)
	{
		auto menuIndex = std::find_if(rects.begin(), rects.end(), [&mouse](auto& r) {return r.second.isContaint(mouse.GetPos()); });
		if (menuIndex != rects.end())
		{
			menus[menuIndex->first]->ProccessCommand(mouse);
			
		}
		for (auto& m : menus)
		{
			m->Update(dt);
		}
		
	}
	void Draw(Graphics& gfx) const
	{
		for (auto& m : menus)
		{
			m->Draw(gfx);
		}
	}
	inline void MakeMenu(VecF menuPos, float menuW, float menuH)
	{
		auto menu = std::make_shared<Menu>(Menu(menuPos, menuW, menuH, Colors::Cyan));
		menus.emplace_back(menu);
		rects.emplace(++tracker, menu->GetRect());
	}
private:
	std::vector<std::shared_ptr<Menu>> menus;
	std::unordered_map<int, RectF> rects;
	int tracker = -1;
};