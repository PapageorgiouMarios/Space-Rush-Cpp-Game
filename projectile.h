#pragma once
#include "player.h"
#include "graphics.h"


class Projectile: public GameObject, public Collidable
{
	float pr_x, pr_y;

	float speed;

	int damage;

	
public:
	void update() ;

	void draw();

	void init();
	
	float get_projectile_Y();

	float get_projectile_X();

	void set_projectile_X(float x) {

		pr_x = x;
	}

	bool shoot = false;

	bool out = false;

	Disk getCollisionHull() const override;
 
	Projectile();

	~Projectile();


};