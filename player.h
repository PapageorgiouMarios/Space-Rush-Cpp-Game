#pragma once
#include "gameobject.h"
#include "config.h"

class Player : public GameObject, public Collidable
{
	float speed = 5.0f;
	
	float pos_x = CANVAS_WIDTH / 2; 

	float pos_y = CANVAS_HEIGHT / 2 + 310;

	float health = 6.f;


public:
	void update() override;

	void draw_hp(float hp);

	float get_player_x();

	float get_player_hp();

	void set_hp(float number1_6) {

		health = number1_6;
	}

    void draw() override;
	void init() override; 

	Disk getCollisionHull() const override;
 
};