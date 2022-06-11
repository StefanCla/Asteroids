#include "precomp.h" // include this first in every .cpp file
#include "game.h"
#include "ship.h"
#include "laser.h"
#include "asteroid.h"
#include "sauser.h"
#include "life.h"

//Asteroid Heaven project
//Creating the project again since i didn't use inheritence and polymorphism

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		brian = new Ship(basePos, radius);

		asteroid = new Asteroid[asteroidSize];
		sauser = new Sauser[sauserSize];
		laser = new Laser[laserSize];
		life = new Life[liveSize];
		sauserLaser = new Laser[sauserSize];
		for (int i = 0; i < liveSize; i++)
		{
			if (i < 3)
			{
				life[i].SetAlive(true);
				lives++;
			}

			life[i].SetID(i);
		}

		//Initialize the variables

		//Gameplay variables
		lastFired = -1;
		keyPress = 0;
		wave = 0;
		play = false;
		score = 0;
		oldScore = 0;
		lives = 0;
		state = 1;
		basePos = vec2(400, 256);
		radius = 0;
		randomSeed = 0;
		seedIncrease = 0;
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
		delete brian;
		brian = 0;

		delete[] asteroid;
		asteroid = 0;

		delete[] sauser;
		sauser = 0;

		delete[] laser;
		laser = 0;

		delete[] life;
		life = 0;

		delete[] sauserLaser;
		sauserLaser = 0;
	}
	

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0);
		randomSeed += deltaTime;

		if(play && wave <= 10 && lives > 0) //Gameloop
		{
			//Thanks to Wessel Frijters for this idea
			snprintf(waveBuffer, sizeof(waveBuffer), "Wave: %i", wave);
			screen->Print(waveBuffer, 10, 8, 0xFFFFFF);
			snprintf(scoreBuffer, sizeof(scoreBuffer), "Score: %i", score);
			screen->Print(scoreBuffer, 65, 8, 0xFFFFFF);

			if ((oldScore + 10000) < score)
			{
				oldScore = score;
				if (lives < 5)
				{
					lives++;
					life[lives - 1].SetAlive(true);
				}
			}

			if (keyPressA)
				keyPress = A, brian->MovementUpdate(keyPress);

			if (keyPressD)
				keyPress = D, brian->MovementUpdate(keyPress);

			if (keyPressW)
				keyPress = W, brian->MovementUpdate(keyPress);

			if (keyPressSpace)
			{
				keyPress = SPACE, brian->MovementUpdate(keyPress);

				for (int i = 0; i < laserSize; i++)
				{
					//Not the nicest way of doing things
					//But it works!
					if (laser[lastFired].Distance() > 50)
					{
						if (!(laser[i].m_Fired))
						{
							laser[i].SetValue(brian->GetBasePos(), brian->GetRadius(), true);
							lastFired = i;
							break;
						}
					}
					else if (lastFired == -1)
					{
						if (!(laser[i].m_Fired))
						{
							laser[i].SetValue(brian->GetBasePos(), brian->GetRadius(), true);
							lastFired = i;
							break;
						}
					}
				}
			}

			keyPress = 0;

			brian->Update(deltaTime);
			brian->Draw(screen);

			//Loop through all lasers and update / draw them
			for (int i = 0; i < laserSize; i++)
			{
				if (laser[i].m_Fired == true)
				{
					laser[i].Update(deltaTime);
					if (laser[i].m_Fired == true)
					{
						laser[i].ScreenWrap();
						laser[i].Draw(screen);
					}
				}
				else if (lastFired == -1)
				{
					//Dont do anything
				}
				else if (laser[lastFired].m_Fired == false)
					laser[lastFired].Update(deltaTime);
			}

			bool sausersAlive = false;
			//Sauser loop
			for (int i = 0; i < sauserSize; i++)
			{
				if (sauser[i].m_Alive == true)
				{
					sausersAlive = true;

					if (sauser[i].CheckCollision(brian->GetBasePos(), brian->m_Size))
					{
						life[--lives].SetAlive(false);
						brian->SetBasePos(basePos);
						brian->SetForce((0.0f, 0.0f));
					}

					if (sauserLaser[i].m_Fired == false)
					{
						if (sauser[i].m_Size == 10)
						{
							sauser[i].CalcShipRadius(brian->GetBasePos());
							sauserLaser[i].SetValue(sauser[i].GetBasePos(), sauser[i].GetShipRadius(), true);
						}
						else
						{
							unsigned int randomSetSeed = static_cast<unsigned int>(randomSeed * 1000);
							sauser[i].CalcShipRadius(randomSetSeed);
							sauserLaser[i].SetValue(sauser[i].GetBasePos(), sauser[i].GetShipRadius(), true);
						}
						sauserLaser[i].m_Fired = true;
					}

					if (sauserLaser[i].m_Fired == true)
					{
						sauserLaser[i].Update(deltaTime, 0.38f); //0.38f = speed 
						sauserLaser[i].Draw(screen);
						
						if (sauserLaser[i].CheckCollision(brian->GetBasePos(), brian->m_Size))
						{
							life[--lives].SetAlive(false);
							brian->SetBasePos(basePos);
							brian->SetForce((0.0f, 0.0f));
						}
						
					}


					//Player laser to sauser collision check
					for (int j = 0; j < laserSize; j++)
					{
						if (laser[j].m_Fired == true)
							if (sauser[i].CheckCollision(laser[j].GetBasePos(), laser[j].m_Size))
								laser[j].m_Fired = false;
					}

					sauser[i].Update(deltaTime);
					sauser[i].Draw(screen);
					sauser[i].ScreenWrap();
				}
			}

			for (int i = 0; i < liveSize; i++)
			{
				if(life[i].GetAlive())
					life[i].Draw(screen);
			}

			bool asteroidsAlive = false;
			//Loop through all asteroids, update / draw and detect collision
			for (int i = 0; i < asteroidSize; i++)
			{
				if (asteroid[i].m_Alive == true)
				{
					asteroid[i].Update(deltaTime);
					asteroid[i].Draw(screen);
					asteroidsAlive = true;

					for (int j = 0; j < laserSize; j++)
					{
						if (laser[j].m_Fired == true)
						{
							if (asteroid[i].CheckCollision(laser[j].GetBasePos(), laser[j].m_Size))
							{
								asteroid[i].Split(asteroid, laser[j].GetRadius(), (static_cast<unsigned int>(randomSeed) + seedIncrease));
								seedIncrease += 3;

								laser[j].m_Fired = false;
								switch (asteroid[i].m_Size)
								{
								case 20: score += 400;
									break;
								case 15: score += 1200;
									break;
								case 10: score += 1600;
									break;
								default: //Don't do anything
									break;
								}
							}
						}
					}
					
					if (asteroid[i].CheckCollision(brian->GetBasePos(), brian->m_Size))
					{
						life[--lives].SetAlive(false);
						brian->SetBasePos(basePos);
						brian->SetForce((0.0f, 0.0f));
					}
					
					asteroid[i].ScreenWrap();
				}
			}

			if (asteroidsAlive == false && sausersAlive == false)
			{
				SetWave(asteroid, sauser, ++wave, 3);
			}

			brian->ScreenWrap();
		}
		else if (play && wave > 10) //Win
		{
			screen->Centre("You Win!", 200, 0xFFFFFF);
			screen->Centre(scoreBuffer, 230, 0xFFFFFF);
			screen->Centre("Press ENTER to play again", 280, 0xFFFFFF);

			if (keyPressEnter)
			{
				Reset();
			}
		}
		else if(play && lives <= 0) //Lose
		{
			screen->Centre("Game Over!", 200, 0xFFFFFF);
			screen->Centre(scoreBuffer, 230, 0xFFFFFF);
			screen->Centre("Press ENTER to play again", 280, 0xFFFFFF);
			
			if (keyPressEnter) 
			{
				Reset();
			}
		}
		else //Start
		{
			//option screen
			screen->Centre("Asteroids", 200, 0xF0000F);
			screen->Centre("Press ENTER to start", 230, 0xFFFFFF);

			if (keyPressEnter)
			{
				play = true;
				SetWave(asteroid, sauser, ++wave, 1);
			}
		}
	}

	void Game::Reset()
	{
		wave = 0;
		score = 0;
		lives = 3;
		seedIncrease = 0;
		brian->SetBasePos(basePos);
		brian->SetForce((0.0f, 0.0f));
		SetWave(asteroid, sauser, ++wave, 2);
		for (int i = 0; i < lives; i++)
		{
			if (i < 4)
				life[i].SetAlive(true);
			else
				life[i].SetAlive(false);
		}
	}

	void Game::SetWave(Asteroid* asteroid, Sauser* sauser, int wave, int state)
	{
		unsigned int randomSetSeed = static_cast<unsigned int>(randomSeed * 1000);

		switch (state)
		{
		case 1: //Start
		{
			for (int i = 0; i < wave; i++)
			{
				//set asteroid value - new pos and set them alive
				asteroid[i].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease);
				seedIncrease += 22;
			}

			if (wave == 1)
			{
				sauser[wave - 1].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease, 30);
				seedIncrease += 7;
			}
		}
			break;
		case 2: //Reset
		{
			for (int i = 0; i < asteroidSize; i++)
			{
				asteroid[i].m_Alive = false;
			}

			for (int i = 0; i < sauserSize; i++)
			{
				sauser[i].m_Alive = false;
			}

			for (int i = 0; i < wave; i++)
			{
				//set asteroid value - new pos and set them alive
				asteroid[i].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease);
				seedIncrease += 16;
			}
		}
			break;
		case 3: //Next wave
		{
			for (int i = 0; i < wave; i++)
			{
				//set asteroid value - new pos and set them alive
				asteroid[i].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease);
				seedIncrease += 31;
			}

			if (wave >= 10)
			{
				for (int i = 0; i < 3; i++)
				{
					sauser[i].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease, 10);
					seedIncrease += 7;
				}
			}
			else if (wave >= 7)
			{
				for (int i = 0; i < 3; i++)
				{
					if (i == 0)
						sauser[i].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease, 25);
					else
						sauser[i].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease, 10);
						
					seedIncrease += 7;
				}
			}
			else if (wave >= 4)
			{
				for (int i = 0; i < 2; i++)
				{
					if (i == 0)
						sauser[i].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease, 25);
					else
						sauser[i].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease, 10);

					seedIncrease += 7;
				}
			}
			else if (wave >= 2)
			{
				for (int i = 0; i < 1; i++)
				{
					sauser[i].SetValues(brian->GetBasePos(), true, randomSetSeed + seedIncrease, 25);
					seedIncrease += 7;
				}
			}
		}
			break;
		default: //Do nothing
			break;
		}

	}
};