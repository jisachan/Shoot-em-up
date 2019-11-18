#pragma once

#include "Texture.h"
#include "Timer.h"

class Projectile : public GameEntity {

private:

	//because we need the bullet to disappear when it is offscreen
	//if it is 10pixels off screen, we can make it disappear
	const int OFFSCREEN_BUFFER = 10;

	Timer* mTimer;

	float mSpeed;

	Texture* mTexture;

public:

	Projectile();
	~Projectile();

	void Fire(Vector2D pos);
	void Reload();

	void Update();
	void Render();


};