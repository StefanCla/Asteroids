#pragma once

#include "base.h"

namespace Tmpl8 {

	class Asteroid : public Base
	{
	public:
		virtual void Draw(Surface* screen); //Keep virtual since saucer inherits
		virtual void Update(float deltaTime); //Keep virtual since saucer inherits
		Asteroid(vec2 position = vec2(0.0f,0.0f), float radius = 0.0f, int points = 100, bool alive = false);
		bool CheckCollision(const vec2& otherPoint, const int size);
		void Split(Asteroid* Arr, float radius, unsigned int randomSeed);
		bool m_Alive;
		virtual void SetValues(vec2 shipPos, bool alive = true, unsigned int randomSeed = 0);

	protected:
		int m_Points;
	};

}; // namespace Tmpl8