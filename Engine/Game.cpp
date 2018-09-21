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
	cam({0.0f,0.0f}),
	mouseController(cam),
	brd({0.0f,0.0f},(float)Graphics::ScreenWidth,(float)Graphics::ScreenHeight),
	//brd2(L"Data\\map01.ini"),
	world(*box2DEngine,BoardGame::tileWidth,BoardGame::tileHeight),
	mediatorGuiAndBrd(&brd,&gui,&world)
{
	bgm.Play(1.0f, 0.5f);
	brd.AddMouseController(&mouseController);
	static MyBox2DListener mrLister;
	mrLister.CaseContact<Tower, Enemy>([](PhysicObject* t, PhysicObject* e)
	{
		auto tower = static_cast<Tower*>(t);
		auto enemy = static_cast<Enemy*>(e);
		tower->AddEnemyID(enemy->GetID());
	});
	mrLister.CaseContact<Projectile, Enemy>([this](PhysicObject* p, PhysicObject* e)
	{
		auto projectile = static_cast<Projectile*>(p);
		auto enemy = static_cast<Enemy*>(e);

		projectile->SetExplosionPos(Graphics::ToScreenSpace(0.2f * projectile->getBody().GetPosition() + 0.8f * enemy->getBody().GetPosition()));
		projectile->MarkDead();
		enemy->ApplyDame(projectile->GetElementType(), projectile->GetDame());
		std::uniform_int_distribution<int> change(0, 10);
		if (change(rng) <= 1)
		{
			enemy->AddSpell(projectile->GetElementType());
		}
		
	});
	mrLister.CaseContact<Base, Enemy>([](PhysicObject* b, PhysicObject* e)
	{
		auto base = static_cast<Base*>(b);
		auto enemy = static_cast<Enemy*>(e);

		base->ApplyDame(0, enemy->GetDame());
		enemy->MarkReachBase();
	});
	mrLister.CaseContact<DirectionGuiding, Enemy>([](PhysicObject* d, PhysicObject* e)
	{
		auto guiding = static_cast<DirectionGuiding*>(d);
		auto enemy = static_cast<Enemy*>(e);
		guiding->Guiding(enemy);
	});

	mrLister.CaseLeave<Tower, Enemy>([](PhysicObject* t, PhysicObject* e)
	{
		if (!t->isRemove())
		{
			auto tower = static_cast<Tower*>(t);
			auto enemy = static_cast<Enemy*>(e);
			tower->RemoveEnemyID(enemy->GetID());
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
	gui.Update(dt, wnd.mouse);
	brd.ProcessComand(wnd.mouse, cam.GetPos());
	world.Update(dt);
	box2DEngine->Step(dt, velocityIterations, positionIterations);
	world.CleanWorld(dt);
}

void Game::ComposeFrame()
{
	const VecI camPos = cam.GetPos();
	brd.Draw(gfx, camPos);
	world.Draw(gfx, camPos);
	gui.Draw(gfx);
	//brd2.DrawTest(gfx, camPos);
}
