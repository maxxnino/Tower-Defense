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
	controler(wnd.mouse, cam),
	bg({ -100.0f / 2.0f,-100.0f / 2.0f }, 100, 100, 2, rng),
	world(Camera::scalePixel * 2, Camera::scalePixel * 2),
	mediatorGuiAndBrd(&bg,&gui,&world)
{
	bgm.Play(1.0f, 0.3f);
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
	float dt = ft.Mark();
	gui.Update(dt, wnd.mouse);
	bg.Update(wnd.mouse, cam, controler);
	world.Update(dt);
}

void Game::ComposeFrame()
{
	const VecI camPos = cam.GetPos();
	bg.Draw(gfx, cam);
	world.Draw(gfx, cam);
	gui.Draw(gfx);
}
