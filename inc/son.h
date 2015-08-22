#ifndef SON_H
#define SON_H
#pragma once

#include <vector>
#include <map>

#include "texture.h"
#include "rect.h"
#include "animatedSprite.h"

#include "iGameObject.h"
#include "iCollidable.h"

class Camera;

class Son : public IGameObject
{
public:
	Son();

	virtual void update();
	virtual void render(Camera& camera);

	void addCollide(ICollidable& object);

	void setPos(int x, int y);

	bool isOnGround() const { return isOnGround_; };
private:
	enum class State
	{
		Standing,
		Walking,
		Jumpping,
		Attacking
	};

	Texture sonTexture_;
	AnimatedSprite sonWalk_;
	AnimatedSprite sonStand_;
	AnimatedSprite sonJump_;
	AnimatedSprite sonAttack_;;
	AnimatedSprite* currentSprite_;
	std::map<State, AnimatedSprite*> animatedSprites_;

	Rect posRect_;
	State currentState_;

	float posX_, posY_;
	float velX_, velY_;
	float accX_, accY_;

	bool isOnGround_;

	std::vector<ICollidable*> collides_;

	void updateX_(ICollidable& collidable);
	void updateY_(ICollidable& collidable);
	void checkWallAround_(ICollidable& collidable);
};

#endif /* SON_H */
