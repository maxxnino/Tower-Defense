#pragma once
#include <sstream>
#include <typeinfo>
#include "PhysicObject.h"
#include "Enemy.h"
#include "Tower.h"

class MyContactLisener : public b2ContactListener
{
public:
	void BeginContact(b2Contact* contact) override 
	{
		const b2Fixture* bodyPtrs[] = { contact->GetFixtureA(),contact->GetFixtureB() };
		bool sensorA = bodyPtrs[0]->IsSensor();
		bool sensorB = bodyPtrs[1]->IsSensor();
		if (!(sensorA ^ sensorB)) return;
		if (sensorA)
		{
			auto enemy = static_cast<Enemy*>(bodyPtrs[1]->GetBody()->GetUserData());
			auto tower = static_cast<Tower*>(bodyPtrs[0]->GetBody()->GetUserData());
			tower->AddEnemy(enemy);
			enemy->AddObs(tower);
		}
		else
		{
			auto enemy = static_cast<Enemy*>(bodyPtrs[0]->GetBody()->GetUserData());
			auto tower = static_cast<Tower*>(bodyPtrs[1]->GetBody()->GetUserData());
			tower->AddEnemy(enemy);
			enemy->AddObs(tower);
		}


		/*if (bodyPtrs[0]->GetType() == b2BodyType::b2_dynamicBody &&
			bodyPtrs[1]->GetType() == b2BodyType::b2_dynamicBody)
		{
			PhysicObject* boxPtrs[] = {
				reinterpret_cast<PhysicObject*>(bodyPtrs[0]->GetUserData()),
				reinterpret_cast<PhysicObject*>(bodyPtrs[1]->GetUserData())
			};
			auto& tid0 = typeid(boxPtrs[0]);
			auto& tid1 = typeid(boxPtrs[1]);

			std::stringstream msg;
			msg << "Collision between " << tid0.name() << " and " << tid1.name() << std::endl;
			OutputDebugStringA(msg.str().c_str());
		}*/
	}
	void EndContact(b2Contact* contact) 
	{
		const b2Fixture* bodyPtrs[] = { contact->GetFixtureA(),contact->GetFixtureB() };
		bool sensorA = bodyPtrs[0]->IsSensor();
		bool sensorB = bodyPtrs[1]->IsSensor();
		if (!(sensorA ^ sensorB)) return;
		if (sensorA)
		{
			auto tower = static_cast<Tower*>(bodyPtrs[0]->GetBody()->GetUserData());
			auto enemy = static_cast<Enemy*>(bodyPtrs[1]->GetBody()->GetUserData());
			tower->RemoveEnemy(enemy);
			enemy->RemoveObs(tower);
		}
		else
		{
			auto tower = static_cast<Tower*>(bodyPtrs[1]->GetBody()->GetUserData());
			auto enemy = static_cast<Enemy*>(bodyPtrs[0]->GetBody()->GetUserData());
			tower->RemoveEnemy(enemy);
			enemy->RemoveObs(tower);
		}
	}
};
