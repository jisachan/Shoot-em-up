#include "StartScreen.h"

StartScreen::StartScreen() {

	mTimer = Timer::Instance();
	//Top Bar Entities
	mTopBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, 80.0f)); //center of the screen, a bit lower than the top
	//font stuff. what does it say, which font file, which size, which color
	mPlayerOne = new Texture("1UP", "emulogic.ttf", 32, { 200,0,0 });
	mHiScore = new Texture("HIGH-SCORE", "emulogic.ttf", 32, { 200,0,0 });
	mPlayerTwo = new Texture("2UP", "emulogic.ttf", 32, { 200,0,0 });

	mPlayerOne->SetParent(mTopBar);
	mHiScore->SetParent(mTopBar);
	mPlayerTwo->SetParent(mTopBar);

	//change x value of 1UP to be 35%  more to the left. don't change y value.
	mPlayerOne->SetPos(Vector2D(-Graphics::Instance()->SCREEN_WIDTH * 0.35f, 0.0f));
	//change x value of HIGH SCORE to be a bit more to the left. don't change y value.
	mHiScore->SetPos(Vector2D(-30.0f, 0.0f));
	//change x value of 2UP to be 20%  more to the right. don't change y value.
	mPlayerTwo->SetPos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.25f, 0.0f));

	mTopBar->SetParent(this);

	//Logo Entities
	mLogo = new Texture("LogoGwaengDark.png", 0, 0, 287, 70);
	//file name, x pos, y pos, x size, y size, nr of frames to switch between, time to show each frame, where to cut the pic (vertical cut)
	mAnimatedLogo = new AnimatedTexture("LogoGwaengDark.png", 0, 0, 287, 70, 3, 0.4f, AnimatedTexture::vertical);

	mLogo->SetPos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));
	mAnimatedLogo->SetPos(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.32f));

	mLogo->SetParent(this);
	mAnimatedLogo->SetParent(this);


	//Play Mode Entities
	mPlayModes = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.55f));
	mOnePlayerMode = new Texture("1 Player", "emulogic.ttf", 32, { 230,230,230 });
	mTwoPlayerMode = new Texture("2 Player", "emulogic.ttf", 32, { 230, 230, 230 });

	mOnePlayerMode->SetParent(mPlayModes);
	mTwoPlayerMode->SetParent(mPlayModes);

	mOnePlayerMode->SetPos(Vector2D(0.0f, -35.0f));
	mTwoPlayerMode->SetPos(Vector2D(0.0f, 35.0f));

	mPlayModes->SetParent(this);

	//Bottom Bar Entities
	mBotBar = new GameEntity(Vector2D(Graphics::Instance()->SCREEN_WIDTH * 0.5f, Graphics::Instance()->SCREEN_HEIGHT * 0.7f));
	mNamco = new Texture("namcot", "emulogic.ttf", 36, { 200,0,0 });
	mDates = new Texture("1981 1985 NAMCO LTD.", "emulogic.ttf", 32, { 230,230,230 });
	mRights = new Texture("ALL RIGHTS RESERVED", "emulogic.ttf", 32, { 230,230,230 });

	//set as children t o stuff
	mNamco->SetParent(mBotBar);
	mDates->SetParent(mBotBar);
	mRights->SetParent(mBotBar);

	mNamco->SetPos(VECTOR2D_ZERO);
	mDates->SetPos(Vector2D(0.0f, 90.0f));
	mRights->SetPos(VECTOR2D_ZERO);

	mBotBar->SetParent(this);

	//Screen Animation Variables
	mAnimationStartPos = Vector2D(0.0f, Graphics::Instance()->SCREEN_HEIGHT);
	mAnimationEndPos = VECTOR2D_ZERO;
	mAnimationTotalTime = 5.0f;
	mAnimationTimer = 0.0f;
	mAnimationDone = false;

	SetPos(mAnimationStartPos);

	//should be in the "PlayScreen.cpp"
	mPlayer = new Player();
	mPlayer->SetParent(this);
	mPlayer->SetScale(VECTOR2D_ONE * 0.32);
	mPlayer->SetPos(Vector2D(50.0f, Graphics::Instance()->SCREEN_HEIGHT / 2));
	mPlayer->Visible(true);
}

StartScreen::~StartScreen() {
	//should be in the "PlayScreen.cpp"
	delete mPlayer;
	mPlayer = nullptr;

	//Freeing Bot Bar Entities
	delete mRights;
	mRights = nullptr;
	delete mDates;
	mDates = nullptr;
	delete mNamco;
	mNamco = nullptr;
	delete mBotBar;
	mBotBar = nullptr;

	//Freeing Play Mode Entities
	delete mTwoPlayerMode;
	mTwoPlayerMode = nullptr;
	delete mOnePlayerMode;
	mOnePlayerMode = nullptr;
	delete mPlayModes;
	mPlayModes = nullptr;

	//Freeing Logo Entities
	delete mAnimatedLogo;
	mAnimatedLogo = nullptr;
	delete mLogo;
	mLogo = nullptr;

	//Freeing Top Bar Entities
	delete mPlayerTwo;
	mPlayerTwo = nullptr;
	delete mHiScore;
	mHiScore = nullptr;
	delete mPlayerOne;
	mPlayerOne = nullptr;
	delete mTopBar;
	mTopBar = nullptr;
}

void StartScreen::Update() {

	if (!mAnimationDone) {

		mAnimationTimer += mTimer->DeltaTime();
		SetPos(Lerp(mAnimationStartPos, mAnimationEndPos, mAnimationTimer / mAnimationTotalTime));

		if (mAnimationTimer >= mAnimationTotalTime)
		{
			mAnimationDone = true;
		}
	}
	else {
		mAnimatedLogo->Update();
	}

	mPlayer->Update();
}

//Rendering is what shows stuff on the screen!!!
void StartScreen::Render() {
	mPlayerOne->Render();
	mHiScore->Render();
	mPlayerTwo->Render();

	if (!mAnimationDone)
	{
		mLogo->Render();
	}
	else
	{
		//These are put in layer order. 
		//The first sentence is on the bottom layer.
		//The last sentence is on the top layer.
		mAnimatedLogo->Render();
	}

	mOnePlayerMode->Render();
	mTwoPlayerMode->Render();

	mNamco->Render();
	mDates->Render();
	mRights->Render();

	mPlayer->Render();
}
