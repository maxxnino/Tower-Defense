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
	gfx( wnd ),
	brd({0.0f,0.0f},(float)Graphics::ScreenWidth,(float)Graphics::ScreenHeight,&gui,gui.GetMouseStateObs())
{
	const b2Vec2 gravity = { 0.0f, 0.0f };
	box2DEngine = std::make_unique<b2World>(gravity);
	brd.AddObs(&gui);
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
	//gui.ProcessCommand(wnd.mouse);
	//gui.Update(dt, wnd.mouse);
	//brd.ProcessComand(wnd.mouse);
	while (!wnd.mouse.IsEmpty())
	{
		auto e = wnd.mouse.Read().GetType();
		if (e == Mouse::Event::Type::LPress)
		{
			const b2Vec2 pos = { 0.0f,0.0f };
			const float size = 1.0f;
			const b2Vec2 vel = { 2.0f,2.0f };
			pro.emplace_back(std::make_unique<Projectile>(*box2DEngine, pos, size, vel));
		}
	}
	
	box2DEngine->Step(dt, velocityIterations, positionIterations);
}

void Game::ComposeFrame()
{
	brd.Draw(gfx);
	gui.Draw(gfx);
	for (auto& p : pro)
	{
		p->Draw(gfx);
	}
}
