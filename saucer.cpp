#include "precomp.h"
#include "asteroid.h"
#include "game.h"
#include "sauser.h"

namespace Tmpl8 {

	Sauser::Sauser(vec2 basePos, float radius) :
		Asteroid(basePos, radius, 30),
		m_ShipRadius(0)
	{
		m_Alive = false;
	}

	vec2& Sauser::GetBasePos()
	{
		return m_BasePos;
	}

	void Sauser::CalcShipRadius(vec2& shipPos)
	{
		//http://www.cplusplus.com/reference/cmath/atan2/
			//Gets the radians to the ship so it knows its location.
		float x = shipPos.x - m_BasePos.x;
		float y = shipPos.y - m_BasePos.y;
		m_ShipRadius = atan2f(y, x);
	}

	void Sauser::CalcShipRadius(unsigned int randomSeed)
	{
		srand(randomSeed);
		m_ShipRadius = (rand() % 360 + 1) * PI / 180;
	}

	float Sauser::GetShipRadius()
	{
		return m_ShipRadius;
	}

	void Sauser::SetValues(vec2 shipPos, bool alive, unsigned int randomSeed, int size)
	{
		m_Alive = alive;
		m_Size = size;
		//randomize the pos
		srand(static_cast<unsigned int>(randomSeed));

		do
		{
			m_BasePos.x = static_cast<float>(rand() % 800 + 1);

		} while (!(m_BasePos.x < (shipPos.x - 250) || m_BasePos.x >(shipPos.x + 250)));

		do
		{
			m_BasePos.y = static_cast<float>(rand() % 512 + 1);

		} while (m_BasePos.y < (shipPos.y - 150) || m_BasePos.y >(shipPos.y + 150));


		int randomRadius = rand() % 360 + 1;
		m_Radius = randomRadius * PI / 180;


	}

	void Sauser::Draw(Surface* screen)
	{
		//calculate the asteroid circle
		//Understand the gist of it. But not fully yet! Research more!
		if (m_Alive == true)
		{
			int x = 0;
			int y = m_Size;
			int dimention = 3 - 2 * m_Size;
			int basePosX = static_cast<int>(m_BasePos.x);
			int basePosY = static_cast<int>(m_BasePos.y);

			screen->Plot(basePosX + x, basePosY + y, 0x0FFF00);
			screen->Plot(basePosX - x, basePosY + y, 0x0FFF00);
			screen->Plot(basePosX + x, basePosY - y, 0x0FFF00);
			screen->Plot(basePosX - x, basePosY - y, 0x0FFF00);
			screen->Plot(basePosX + y, basePosY + x, 0x0FFF00);
			screen->Plot(basePosX - y, basePosY + x, 0x0FFF00);
			screen->Plot(basePosX + y, basePosY - x, 0x0FFF00);
			screen->Plot(basePosX - y, basePosY - x, 0x0FFF00);

			while (y >= x)
			{
				x++;

				if (dimention > 0)
				{
					y--;
					dimention = dimention + 4 * (x - y) + 10;
				}
				else
					dimention = dimention + 4 * x + 6;

				screen->Plot(basePosX + x, basePosY + y, 0x0FFF00);
				screen->Plot(basePosX - x, basePosY + y, 0x0FFF00);
				screen->Plot(basePosX + x, basePosY - y, 0x0FFF00);
				screen->Plot(basePosX - x, basePosY - y, 0x0FFF00);
				screen->Plot(basePosX + y, basePosY + x, 0x0FFF00);
				screen->Plot(basePosX - y, basePosY + x, 0x0FFF00);
				screen->Plot(basePosX + y, basePosY - x, 0x0FFF00);
				screen->Plot(basePosX - y, basePosY - x, 0x0FFF00);
			}
		}
	}

};