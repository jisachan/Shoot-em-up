#include "Projectile.h"

Projectile::Projectile() {
	mTimer = Timer::Instance();

	mSpeed = 800.0f;

	mTexture = new Texture("Projectiley.png");
	mTexture->SetParent(this);
	mTexture->SetScale(VECTOR2D_ONE * 0.1);
	mTexture->SetPos(VECTOR2D_ZERO);

	//rotation example
	Rotate(45);

	Reload();
}

Projectile::~Projectile() {
	
	delete mTexture;
	mTexture = nullptr;

	mTimer = nullptr;
}

void Projectile::Fire(Vector2D pos)
{
	SetPos(pos);
	SetActive(true);
}

void Projectile::Reload()
{
	SetActive(false);
}

void Projectile::Update()
{
	if (GetActive()) {
		Translate(VECTOR2D_RIGHT*mSpeed*mTimer->DeltaTime(), local);

		Vector2D pos = GetPos();
		if (pos.x < -OFFSCREEN_BUFFER || pos.x > Graphics::Instance()->SCREEN_WIDTH + OFFSCREEN_BUFFER) {
			Reload();
		}
	}
}

void Projectile::Render()
{
	if (GetActive())
	{
		mTexture->Render();
	}
}
