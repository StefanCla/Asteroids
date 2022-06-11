#include "precomp.h"
#include "base.h"
#include "game.h"
#include "laser.h"

namespace Tmpl8 {

	const vec2 SHIP_LENGTH(10, 0); //Length of the laser

	Laser::Laser(vec2& force, vec2& m_BasePos, float m_Radius, bool fired, float distance):
		Base(m_BasePos, m_Radius, 1),
		m_Fired(fired),
		m_AbsoluteBase(m_BasePos),
		m_Distance(distance),
		m_MaxDistance(300)
	{}

	void Laser::SetValue(vec2& basePos, float radius, bool fired)
	{
		m_BasePos = basePos;
		m_AbsoluteBase = basePos;
		m_Radius = radius;
		m_Fired = fired;
		m_MaxDistance = 300;
	}

	void Laser::Draw(Surface* screen)
	{
		vec2 rotate = Rotate(SHIP_LENGTH, m_Radius);
		screen->Line(m_BasePos.x, m_BasePos.y, (m_BasePos.x + rotate.x), (m_BasePos.y + rotate.y), 0xF0000F);
	}

	void Laser::Update(float deltaTime)
	{
		//keyPress not used here

		float volX = 0.65f * cos(m_Radius) * deltaTime;
		float volY = 0.65f * sin(m_Radius) * deltaTime;

		m_BasePos.x += volX;
		m_BasePos.y += volY;

		if (m_Fired == true)
		{
			m_Distance = Distance();
			if (!(m_Distance <= m_MaxDistance))
				m_Fired = false;
		}
	}

	void Laser::Update(float deltaTime, float speed)
	{
		//keyPress not used here

		float volX = speed * cos(m_Radius) * deltaTime;
		float volY = speed * sin(m_Radius) * deltaTime;

		m_BasePos.x += volX;
		m_BasePos.y += volY;

		if (m_Fired == true)
		{
			m_Distance = Distance();
			if (!(m_Distance <= m_MaxDistance))
				m_Fired = false;
		}
	}

	float Laser::Distance()
	{
		//Distance between ship base and base of the laser
		//https://www.varsitytutors.com/hotmath/hotmath_help/topics/magnitude-and-direction-of-vectors formula and explanation
		float distance = sqrt(pow((m_AbsoluteBase.x - (m_BasePos.x + SHIP_LENGTH.x)), 2) + 
			pow((m_AbsoluteBase.y - (m_BasePos.y + SHIP_LENGTH.y)), 2));

		return distance;
	}

	vec2& Laser::GetBasePos()
	{
		return m_BasePos;
	}

	vec2& Laser::GetAbsoluteBase()
	{
		return m_AbsoluteBase;
	}

	float Laser::GetRadius()
	{
		return m_Radius;
	}

	bool Laser::CheckCollision(const vec2& otherPoint, const int size)
	{
		//Note, i can use it without sqrt. But because asteroids is so lightweight. I decided to use it anyway
		float distance = sqrt(pow((otherPoint.x - (m_BasePos.x + SHIP_LENGTH.x)), 2) +
			pow((otherPoint.y - (m_BasePos.y + SHIP_LENGTH.y)), 2));

		if (distance < m_Size + size)
		{
			m_Fired = false;
			return true;
		}
		else
			return false;
	}

	void Laser::ScreenWrap()
	{
		if (m_BasePos.x > 800 && m_BasePos.y < 512)
		{
			float x = 800 - m_AbsoluteBase.x;
			m_MaxDistance -= x;
			m_BasePos.x = 0;
			m_AbsoluteBase.x = 0;
		}
		else if (m_BasePos.x > 800 && m_BasePos.y > 512)
		{
			m_MaxDistance -= Distance();
			m_BasePos.x = 0;
			m_BasePos.y = 0;
			m_AbsoluteBase.x = 0;
			m_AbsoluteBase.y = 0;
		}
		else if (m_BasePos.x < 800 && m_BasePos.y > 512)
		{
			float y = 512 - m_AbsoluteBase.y;
			m_MaxDistance -= y;
			m_BasePos.y = 0;
			m_AbsoluteBase.y = 0;
		}
		else if (m_BasePos.x < 0 && m_BasePos.y > 0)
		{
			float x = 800 - m_AbsoluteBase.x;
			x = 800 - x;
			m_MaxDistance -= x;
			m_BasePos.x = 800;
			m_AbsoluteBase.x = 800;
		}
		else if (m_BasePos.x < 0 && m_BasePos.y < 0)
		{
			m_MaxDistance -= Distance();
			m_BasePos.x = 800;
			m_BasePos.y = 512;
			m_AbsoluteBase.x = 800;
			m_AbsoluteBase.y = 512;
		}
		else if (m_BasePos.x > 0 && m_BasePos.y < 0)
		{
			float y = 512 - m_AbsoluteBase.y;
			y = 512 - y;
			m_MaxDistance -= y;
			m_BasePos.y = 512;
			m_AbsoluteBase.y = 512;
		}
	}
};