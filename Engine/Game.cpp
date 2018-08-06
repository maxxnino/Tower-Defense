/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
#include "MainWindow.h"
#include "Game.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
{
	//bottom menu
	{
		const VecF menuPos = { 100.0f,500.0f };
		auto menu = std::make_unique<Menu>(Menu(menuPos, 600.0f, 75.0f, Colors::Cyan));
		menus.emplace_back(std::move(menu));
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
		auto menu = std::make_unique<Menu>(Menu(menuPos, 75.0f, 400.0f, Colors::Cyan));
		menus.emplace_back(std::move(menu));
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
		auto menu = std::make_unique<Menu>(Menu(menuPos, 75.0f, 400.0f, Colors::Cyan));
		menus.emplace_back(std::move(menu));
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

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{
	const float dt = ft.Mark();
	for (auto& m : menus)
	{
		m->Update(dt, wnd.mouse);
	}
}

void Game::ComposeFrame()
{
	for (auto& m : menus)
	{
		m->Draw(gfx);
	}
}
