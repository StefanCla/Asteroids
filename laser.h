#pragma once

#include "base.h"

namespace Tmpl8 {

	class Laser : public Base
	{
	public:
		void Draw(Surface* screen);
		void Update(float deltaTime);
		void Update(float deltaTime, float speed);
		Laser(vec2& force = vec2(0,0), vec2& m_BasePos = (vec2)(0.0f, 0.0f), float m_Radius = 0.0f, bool fired = false, float distance = 0.0f);
		void SetValue(vec2& m_BasePos, float m_Radius, bool fired);
		bool m_Fired;
		vec2& GetBasePos();
		vec2& GetAbsoluteBase();
		float GetRadius();
		bool CheckCollision(const vec2& otherPoint, const int size);
		float Distance();
		void ScreenWrap();

	private:
		float m_Distance;
		vec2 m_AbsoluteBase;
		float m_MaxDistance;
	};

}; // namespace Tmpl8