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
	world(*box2DEngine,BoardGame::tileWidth,BoardGame::tileHeight),
	mediatorGuiAndBrd(&brd,&gui,&world)
{
	static MyBox2DListener mrLister;
	mrLister.CaseContact<Tower, Enemy>([](PhysicObject& t, PhysicObject& e)
	{
		t.AddEnemyID(e.GetID());
	});
	mrLister.CaseContact<Projectile, Enemy>([](PhysicObject& p, PhysicObject& e)
	{
		p.MarkDead();
		e.ApplyDame(p.GetDame());
	});
	mrLister.CaseContact<Base, Enemy>([](PhysicObject& b, PhysicObject& e)
	{
		b.ApplyDame(e.GetDame());
		e.MarkReachBase();
	});


	mrLister.CaseLeave<Tower, Enemy>([](PhysicObject& t, PhysicObject& e)
	{
		if (t.isRemove())
		{
			t.RemoveEnemyID(e.GetID());
		}
	});
	
	box2DEngine->SetContactListener(&mrLister);
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
	if (dt > 0.01666666666667f * 5.0f)
	{
		dt = 0.01666667f;
	}
	gui.Update(dt, wnd.mouse);
	brd.ProcessComand(wnd.mouse);
	world.Update(dt);
	box2DEngine->Step(dt, velocityIterations, positionIterations);
	world.CleanWorld(dt);
}

void Game::ComposeFrame()
{
	brd.Draw(gfx);
	world.Draw(gfx);
	gui.Draw(gfx);
}
