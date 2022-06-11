#include "precomp.h"
#include "ship.h"
#include "game.h"
#include "base.h"
#include "laser.h"

namespace Tmpl8 {

	const vec2 SHIP_LENGTH(10, 0);
	const enum keys { A = 1, D, W, SPACE };

	Ship::Ship(vec2 base, float radius) :
		Base(base, radius, 10),
		m_Speed(0.0f),
		m_SpeedRadius(0.0f),
		m_Force(0.0f, 0.0f)
	{
		vec2 nose(10, 0);
		m_Direction = Rotate(nose, m_Radius);
	}

	void Ship::Draw(Surface* screen)
	{
		//m_BasePos is default point of the ship
		//m_Direction is the nose which is based on the base

		vec2 wingL = Rotate(m_Direction, 205 * PI / 180);
		vec2 wingR = Rotate(m_Direction, 155 * PI / 180);
		wingL *= 1.8;
		wingR *= 1.8;
		screen->Line(m_Direction.x + m_BasePos.x, m_Direction.y + m_BasePos.y,
			m_Direction.x + m_BasePos.x + wingL.x, m_Direction.y + m_BasePos.y + wingL.y, 0x00FF00);
		screen->Line(m_Direction.x + m_BasePos.x, m_Direction.y + m_BasePos.y,
			m_Direction.x + m_BasePos.x + wingR.x, m_Direction.y + m_BasePos.y + wingR.y, 0x00FF00);

		vec2 wingBackL = Rotate(wingL, 330 * PI / 180);
		vec2 wingBackR = Rotate(wingR, 30 * PI / 180);
		wingBackL *= 0.5;
		wingBackR *= 0.5;
		screen->Line(m_Direction.x + m_BasePos.x + wingL.x, m_Direction.y + m_BasePos.y + wingL.y,
			m_Direction.x + m_BasePos.x + wingBackL.x, m_Direction.y + m_BasePos.y + wingBackL.y, 0x00FFFF);
		screen->Line(m_Direction.x + m_BasePos.x + wingR.x, m_Direction.y + m_BasePos.y + wingR.y,
			m_Direction.x + m_BasePos.x + wingBackR.x, m_Direction.y + m_BasePos.y + wingBackR.y, 0x00FFFF);
	}

	void Ship::Update(float deltaTime)
	{
		//Thanks to Brian Beuken & Wessel Frijters for helping me with this problem
		if (m_Force.length() > 0.6f)
			m_Force = m_Force.normalized() * 0.6;


		m_BasePos.x += m_Force.x * deltaTime;
		m_BasePos.y += m_Force.y * deltaTime;
	}

	vec2& Ship::GetBasePos()
	{
		return m_BasePos;
	}

	float Ship::GetRadius()
	{
		return m_Radius;
	}

	void Ship::MovementUpdate(int keyPress)
	{
		switch (keyPress)
		{
		case A:
		{
			if (m_Radius > (PI * 2))
				m_Radius = 0;
			else if (m_Radius < 0)
				m_Radius = PI * 2;

			m_Radius -= 0.02;

			m_Direction = Rotate(SHIP_LENGTH, m_Radius);
		}
			break;
		case D:
		{
			if (m_Radius > (PI * 2))
				m_Radius = 0;
			else if (m_Radius < 0)
				m_Radius = PI * 2;

			m_Radius += 0.02;

			m_Direction = Rotate(SHIP_LENGTH, m_Radius);
		}
			break;
		case W:
		{
			m_SpeedRadius = m_Radius;

			m_Speed += 0.0001f;

			if (m_Speed > 0.003f)
				m_Speed = 0.003f;

			m_Force.x += cos(m_SpeedRadius) * m_Speed;
			m_Force.y += sin(m_SpeedRadius) * m_Speed;
		}
			break;
		default:
		{
			//Dont do anything
		}
			break;
		}

	}

	void Ship::SetBasePos(vec2& basePos)
	{
		//Set point after being hit
		m_BasePos = basePos;
	}

	void Ship::SetForce(vec2 force)
	{
		m_Force = force;
	}

	vec2 Ship::GetForce()
	{
		return m_Force;
	}
};