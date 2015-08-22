#ifndef I_GAME_OBJECT_H
#define I_GAME_OBJECT_H

class Camera;

class IGameObject
{
public:
	virtual ~IGameObject() {}

	virtual void update() = 0;
	virtual void render(Camera& camera) = 0;
};

#endif /* I_GAME_OBJECT_H */
