#pragma once

#include "asteroid.h"

namespace Tmpl8 {

	class Sauser : public Asteroid
	{
	public:
		Sauser(vec2 basePos = vec2(0.0f, 0.0f), float radius = 0.0f);
		vec2& GetBasePos();
		float GetShipRadius();
		void CalcShipRadius(vec2& shipPos);
		void CalcShipRadius(unsigned int randomSeed);
		void SetValues(vec2 shipPos, bool = true, unsigned int randomSeed = 0, int size = 10); //maybe change
		void Draw(Surface* screen);
		//bool CheckCollision(const vec2& otherPoint, const int size);


	private:
		float m_ShipRadius;
	};

}; // namespace Tmpl8