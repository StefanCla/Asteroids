#include "precomp.h"
#include "base.h"
#include "game.h"
#include "life.h"

namespace Tmpl8 {

	const vec2 SHIP_LENGTH(0.0f, -10.0f);

	Life::Life(vec2& base, float radius, int ID) :
		Base(base, radius, 0),
		m_Direction(SHIP_LENGTH),
		m_Alive(false),
		m_ID(ID)
	{}

	void Life::Draw(Surface* screen)
	{
		if (m_Alive == true)
		{
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
	}

	void Life::Update(float deltaTime)
	{
		//for (int i = 3; i > lives; i--)
		//{
		//	if (m_ID == i)
		//		m_Alive = false;
		//}
	}

	void Life::SetID(int ID)
	{
		m_ID = ID;

		m_BasePos.y = 28.0f;
		switch (ID)
		{
		case 0: m_BasePos.x = 10.0f;
			break;
		case 1: m_BasePos.x = 30.0f;
			break;
		case 2: m_BasePos.x = 50.0f;
			break;
		case 3: m_BasePos.x = 70.0f;
			break;
		case 4: m_BasePos.x = 90.0f;
			break;
		default: //Do nothing
			break;
		}
	}

	void Life::SetAlive(bool alive)
	{
		m_Alive = alive;
	}

	bool Life::GetAlive()
	{
		return m_Alive;
	}

}; // namespace Tmpl8