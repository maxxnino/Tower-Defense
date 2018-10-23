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
	{
		lines.emplace_back(std::make_unique<LineWall>(box2DEngine, b2Vec2(-20.0f, 12.0f), b2Vec2(19.0f, 12.0f)));
		lines.emplace_back(std::make_unique<LineWall>(box2DEngine, b2Vec2(19.0f, 12.0f), b2Vec2(19.0f, -15.0f)));
		lines.emplace_back(std::make_unique<LineWall>(box2DEngine, b2Vec2(-20.0f, 7.0f), b2Vec2(13.0f, 7.0f)));
		lines.emplace_back(std::make_unique<LineWall>(box2DEngine, b2Vec2(13.0f, 7.0f), b2Vec2(13.0f, -15.0f)));
	}
	void DrawDebug(Graphics& gfx, const Camera& cam) const
	{
		for (const auto& l : lines)
		{
			l->DrawDebug(gfx, cam);
		}
	}
	void MakeBorder(b2World& box2DEngine, const b2Vec2& p1, const b2Vec2& p2)
	{
		lines.emplace_back(std::make_unique<LineWall>(box2DEngine, p1, p2));
	}
private:
	LineWall top;
	LineWall right;
	LineWall bottom;
	LineWall left;
	std::vector<std::unique_ptr<LineWall>> lines;
};