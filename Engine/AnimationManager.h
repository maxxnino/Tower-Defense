#pragma once
#include "Animation.h"
#include "Codex.h"
class AnimationManager
{
public:
	const Animation* GetProAnimation(int i) const
	{
		switch (i)
		{
		case 1:
			return &pro01;
			break;
		case 2:
			return &pro02;
			break;
		case 3:
			return &pro03;
			break;
		default:
			return &pro01;
			break;
		}
	}
	const Animation* GetExplsionAnimation(int i) const
	{
		switch (i)
		{
		case 1:
			return &exl01;
			break;
		case 2:
			return &exl01;
			break;
		case 3:
			return &exl01;
			break;
		default:
			return &exl01;
			break;
		}
	}
private:
	const Animation pro01 = { 0, 0, 30, 30, 2, Codex<Surface>::Retrieve(L"Images\\pm_pro_30_30_2.png"), 0.1f, Colors::Black };
	const Animation pro02 = { 30, 0, 30, 30, 8, Codex<Surface>::Retrieve(L"Images\\pm_pro_30_30_9.png"), 0.1f, Colors::Black };
	const Animation pro03 = { 0, 0, 30, 30, 14, Codex<Surface>::Retrieve(L"Images\\pm_pro_30_30_14.png"), 0.1f, Colors::Black };
	const Animation exl01 = { 0, 0, 30, 30, 14, Codex<Surface>::Retrieve(L"Images\\pm_pro_30_30_14.png"), 0.1f, Colors::Black };
};