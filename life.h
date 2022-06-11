#pragma once

#include "base.h"

namespace Tmpl8 {

	class Life : public Base
	{
	public:
		void Draw(Surface* screen);
		void Update(float deltaTime);
		Life(vec2& Base = (vec2)(0.0f, 0.0f), float radius = 0.0f, int ID = 0);
		void SetID(int ID);
		void SetAlive(bool alive);
		bool GetAlive();

	private:
		vec2 m_Direction;
		bool m_Alive;
		int m_ID;
	};

}; // namespace Tmpl8