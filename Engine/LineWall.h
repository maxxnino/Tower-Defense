#pragma once
#include "PhysicObject.h"
#include "Graphics.h"
class LineWall : public PhysicObject
{
public:
	LineWall(b2World& box2DEngine, const b2Vec2& beginPos, const b2Vec2& endPos)
		:
		beginPos(beginPos),
		endPos(endPos),
		PhysicObject(box2DEngine, CollisionFillter::BORDER, CollisionFillter::ENEMY, beginPos, endPos)
	{
		body->SetUserData(this);
	}
	void DrawDebug(Graphics& gfx, const Camera& cam) const
	{
		gfx.DrawLine(cam.GetDrawPosition(beginPos), cam.GetDrawPosition(endPos), Colors::Blue);
	}
	/**********************************/
	/*Virtual function for PhysiObject*/
	/***********************************/
private:
	b2Vec2 beginPos;
	b2Vec2 endPos;
};

class Border
{
public:
	Border(b2World& box2DEngine)
		:
		top(box2DEngine, { -20.0f, 12.0f}, {19.0f, 12.0f }),
		right(box2DEngine, { 19.0f, 12.0f }, { 19.0f, -15.0f }),
		bottom(box2DEngine, { -20.0f, 7.0f }, { 13.0f, 7.0f }),
		left(box2DEngine, { 13.0f, 7.0f }, { 13.0f, -15.0f })
	{}
	void DrawDebug(Graphics& gfx, const Camera& cam) const
	{
		top.DrawDebug(gfx, cam);
		right.DrawDebug(gfx, cam);
		bottom.DrawDebug(gfx, cam);
		left.DrawDebug(gfx, cam);
	}
private:
	LineWall top;
	LineWall right;
	LineWall bottom;
	LineWall left;
};