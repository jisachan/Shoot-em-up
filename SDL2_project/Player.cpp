#include "Player.h"

Player::Player() {
	mTimer = Timer::Instance();
	mInput = InputManager::Instance();

	mVisible = false;
	mAnimating = false;

	mScore = 0;
	mLives = 2;

	mShip = new Texture("Snakey.png");
	mShip->SetParent(this);
	mShip->SetPos(VECTOR2D_ZERO);

	mMoveSpeed = 200.0f;
	//set the bounds for player movement.
	//player can move between 0 on the x and up to 900.
	mMoveBounds = Bounds(44, 900, 44, 850);
	//mMoveBoundsX = Vector2D(44.0f, 900.0f);
	//mMoveBoundsY = Vector2D();

	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		mProjectiles[i] = new Projectile();
	}
}

Player::~Player()
{
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		delete mProjectiles[i];
		mProjectiles[i] = nullptr;
	}
	delete mShip;
	mShip = nullptr;
	mInput = nullptr;
	mTimer = nullptr;
}

void Player::HandleMovement() {
	if (mInput->KeyDown(SDL_SCANCODE_RIGHT)) {
		Translate(VECTOR2D_RIGHT * mMoveSpeed * mTimer->DeltaTime(), world);
	}
	if (mInput ->KeyDown(SDL_SCANCODE_LEFT)) {

		Translate(VECTOR2D_LEFT * mMoveSpeed * mTimer->DeltaTime(), world);
	}
	if (mInput->KeyDown(SDL_SCANCODE_UP)) {

		Translate(VECTOR2D_UP * mMoveSpeed * mTimer->DeltaTime(), world);
	}
	if (mInput->KeyDown(SDL_SCANCODE_DOWN)) {

		Translate(VECTOR2D_DOWN * mMoveSpeed * mTimer->DeltaTime(), world);
	}
	
	Vector2D pos = GetPos(local);
	{
		if (pos.x < mMoveBounds.left) {
			pos.x = mMoveBounds.left;
		}
		else if (pos.x > mMoveBounds.right) {
			pos.x = mMoveBounds.right;
		}

		if (pos.y < mMoveBounds.up) {
			pos.y = mMoveBounds.up;
		}
		else if (pos.y > mMoveBounds.down) {
			pos.y = mMoveBounds.down;
		}

		SetPos(pos);
	}
}

void Player::HandleFiring()
{
	if (mInput->KeyPressed(SDL_SCANCODE_SPACE))
	{
		for (int i = 0; i < MAX_PROJECTILES; i++)
		{
			if (!mProjectiles[i]->GetActive())
			{
				mProjectiles[i]->Fire(GetPos());
				//Set firing audio file here.
				//mAudio->PlaySFX("nameoffile.wav");
				break;
			}
		}
	}
}

void Player::Visible(bool visible)
{
	mVisible = visible;
}

bool Player::IsAnimating()
{
	return mAnimating;
}

int Player::Score()
{
	return mScore;
}

int Player::Lives()
{
	return mLives;
}

void Player::AddScore(int change)
{
	mScore += change;
}

void Player::Update()
{
	if (mAnimating) {

	}
	else {
		if (GetActive()) {
			HandleMovement();
			HandleFiring();
		}
	}
	for(int i = 0; i<MAX_PROJECTILES; i++)
	{ 
		mProjectiles[i]->Update();
	}
}

void Player::Render()
{
	if (mVisible) {
		if (mAnimating) {

		}
		else {
			mShip->Render();
		}
	}
	for (int i = 0; i < MAX_PROJECTILES; i++)
	{
		mProjectiles[i]->Render();
	}
}

