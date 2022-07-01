#pragma once
#include "gameobject.h"

class Enemy : public GameObject, public Collidable{

	float pos_x, pos_y, speed;
	
	int direction=-1;

public :
	void update() override;
	
	void draw() override;

	void draw2();

	void draw3();

	void init() override;

	void setPE(float i, float j) {

		pos_x = i;
		pos_y = j;
	}

	float getXE() {

		return pos_x;

	}

	void setSpeed(float temp_speed) {

		speed = temp_speed;
		 
	}
	
	float getSpeed() {

		return speed;

	}
	
	 
	float getYE() {

		return pos_y;

	}

	Disk getCollisionHull() const override;


	Enemy();
	~Enemy();
}; 