#pragma once
#include "Box.h"
class MyContactListener : public b2ContactListener
{
	virtual void BeginContact(b2Contact* contact) {

		//check if both fixtures were balls
		void* bodyAUserData = contact->GetFixtureA()->GetBody()->GetUserData();
		void* bodyBUserData = contact->GetFixtureB()->GetBody()->GetUserData();

		if (bodyAUserData && bodyBUserData)
		{
			Box* boxA = static_cast<Box*>(bodyAUserData);
			Box* boxB = static_cast<Box*>(bodyBUserData);

		}
	}
}
