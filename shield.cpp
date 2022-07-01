#include "shield.h"
#include "graphics.h"
#include "config.h"

void Shield::update()
{

}

void Shield::draw()
{
	 
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "shield_state_1.png";


	br.outline_opacity = 0.f;



	graphics::setOrientation(-90.f);



	graphics::drawRect(getX(), getY(), 50, 190, br);

	graphics::resetPose();
 
}


void Shield::draw_state2()
{
	 
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "shield_state_2.png";


	br.outline_opacity = 0.f;

	graphics::setOrientation(-90.f);

	graphics::drawRect(getX(), getY(), 50, 190, br);

	graphics::resetPose();

 
}

void Shield::draw_state3()
{
	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "shield_state_3.png";


	br.outline_opacity = 0.f;

	graphics::setOrientation(-90.f);

	graphics::drawRect(getX(), getY(), 50, 190, br);

	graphics::resetPose();
 
 
}


void Shield::init()
{
}

float Shield::get_hp()
{
	return health;
}

Disk Shield::getCollisionHull() const
{
	Disk shield_disk;

	shield_disk.cx = pos_x;

	shield_disk.cy = pos_y + 50;

	shield_disk.radius = 69;

	return shield_disk;
}

Shield::Shield()
{
	init();
}

Shield::~Shield()
{
}