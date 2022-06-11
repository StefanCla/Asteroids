#pragma once

#include "base.h"

namespace Tmpl8 {

	class Ship : public Base
	{
	public:
		void Draw(Surface* screen);
		void Update(float deltaTime);
		Ship(vec2 base, float radius);
		vec2& GetBasePos();
		float GetRadius();
		void Drift();
		void MovementUpdate(int keyPress);
		void SetBasePos(vec2& basePos);
		void SetForce(vec2 force);
		vec2 GetForce();

		//Add drifting so that the ship slides.

	private:
		vec2 m_Direction;
		float m_Speed;
		float m_SpeedRadius;
		vec2 m_Force;
	};

}; // namespace Tmpl8