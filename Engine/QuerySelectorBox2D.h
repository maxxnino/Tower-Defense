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
			if (fixture->TestPoint(mousePos))
			{
				foundBodies.push_back(fixture->GetBody());
			}
			return true;//keep going to find all fixtures in the query area
		}
		std::vector<b2Body*> foundBodies;
		b2Vec2 mousePos = { 0.0f,0.0f };
	};
public:
	QuerySelectorBox2D()
	{
		aabb.lowerBound = { 0.0f, 0.0f };
		aabb.upperBound = { 0.0f, 0.0f };
	}
	template <class T>
	std::vector<T*> GetBodyList(b2World& box2DEngine, const b2Vec2& pos)
	{
		queryCallback.foundBodies.clear();
		queryCallback.mousePos = pos;
		aabb.lowerBound = { pos.x - 0.01f, pos.y - 0.01f };
		aabb.upperBound = { pos.x + 0.01f, pos.y + 0.01f };
		box2DEngine.QueryAABB(&queryCallback, aabb);

		std::vector<T*> bodyList;
		
		for (size_t i = 0; i < queryCallback.foundBodies.size(); i++)
		{
			auto p = static_cast<PhysicObject*>(queryCallback.foundBodies[i]->GetUserData());
			if (auto b = dynamic_cast<T*>(p))
			{
				bodyList.emplace_back(b);
			}
		}
		return std::move(bodyList);
	}
private:
	MyQuerySelector queryCallback;
	b2AABB aabb;
};
