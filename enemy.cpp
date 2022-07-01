#include "enemy.h"
#include "graphics.h"
#include "config.h"

void Enemy::update()
{
	pos_x += direction* getSpeed() * graphics::getDeltaTime() / 10.0f;

	if (pos_x < 30) direction = 1;

	if (pos_x > CANVAS_WIDTH - 30) direction = -1;

}

void Enemy::draw()
{

	float glow = 0.4f + 0.3f * sinf(graphics::getGlobalTime() / 30);
	
	
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "slugger1.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(getXE(),getYE(),40,40,br);
	graphics::resetPose();
 
	 
}

void Enemy::draw2()
{

	float glow = 0.4f + 0.3f * sinf(graphics::getGlobalTime() / 30);


	graphics::Brush br;

	 
	br.texture = std::string(ASSET_PATH) + "slugger3.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(getXE(), getYE(), 40, 40, br);
	
	graphics::resetPose();

 
}

void Enemy::draw3()
{

	float glow = 0.4f + 0.3f * sinf(graphics::getGlobalTime() / 30);


	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "slugger2.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(getXE(), getYE(), 40, 40, br);
	graphics::resetPose();

}


void Enemy::init()
{
	//pos_x = CANVAS_WIDTH / 2;
	//pos_y = CANVAS_HEIGHT - CANVAS_HEIGHT * 0.8;

}

Disk Enemy::getCollisionHull() const
{
	Disk enemy_disk;

	enemy_disk.cx = pos_x;

	enemy_disk.cy = pos_y;

	enemy_disk.radius = 18;

	return enemy_disk;
}

Enemy::Enemy()
{
	init();
}

Enemy::~Enemy()
{
}