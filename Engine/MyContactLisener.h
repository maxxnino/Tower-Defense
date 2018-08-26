#pragma once
#include <sstream>
#include <typeinfo>
#include "PhysicObject.h"

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
			static_cast<Enemy*>(bodyPtrs[1]->GetBody()->GetUserData())->MarkAsDead();
		}
		else
		{
			static_cast<Enemy*>(bodyPtrs[0]->GetBody()->GetUserData())->MarkAsDead();
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
};
