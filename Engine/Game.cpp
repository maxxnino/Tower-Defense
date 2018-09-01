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
	box2DEngine(std::make_unique<b2World>(b2Vec2(0.0f, 0.0f))),
	brd({0.0f,0.0f},(float)Graphics::ScreenWidth,(float)Graphics::ScreenHeight),
	world(*box2DEngine),
	mediatorGuiAndBrd(&brd,&gui,&world)
{
	box2DEngine->SetContactListener(&listener);
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
	timer += dt;
	gui.Update(dt, wnd.mouse);
	brd.ProcessComand(wnd.mouse);
	if (timer >= 1.0f)
	{
		timer = 0.0f;
		world.MakeEnemy();
	}
	
	box2DEngine->Step(dt, velocityIterations, positionIterations);
	

	/*for (size_t i = 0; i < enemies.size();)
	{
		if (enemies[i]->isRemove())
		{
			std::swap(enemies[i], enemies.back());
			enemies.pop_back();
		}
		else
		{
			i++;
		}
	}*/
}

void Game::ComposeFrame()
{
	brd.Draw(gfx);
	gui.Draw(gfx);
	world.Draw(gfx);
}
