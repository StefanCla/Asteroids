#include "precomp.h"
#include "base.h"
#include "game.h"
#include "asteroid.h"

namespace Tmpl8 {

	const vec2 SHIP_LENGTH(10, 0); //Length of the laser

	Asteroid::Asteroid(vec2 position, float radius, int points, bool alive):
		Base(position, radius, 20), //0 get overwitten in the constructor
		m_Points(points),
		m_Alive(false)
	{}

	void Asteroid::Draw(Surface* screen)
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

			screen->Plot(basePosX + x, basePosY + y, 0xFFFFFF);
			screen->Plot(basePosX - x, basePosY + y, 0xFFFFFF);
			screen->Plot(basePosX + x, basePosY - y, 0xFFFFFF);
			screen->Plot(basePosX - x, basePosY - y, 0xFFFFFF);
			screen->Plot(basePosX + y, basePosY + x, 0xFFFFFF);
			screen->Plot(basePosX - y, basePosY + x, 0xFFFFFF);
			screen->Plot(basePosX + y, basePosY - x, 0xFFFFFF);
			screen->Plot(basePosX - y, basePosY - x, 0xFFFFFF);

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

				screen->Plot(basePosX + x, basePosY + y, 0xFFFFFF);
				screen->Plot(basePosX - x, basePosY + y, 0xFFFFFF);
				screen->Plot(basePosX + x, basePosY - y, 0xFFFFFF);
				screen->Plot(basePosX - x, basePosY - y, 0xFFFFFF);
				screen->Plot(basePosX + y, basePosY + x, 0xFFFFFF);
				screen->Plot(basePosX - y, basePosY + x, 0xFFFFFF);
				screen->Plot(basePosX + y, basePosY - x, 0xFFFFFF);
				screen->Plot(basePosX - y, basePosY - x, 0xFFFFFF);
			}
		}
	}

	void Asteroid::Update(float deltaTime)
	{
		//keyPress not used here

		float volX = 0.15f * cos(m_Radius) * deltaTime;
		float volY = 0.15f * sin(m_Radius) * deltaTime;

		m_BasePos.x += volX;
		m_BasePos.y += volY;
	}

	bool Asteroid::CheckCollision(const vec2& otherPoint, const int size)
	{
		//Note, i can use it without sqrt. But because asteroids is so lightweight. I decided to use it anyway
		float distance = sqrt(pow((otherPoint.x - (m_BasePos.x + SHIP_LENGTH.x)), 2) +
			pow((otherPoint.y - (m_BasePos.y + SHIP_LENGTH.y)), 2));

		if (distance < m_Size + size)
		{
			m_Alive = false;
			return true;
		}
		else
			return false;
	}

	void Asteroid::Split(Asteroid* Arr, float radius, unsigned int randomSeed)
	{
		//Asteroids move in the direction you shot once broken
		//asteroid splits in 2, but get smaller
		//move at about a 70-80 degree from the direction you shot.

		srand(static_cast<unsigned int>(randomSeed * 1000));

		int count = 0;
		float RadArray[2];
		RadArray[0] = radius + ((rand() % 85 + 1) * PI / 180);
		RadArray[1] = radius + ((rand() % 85 + 275) * PI / 180);

		if (m_Size == 20)
		{
			for (int i = 10; i < 30; i++)
			{
				if (Arr[i].m_Alive == false)
				{
					Arr[i].m_Alive = true;
					Arr[i].m_Size = 15;
					Arr[i].m_BasePos = m_BasePos;
					Arr[i].m_Radius = RadArray[count];
					count++;
				}

				if (count == 2)
					break;
			}
		}
		/* Code works fine. Disabled due to balancing the game. Can be re-abled to make it more challenging
		*
		else if (m_Size == 15)
		{
			for (int i = 30; i < 70; i++)
			{
				if (Arr[i].m_Alive == false)
				{
					if (Arr[i].m_Alive == false)
					{
						Arr[i].m_Alive = true;
						Arr[i].m_Size = 10;
						Arr[i].m_BasePos = m_BasePos;
						Arr[i].m_Radius = RadArray[count];
						count++;
					}

					if (count == 2)
						break;
				}
			}
		}
		*/
	}

	void Asteroid::SetValues(vec2 shipPos, bool alive, unsigned int randomSeed)
	{
		m_Alive = alive;
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
};