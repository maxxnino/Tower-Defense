#pragma once
#include "Box2D/Box2D.h"
#include "PhysicObject.h"
#include <vector>
#include <typeinfo>
class QuerySelectorBox2D
{
private:
	class MyQuerySelector : public b2QueryCallback
	{
	public:
		bool ReportFixture(b2Fixture* fixture) override
		{
			if (!fixture->IsSensor())
			{
				foundBodies.push_back(fixture->GetBody());
			}
			return true;//keep going to find all fixtures in the query area
		}
		std::vector<b2Body*> foundBodies;
	};
public:
	template <class T>
	std::vector<T*> GetBodyList(b2World& box2DEngine, const b2Vec2& pos, float size)
	{
		queryCallback.foundBodies.clear();
		b2AABB aabb;
		aabb.lowerBound = { pos.x - size, pos.y - size};
		aabb.upperBound = { pos.x + size, pos.y + size };
		box2DEngine.QueryAABB(&queryCallback, aabb);

		std::vector<T*> bodyList;
		
		for (size_t i = 0; i < queryCallback.foundBodies.size(); i++)
		{
			auto p = static_cast<PhysicObject*>(queryCallback.foundBodies[i]->GetUserData());
			if (auto b = dynamic_cast<T*>(p))
			{
				bodyList.emplace_back(static_cast<T*>(b));
			}
		}
		queryCallback.foundBodies.clear();
		return std::move(bodyList);
	}
private:
	MyQuerySelector queryCallback;
};
