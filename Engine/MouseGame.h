#pragma once
#include "Mouse.h"
#include <deque>
class MouseGame
{
public:
	MouseGame(Mouse& mouse)
		:
		mouse(mouse)
	{}
	const VecI getPos() const
	{
		return mouse.GetPos();
	}
	Mouse::Event::Type getMouseEventForGUI()
	{
		if (index < mouseEvents.size())
		{
			index++;
			return mouseEvents[index - 1];
		}
		else
		{
			isPassOver = true;
			return Mouse::Event::Type::Invalid;
		}
	}
	Mouse::Event::Type getMouseEventForGame()
	{
		auto e = mouseEvents.front();
		mouseEvents.pop_front();
		return e;
	}
	void Update()
	{
		index = 0;
		isPassOver = false;
		mouseEvents.clear();
		while (!mouse.IsEmpty())
		{
			mouseEvents.emplace_back(mouse.Read().GetType());
		}
	}
	bool isEmpty()
	{
		return mouseEvents.empty();
	}
	void PassOver()
	{
		isPassOver = true;
	}
	bool GetPassOver()
	{
		return isPassOver;
	}
	Mouse& getMouse()
	{
		return mouse;
	}
	void EatLastComand()
	{
		index--;
		mouseEvents.pop_front();
	}
private:
	Mouse& mouse;
	int index = 0;
	std::deque<Mouse::Event::Type> mouseEvents;
	bool isPassOver = false;
};