#pragma once
#include "Rect.h"
#include <cmath>
#include <memory>
#include <functional>
#include "Box2D/Box2D.h"
enum CollisionFillter {
	BOX = 0x0001,
	ENEMY = 0x0002,
	TOWER = 0x0004,
	SENSOR = 0x0008,
	BASE = 0x0010
};
class PhysicObject
{
public:
	PhysicObject(b2World& box2DEngine, uint16 categoryBits, uint16 maskBits, const b2Vec2& worldPos, 
		bool isCircle = false, bool isSensor = false,float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f } )
		:
		size(size)
	{
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody;
			bodyDef.fixedRotation = true;
			bodyDef.position.Set(worldPos.x, worldPos.y);
			bodyDef.linearVelocity = b2Vec2(linVel.x, linVel.y);
			body = { box2DEngine.CreateBody(&bodyDef),[&box2DEngine](b2Body* pBody) {box2DEngine.DestroyBody(pBody); } };
		}
		if (isCircle)
		{
			b2CircleShape circleShape;
			circleShape.m_radius = size;
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &circleShape;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.0f;
			fixtureDef.restitution = 1.0f;
			//collision fillter
			fixtureDef.filter.categoryBits = categoryBits;
			fixtureDef.filter.maskBits = maskBits;
			body->CreateFixture(&fixtureDef);
		}
		else
		{
			b2PolygonShape dynamicBox;
			dynamicBox.SetAsBox(size, size);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &dynamicBox;
			fixtureDef.isSensor = isSensor;
			fixtureDef.density = 1.0f;
			fixtureDef.friction = 0.0f;
			fixtureDef.restitution = 1.0f;
			//collision fillter
			fixtureDef.filter.categoryBits = categoryBits;
			fixtureDef.filter.maskBits = maskBits;
			body->CreateFixture(&fixtureDef);
		}
		
	}
	b2Body& getBody()
	{
		return *body;
	}
	void SetVelocity(const b2Vec2& dir)
	{
		b2Vec2 vel = body->GetLinearVelocity() + dir;
		const float curSpeedSq = std::pow(vel.x, 2) + std::pow(vel.y, 2);
		if (curSpeedSq > maxSpeedSq)
		{
			float factor = std::sqrt(maxSpeedSq / curSpeedSq);
			vel = factor * vel;
		}
		body->SetLinearVelocity(vel);
	}
protected:
	float maxSpeedSq = 10.0f;
	float size;
	std::unique_ptr<b2Body, std::function<void(b2Body*)>> body;
};