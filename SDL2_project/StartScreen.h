#ifndef _STARTSCREEN_H
#define _STARTSCREEN_H

#include "AnimatedTexture.h"
#include "InputManager.h"
#include "Player.h"

class StartScreen : public GameEntity {

private:
	Timer* mTimer;

	//Top bar entities
	GameEntity* mTopBar;
	Texture* mPlayerOne;
	Texture* mHiScore;
	Texture* mPlayerTwo;

	//Logo Entities
	Texture* mLogo;
	AnimatedTexture* mAnimatedLogo;

	//Play Mode Entities
	GameEntity* mPlayModes;
	Texture* mOnePlayerMode;
	Texture* mTwoPlayerMode;

	//Bottom Bar Entities
	GameEntity* mBotBar;
	Texture* mNamco; //company name
	Texture* mDates; //dates
	Texture* mRights; //copyrights etc

	//Screen Animation Variables
	Vector2D mAnimationStartPos;
	Vector2D mAnimationEndPos;
	float mAnimationTotalTime;
	float mAnimationTimer;
	bool mAnimationDone;

	//should be in the "PlayScreen.h"
	Player* mPlayer;

public:

	StartScreen();
	~StartScreen();

	void Update();
	void Render();

};
#endif
