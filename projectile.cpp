#include "projectile.h"
#include "graphics.h"
#include "config.h"
#include "game.h"

float Projectile::get_projectile_Y() {

	return pr_y;
}

float Projectile::get_projectile_X()
{
	return pr_x;
}

void Projectile::update()
{

	pr_y -= speed * graphics::getDeltaTime() / 11.f;


}

 
void Projectile::draw()
{
	graphics::Brush br;

	graphics::setOrientation(90.f);
	
	br.texture = std::string(ASSET_PATH) + "bullet1.png";
	
	br.outline_opacity = 0.0f;
	
	graphics::drawRect(pr_x, pr_y, 26, 26, br);

	br.texture = "";

	float glow = 0.4f + 0.3f * sinf(graphics::getGlobalTime() / 30);

	br.fill_color[0] = 0.2f;
	br.fill_color[1] = 0.6f;
	br.fill_color[2] = 1.0f + glow * 0.5f; 0.2f;
	br.fill_secondary_color[0] = 0.1f;
	br.fill_secondary_color[1] = 0.25f;
	br.fill_secondary_color[2] = 0.7f;
	br.fill_opacity = 0.5f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	br.outline_opacity = 0.0f;

	graphics::drawDisk(pr_x, pr_y, 16, br);
	
	graphics::resetPose();

}

void Projectile::init()
{

	pr_y = CANVAS_HEIGHT / 2 + 230;
	
	speed = 4.5f;

	
}

Disk Projectile::getCollisionHull() const
{
	Disk projectile_disk;

	projectile_disk.cx = pr_x;

	projectile_disk.cy = pr_y;

	projectile_disk.radius = 12;

	return projectile_disk;
}

Projectile::Projectile()
{
	init();
}

Projectile::~Projectile(){

}