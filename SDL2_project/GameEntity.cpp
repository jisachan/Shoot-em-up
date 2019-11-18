#include "GameEntity.h"

GameEntity::GameEntity(Vector2D pos) {

	mPos = pos;
	mRotation = 0.0f;
	mActive = true;
	mParent = NULL;
	mScale = VECTOR2D_ONE;
}

GameEntity::~GameEntity()
{
	mParent = nullptr;
}

void GameEntity::SetPos(Vector2D pos)
{
	mPos = pos;
}

Vector2D GameEntity::GetPos(SPACE space)
{
	if (space == local || mParent == NULL)
		return mPos;

	Vector2D parentScale = mParent->GetScale(world);

	//The object's local position is rotated by the parent's rotation
	//The final position also depends on the parent's scale (if the parent is scaled up, the object should be further away from the parent)
	Vector2D childPos = Vector2D(mPos.x * parentScale.x, mPos.y * parentScale.y);
	Vector2D rotPos = RotateVector(childPos, mParent->GetRotation(local));

	return mParent->GetPos(world) + rotPos;
}

void GameEntity::SetRotation(float rotation)
{
	mRotation = rotation;

	if (mRotation > 360.0f)
		mRotation -= 360.0f;

	if (mRotation < 0.0f)
		mRotation += 360.0f;

	// I don't get this. why?
	//if (mRotation > 360.0f) {

	//	int mul = mRotation / 360;
	//	mRotation -= 360.0f * mul;

	//}
	//else if (mRotation < 0.0f) {

	//	int mul = (mRotation / 360) - 1;
	//	mRotation -= 360.0f * mul;
	//}
}

float GameEntity::GetRotation(SPACE space)
{
	if (space == local || mParent == nullptr)
		return mRotation;

	return mParent->GetRotation(world) + mRotation;
}

void GameEntity::SetScale(Vector2D scale) 
{
	mScale = scale;
}

Vector2D GameEntity::GetScale(SPACE space) 
{
	if (space == local || mParent == nullptr)
		return mScale;

	Vector2D scale = mParent->GetScale(world);
	scale.x *= mScale.x;
	scale.y *= mScale.y;

	return scale;
}

void GameEntity::SetActive(bool active)
{
	mActive = active;
}

bool GameEntity::GetActive()
{
	return mActive;
}

void GameEntity::SetParent(GameEntity* parent)
{
	//If the parent is removed, The Position/Rotation/Scale are the GameEntity's world values, to keep the object looking the same after the removal of the parent;
	if (parent == nullptr) 
	{
		mPos = GetPos(world);
		mScale = GetScale(world);
		mRotation = GetRotation(world);
	}
	else
	{
		//If the object already has a parent, remove the current parent to get it ready to be the child for the new parent
		if (mParent != NULL)
			SetParent(NULL);

		Vector2D parentScale = parent->GetScale(world);

		//Setting the local position to be relative to the new parent (while maintaining the same world position as before)
		Vector2D distance = GetPos(world) - parent->GetPos(world);
		mPos = RotateVector(distance, -parent->GetRotation(world));
		mPos.x /= parentScale.x;
		mPos.y /= parentScale.y;

		//Setting the local rotation to be relative to the new parent (while maintaining the same world rotation as before)
		mRotation = mRotation - parent->GetRotation(world);

		//Setting the new scale to be relative to the new parent (while maintaining the same world scale as before)
		mScale = Vector2D(mScale.x / parentScale.x, mScale.y / parentScale.y);
	}

	mParent = parent;
}

GameEntity* GameEntity::GetParent()
{
	return mParent;
}

void GameEntity::Translate(Vector2D vec, SPACE space)
{
	//"local" space is for the objects that rotate.
	//"world" space is for the objects that don't rotate.
	if (space == world) {
		mPos += vec;
	}
	else
	{
		mPos += RotateVector(vec, GetRotation()); //"Rotation" returns "world rotation" by default
	}
}

void GameEntity::Rotate(float amount) 
{
	mRotation += amount;
}

void GameEntity::Update()
{

}

void GameEntity::Render()
{

}
