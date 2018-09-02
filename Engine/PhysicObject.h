#pragma once
#include <cmath>
#include <memory>
#include <functional>
#include <string>
#include "Box2D/Box2D.h"
#include "Rect.h"
enum CollisionFillter {
	BORDER = 0x0001,
	ENEMY = 0x0002,
	TOWER = 0x0004,
	BASE = 0x0008,
	BULLET = 0x0010
};
class PhysicObject
{
public:
	PhysicObject(b2World& box2DEngine, uint16 categoryBits, uint16 maskBits, const b2Vec2& worldPos, 
		bool isCircle = false, bool isSensor = false,float size = 1.0f, const b2Vec2& linVel = { 0.0f,0.0f } )
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
			fixtureDef.isSensor = isSensor;
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
	PhysicObject(b2World& box2DEngine, uint16 categoryBits, uint16 maskBits, const b2Vec2& posBegin, const b2Vec2& posEnd)
	{
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_staticBody; //change body type
			bodyDef.position.Set(0, 0); //middle, bottom
			body = { box2DEngine.CreateBody(&bodyDef),[&box2DEngine](b2Body* pBody) {box2DEngine.DestroyBody(pBody); } };
		}

		{
			//shape
			b2EdgeShape edgeShape;
			edgeShape.Set(posBegin, posEnd);

			//fixture
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &edgeShape;
			//collision fillter
			fixtureDef.filter.categoryBits = categoryBits;
			fixtureDef.filter.maskBits = maskBits;
			body->CreateFixture(&fixtureDef);
		}
	}
	PhysicObject(b2World& box2DEngine, uint16 categoryBits, uint16 maskBits, const b2Vec2& worldPos, float width, float height, bool isCircle = false)
	{
		{
			b2BodyDef bodyDef;
			bodyDef.type = b2_dynamicBody; //change body type
			bodyDef.position.Set(worldPos.x, worldPos.y); //middle, bottom
			body = { box2DEngine.CreateBody(&bodyDef),[&box2DEngine](b2Body* pBody) {box2DEngine.DestroyBody(pBody); } };
		}
		if (isCircle)
		{
			b2CircleShape circleShape;
			circleShape.m_radius = width;
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &circleShape;
			fixtureDef.isSensor = true;
			//collision fillter
			fixtureDef.filter.categoryBits = categoryBits;
			fixtureDef.filter.maskBits = maskBits;
			body->CreateFixture(&fixtureDef);
		}
		{
			b2PolygonShape kinematicBBox;
			kinematicBBox.SetAsBox(width, height);
			b2FixtureDef fixtureDef;
			fixtureDef.shape = &kinematicBBox;
			fixtureDef.isSensor = true;
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

	/**********************************/
	/*Virtual function for PhysiObject*/
	virtual void SetVelocity(const b2Vec2& dir) {}
	virtual void MarkDead() {}
	virtual void AddEnemyID(int id) { assert(false); }
	virtual int GetID() { assert(false); return -1; }
	virtual void RemoveEnemyID(int id) { assert(false); }
	virtual void ApplyDame(int dame) { assert(false); }
	virtual int GetDame() { assert(false); return -1; }
	/***********************************/
protected:
	std::unique_ptr<b2Body, std::function<void(b2Body*)>> body;
};