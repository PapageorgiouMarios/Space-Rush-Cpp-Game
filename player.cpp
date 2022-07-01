#include "player.h"
#include "graphics.h"


void Player::update()
{
	if (graphics::getKeyState(graphics::SCANCODE_A) || graphics::getKeyState(graphics::SCANCODE_LEFT)) {

		pos_x -= speed * graphics::getDeltaTime() / 10.0f;
}
	if (graphics::getKeyState(graphics::SCANCODE_D) || graphics::getKeyState(graphics::SCANCODE_RIGHT)) {

		pos_x += speed * graphics::getDeltaTime() / 10.0f;
	}
	
    if (pos_x < 40) pos_x = 40;
	
	if (pos_x > CANVAS_WIDTH - 40) pos_x = CANVAS_WIDTH - 40;

}

 

void Player::draw_hp(float hp)
{
	 
	if (hp == 6) {
		
		graphics::Brush br;

		graphics::setOrientation(0.f);

		br.texture = std::string(ASSET_PATH) + "health_6.png";


		br.outline_opacity = 0.f;

		graphics::drawRect(90, 30, 180, 40, br);

		graphics::resetPose();

	}

	if (hp == 5) {

		graphics::Brush br;

		graphics::setOrientation(0.f);

		br.texture = std::string(ASSET_PATH) + "health_5.png";


		br.outline_opacity = 0.f;

		graphics::drawRect(90, 30, 180, 40, br);

		graphics::resetPose();
	}

	if (hp == 4) {

		graphics::Brush br;

		graphics::setOrientation(0.f);

		br.texture = std::string(ASSET_PATH) + "health_4.png";


		br.outline_opacity = 0.f;

		graphics::drawRect(90, 30, 180, 40, br);

		graphics::resetPose();

	}

	if (hp == 3) {

		graphics::Brush br;

		graphics::setOrientation(0.f);

		br.texture = std::string(ASSET_PATH) + "health_3.png";


		br.outline_opacity = 0.f;

		graphics::drawRect(90, 30, 180, 40, br);

		graphics::resetPose();

	}

	if (hp == 2) {

		graphics::Brush br;

		graphics::setOrientation(0.f);

		br.texture = std::string(ASSET_PATH) + "health_2.png";


		br.outline_opacity = 0.f;

		graphics::drawRect(90, 30, 180, 40, br);

		graphics::resetPose();

	}

	if (hp == 1) {

		graphics::Brush br;

		graphics::setOrientation(0.f);

		br.texture = std::string(ASSET_PATH) + "health_1.png";


		br.outline_opacity = 0.f;

		graphics::drawRect(90, 30, 180, 40, br);

		graphics::resetPose();

	}
	 
}

float Player::get_player_x()
{
	return pos_x;
}

float Player::get_player_hp()
{
	return health;
}

void Player::draw()
{
	float glow = 0.4f + 0.3f * sinf(graphics::getGlobalTime() / 30);
	 
	graphics::Brush br;
	br.texture = std::string(ASSET_PATH) + "bw_spaceship.png";
	br.outline_opacity = 0.0f;
	graphics::drawRect(pos_x, pos_y- 30, 65, 65, br);
	br.texture = "";

	graphics::setOrientation(180);
	br.texture = std::string(ASSET_PATH) + "flame.png";
	br.outline_opacity = 0.0f;
	 
	
	
	graphics::drawRect(pos_x, pos_y + 11, 20, 20 , br);
	br.texture = "";


	br.fill_color[0] = 1.0f;
	br.fill_color[1] = 0.5f + glow*0.5f ;
	br.fill_color[2] = 0.0f;
	br.fill_secondary_color[0] = 0.85f;
	br.fill_secondary_color[1] = 0.3f;
	br.fill_secondary_color[2] = 0.3f;
	br.fill_opacity = 0.75f;
	br.fill_secondary_opacity = 0.0f;
	br.gradient = true;
	br.outline_opacity = 0.0f;

	graphics::drawDisk(pos_x, pos_y+4, 24, br);


}

 
void Player::init()
{
}

Disk Player::getCollisionHull() const
{
	Disk player_disk;
	
	player_disk.cx = pos_x;
	
	player_disk.cy = pos_y - 27;
	
	player_disk.radius = 33;

	return player_disk;
	 
}
