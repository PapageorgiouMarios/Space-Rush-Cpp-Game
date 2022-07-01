#pragma once
#include "gameobject.h"
#include "config.h"

class Shield : public GameObject, public Collidable
{
	float pos_x, pos_y, size;
	
	int health;
	 

public:
	void update() override;
	
	void draw() override;

	void draw_state2();

	void draw_state3();
	 
	void init() override;
	
	void setP(float i, float j) {
		
		pos_x = i;
		pos_y = j;
	}

	float getX() {
		
		return pos_x;

	}

	float getY() {
		
		return pos_y;

	}

	float get_hp();

	void set_hp(float number1_30) {

		health = number1_30;
	}

	Disk getCollisionHull() const override;

	Shield();
	~Shield(); 
};
