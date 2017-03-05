#pragma once

namespace GameObjects {
	class Eagle;
	class Tank;
	class Missile;
}

class Collidable
{

public:
	virtual void collide(Collidable* collidable) = 0;

	virtual void collideWith(GameObjects::Eagle* eagle) = 0;
	virtual void collideWith(GameObjects::Tank* tank) = 0;
	virtual void collideWith(GameObjects::Missile* missile) = 0;
};