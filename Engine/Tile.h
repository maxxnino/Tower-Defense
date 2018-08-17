//#pragma once
//#include <unordered_set>
//#include "Rect.h"
//#include "Graphics.h"
//#include "IGui.h"
//#include "MouseGame.h"
//class Tile
//{
//public:
//	void MouseClick(const VecI& mousePos, MouseGame& mouse, bool& passOver)
//	{
//		for (auto i : items)
//		{
//			if (i->GetRect().isContaint(mousePos))
//			{
//				i->MouseClick();
//				passOver = false;
//			}
//		}
//	}
//	void MouseMove(const VecI& mousePos, MouseGame& mouse, bool& passOver)
//	{
//		for (auto i : items)
//		{
//			if (i->GetRect().isContaint(mousePos))
//			{
//				i->MouseIn();
//				passOver = false;
//			}
//			else
//			{
//				i->MouseLeave();
//				passOver = true;
//			}
//		}
//	}
//	void AddItem(std::shared_ptr<IGui> sub)
//	{
//		items.emplace_back(sub);
//	}
//	void Awake()
//	{
//		c = Colors::Red;
//	}
//	void Sleep()
//	{
//		c = Colors::Blue;
//	}
//	void Draw(Graphics& gfx, VecI pos,int width, int height) const
//	{
//		gfx.DrawRectDim(pos + VecI(2, 2), width - 2, height - 2, c);
//	}
//private:
//	std::vector<std::shared_ptr<IGui>> items;
//	Color c = Colors::Blue;
//};