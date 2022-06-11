#pragma once

#include "ship.h"
#include "laser.h"
#include "asteroid.h"
#include "sauser.h"
#include "life.h"

namespace Tmpl8 {

class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }
	void KeyA(int key) { keyPressA = key; };
	void KeyD(int key) { keyPressD = key; };
	void KeyW(int key) { keyPressW = key; };
	void KeySpace(int key) { keyPressSpace = key; };
	void KeyEnter(int key) { keyPressEnter = key; };
	void SetWave(Asteroid* asteroid, Sauser* sauser, int wave, int state);
	void Reset();
private:
	Surface* screen;
	int keyPressA;
	int keyPressD;
	int keyPressW;
	int keyPressSpace;
	int keyPressEnter;

	//Moved all variables here so they are not global
	//Array size
	const int asteroidSize = 30; //Changed from 70 to 30. Removing the small asteroids
	const int sauserSize = 3;
	const int laserSize = 15;
	const int liveSize = 5;
	const enum keys { A = 1, D, W, SPACE };
	char scoreBuffer[1024];
	char waveBuffer[1024];

	//Gameplay variables
	int lastFired;
	int keyPress;
	int wave;
	bool play;
	int score;
	int oldScore;
	int lives;
	int state;
	float randomSeed;
	int seedIncrease;

	vec2 basePos;
	float radius;

	//Objects
	Ship* brian;
	Laser* laser;
	Asteroid* asteroid;
	Sauser* sauser;
	Laser* sauserLaser;
	Life* life;
};

}; // namespace Tmpl8