#include "bullet.h"
#include "graphics.h"
#include "config.h"
#include "enemy.h"
 


 

void Bullet::update()
{

	 
	b_y += (get_Bullet_Speed()) * graphics::getDeltaTime() / 10.f;
	 

 


}

void Bullet::draw()
{
	graphics::Brush br;

	graphics::setOrientation(90.f);

	br.texture = std::string(ASSET_PATH) + "bullet3.png";

	br.outline_opacity = 0.0f;

	

	graphics::drawRect(b_x,get_bullet_Y(), 30, 30, br);

	br.texture = "";

	float glow = 0.4f + 0.3f * sinf(graphics::getGlobalTime() / 30);

	br.fill_color[0] = 1.0f + glow * 0.6f;
	br.fill_color[1] = 0.2f;
	br.fill_color[2] = 0.2f;
	br.fill_secondary_color[0] = 0.8f;
	br.fill_secondary_color[1] = 0.2f;
	br.fill_secondary_color[2] = 0.1f;
	br.fill_opacity = 0.5f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	br.outline_opacity = 0.0f;

	graphics::drawDisk(b_x, b_y, 16, br);

	graphics::resetPose();
 
}

void Bullet::init()
{
	b_y = get_bullet_Y();
	
	b_x = get_bullet_X();

	//b_speed = 2.0f;

 
}
 

void Bullet::set_bullet_Y(float y)
{
	b_y = y;
}

Disk Bullet::getCollisionHull() const
{
	Disk bullet_disk;

	bullet_disk.cx = b_x;

	bullet_disk.cy = b_y;

	bullet_disk.radius = 12;

	return bullet_disk;
}

float Bullet::get_bullet_Y()
{
	return b_y;
}

void Bullet::set_bullet_X(float x)
{
	b_x = x;
}

float Bullet::get_bullet_X()
{
	return b_x;
}

 
bool Bullet::out_of_bounds()
{

	if (b_y == CANVAS_HEIGHT + 20) {

		return true;
	}
}

 
Bullet::Bullet()
{
	init();
}

Bullet::~Bullet()
{
}
