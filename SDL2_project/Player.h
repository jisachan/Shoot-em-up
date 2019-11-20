#ifndef _PLAYER_H
#define _PLAYER_H
#include "AnimatedTexture.h"
#include "InputManager.h"
#include "MathHelper.h"
#include "Projectile.h"

class Player : public GameEntity {

private:

	Timer* mTimer;
	InputManager* mInput;

	bool mVisible; //true if player is visible on screen. will use to switch player on and off
	bool mAnimating; // stops player from moving if player gets killed etc.
	
	int mScore;
	int mLives; 

	Texture* mShip;

	float mMoveSpeed;
	Vector2D mMoveBounds;

	static const int MAX_PROJECTILES = 15;
	Projectile* mProjectiles[MAX_PROJECTILES];

private:

	void HandleMovement();
	void HandleFiring();

public:

	Player();
	~Player();

	void Visible(bool visible);
	bool IsAnimating();

	int Score();
	int Lives(); //getter for lives

	void AddScore(int change);

	void Update();
	void Render();
};
#endif
