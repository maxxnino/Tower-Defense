#include "SkillState.h"
#include "Skill.h"

void DameOverTime::Update(float dt, Enemy& enemy, Skill * skill)
{
	timerDuration += dt;
	if (timerDuration <= 3.0f)
	{
		UpdateAnimation(dt);
		timer += dt;
		while (timer >= 1.0f)
		{
			enemy.ApplyDame(10);
			timer -= 1.0f;
		}
		pos = enemy.getBody().GetPosition();
	}
	else
	{
		skill->MarkRemove();
	}
}
