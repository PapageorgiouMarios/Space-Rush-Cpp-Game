#pragma once
#include "graphics.h"
#include "enemy.h"

class Bullet : public GameObject, public Collidable
{
	float b_x = NULL;
	
	float b_y = NULL;

	float b_speed;

	int b_damage;


public:
	void update();

	void draw();

	void init();

	float get_bullet_Y();

	float get_bullet_X();

	void set_bullet_Y(float y);

	void set_bullet_X(float x);

	void set_Bullet_Speed(float s) {

		b_speed = s;
	}

	float get_Bullet_Speed() {

		return b_speed;
	}
	 

	bool out_of_bounds();

	Disk getCollisionHull() const override;

	Bullet();

	~Bullet();


};
