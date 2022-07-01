#include "game.h"
#include "graphics.h"
#include "config.h"
#include "shield.h"
#include "projectile.h"
#include "bullet.h"
 
void Game::update()
{
	 
	if (status == MENU_SCREEN) {

		updateMenuScreen();
	}

	if (status == GAMEPLAY_SCREEN) {

		updateGameplayScreen();
	}

	if (status == GAME_OVER_SCREEN) {

		updateGameOverScreen();
	}
 
}
 
void Game::draw()
{
	if (status == MENU_SCREEN) {

		drawMenuScreen();
	}

	if (status == GAMEPLAY_SCREEN) {

		drawGameplayScreen();
	}

	if (status == GAME_OVER_SCREEN) {

		drawGameOverScreen();
	}
 
}

void Game::updateMenuScreen()
{
	if (graphics::getKeyState(graphics::SCANCODE_RETURN)) {

		if (graphics::getGlobalTime() > 1000) {
			 
			status = GAMEPLAY_SCREEN;
			
		}
		 

	}
}

void Game::updateGameplayScreen()
{
	

	if (restart == true) {


		if (!player_created && graphics::getGlobalTime() > 200)
		{
			player = new Player();

			player_created = true;

			player->set_hp(remaining_health);


		}
		if (player)
		{
			player->update();

		}

		if (!enemies_spawned) { spawn_enemy_ship(); }

		if (enemies_spawned) {

			for (int i = 0; i < 55; i++) {

				if (multiple[i] != nullptr) {

					multiple[i]->update();
				}

			}

		}

		if (shields_created_once == false) { spawn_shields(); }

		shoot_pr();

		shoot_bull();

		if (remaining_enemies() == 0) {

			enemies_spawned = false;

			waves += 1;

			speed += 0.15f;

			b_speed += 0.15f;

			if (remaining_health < 6 && remaining_health > 0) {

				remaining_health += 1;

				player->set_hp(remaining_health);
			}

		}

		if (player != nullptr && player->get_player_hp() == 0) {

			graphics::playSound(std::string(ASSET_PATH) + "player_dead.wav", 0.5f, false);

			status = GAME_OVER_SCREEN;

			restart = false;
		}
	}
}

void Game::updateGameOverScreen()
{
	graphics::stopMusic();

	if (graphics::getKeyState(graphics::SCANCODE_C)) {

		if (graphics::getGlobalTime() > 1000) {


			delete player;
			player_created = false;


			remaining_health = 6;

			speed = 2.0f;

			waves = 1;

			float b_speed = 2.0f;

			for (int k = 0; k <= 54; k++) {

				delete multiple[k];
				multiple[k] = nullptr;
			}

			enemies_spawned = false;
			
			health_1 = 30;

			health_2 = 30;

			health_3 = 30;

			health_4 = 30;

			shield1 = new Shield();

			shield2 = new Shield();

			shield3 = new Shield();

			shield4 = new Shield();

			shield1->set_hp(health_1);

			shield2->set_hp(health_2);

			shield3->set_hp(health_3);

			shield4->set_hp(health_4);

			shield1->setP(CANVAS_WIDTH / 2 - 140, CANVAS_HEIGHT / 2 + 200);

			shield2->setP(CANVAS_WIDTH / 2 - 415, CANVAS_HEIGHT / 2 + 200);

			shield3->setP(CANVAS_WIDTH / 2 + 140, CANVAS_HEIGHT / 2 + 200);

			shield4->setP(CANVAS_WIDTH / 2 + 415, CANVAS_HEIGHT / 2 + 200);
 
			bool shield1_destroyed = false;

			bool shield2_destroyed = false;

			bool shield3_destroyed = false;

			bool shield4_destroyed = false;

			bool shields_created_once = false;

			bullet_hell.clear();

			enemy_bullet_hell.clear();

			graphics::Brush br;
 
			player_score = 0;

			restart = true;

			status = GAMEPLAY_SCREEN;

		}


	}
}

	//if (graphics::getKeyState(graphics::SCANCODE_ESCAPE)) {

		//graphics::destroyWindow();
	//}


void Game::drawMenuScreen()
{
	//draw background

	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "Menu_Screen.png";

	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::resetPose();
}

void Game::spawn_enemy_ship()
{
 
	for (int i = 0; i <= 10; i++) {

		multiple[i] = new Enemy();

		multiple[i]->setPE((80*i) - 880, CANVAS_HEIGHT/2 - 50);
		
		points[i] = 20;

	}
	for (int i = 11; i <= 21; i++) {

		multiple[i] = new Enemy();

		multiple[i]->setPE((80*i)- 1760, CANVAS_HEIGHT / 2 - 100);
		
		points[i] = 20;

	}
	for (int i = 22; i <= 32; i++) {

		multiple[i] = new Enemy();

		multiple[i]->setPE((80*i) - 2640, CANVAS_HEIGHT / 2 - 150);
		
		points[i] = 50;

	}
	for (int i = 33; i <= 43; i++) {

		multiple[i] = new Enemy();

		multiple[i]->setPE((80*i) - 3520, CANVAS_HEIGHT / 2 - 200);

		points[i] = 50;

	}
	for (int i = 44; i <= 54; i++) {

		multiple[i] = new Enemy();

		multiple[i]->setPE((80*i) - 4400, CANVAS_HEIGHT / 2 - 250);

		points[i] = 100;

	}

	for (int j = 0; j <= 54; j++) {

		multiple[j]->setSpeed(speed);
	}
	enemies_spawned = true;
 
}

void Game::drawGameplayScreen()
{
	//draw background

	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "bs.png";

	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_WIDTH, br);

	graphics::resetPose();


	//draw player
	if (player) { player->draw(); }

	//draw player hp

	if (player) { player->draw_hp(player->get_player_hp()); }

	//draw player's score
	init();
	if (player && restart == true) {

		char info1[40];

		sprintf_s(info1, "SCORE: %d", player_score);

		graphics::drawText(920, 50, 35, info1, br);

	}
	//draw wave

	if (player && restart == true) {

		char info1[40];

		sprintf_s(info1, "WAVE: %d", waves);

		graphics::drawText(CANVAS_WIDTH/2 - 100, 50, 35, info1, br);

	}

	//draw enemy
	if (enemies_spawned) {

		for (int i = 0; i <= 10; i++) {

			if (multiple[i] != nullptr) {

				multiple[i]->draw();
			}

		}

		for (int i = 11; i <= 21; i++) {

			if (multiple[i] != nullptr) {

				multiple[i]->draw();
			}
		}

		for (int i = 22; i <= 43; i++) {

			if (multiple[i] != nullptr) {

				multiple[i]->draw3();
			}
		}

		for (int i = 44; i <= 54; i++) {

			if (multiple[i] != nullptr) {

				multiple[i]->draw2();
			}
		}

	}

	//draw shield

	if (shield1_destroyed == false && shield1 != nullptr) {

		if (health_1 <= 30 && health_1 >= 21)
		{
			shield1->draw();
		}

		if (health_1 <= 20 && health_1 >= 11)
		{
			shield1->draw_state2();
		}

		if (health_1 <= 10 && health_1 >= 1)
		{
			shield1->draw_state3();
		}
	}
	if (shield2_destroyed == false && shield2 != nullptr) {

		if (health_2 <= 30 && health_2 >= 21)
		{
			shield2->draw();
		}

		if (health_2 <= 20 && health_2 >= 11)
		{
			shield2->draw_state2();
		}

		if (health_2 <= 10 && health_2 >= 1)
		{
			shield2->draw_state3();
		}
	}

	if (shield3_destroyed == false && shield3 != nullptr) {

		if (health_3 <= 30 && health_3 >= 21)
		{
			shield3->draw();
		}

		if (health_3 <= 20 && health_3 >= 11)
		{
			shield3->draw_state2();
		}

		if (health_3 <= 10 && health_3 >= 1)
		{
			shield3->draw_state3();
		}
	}

	if (shield4_destroyed == false && shield4 != nullptr) {

		if (health_4 <= 30 && health_4 >= 21)
		{
			shield4->draw();
		}

		if (health_4 <= 20 && health_4 >= 11)
		{
			shield4->draw_state2();
		}

		if (health_4 <= 10 && health_4 >= 1)
		{
			shield4->draw_state3();
		}
	}

	//draw projectile

	for (int i = 0; i < bullet_hell.size(); i += 53) {


		if (bullet_hell[i] != nullptr) {


			bullet_hell[i]->draw();


		}
	}

	for (int i = 0; i < enemy_bullet_hell.size(); i += 53) {

		if (enemy_bullet_hell[i]) {

			enemy_bullet_hell[i]->draw();
		}
	}

}

void Game::drawGameOverScreen()
{
	//draw background

	graphics::Brush br;

	br.texture = std::string(ASSET_PATH) + "Game_Over_Screen.png";

	br.outline_opacity = 0.0f;

	graphics::drawRect(CANVAS_WIDTH / 2, CANVAS_HEIGHT / 2, CANVAS_WIDTH, CANVAS_HEIGHT, br);

	graphics::resetPose();
}

void Game::spawn_shields() {

	shield1 = new Shield();
	
	shield1->setP(CANVAS_WIDTH / 2 - 140, CANVAS_HEIGHT / 2 + 200);

	shield1->set_hp(health_1);

	if (health_1 == 0) {

		graphics::playSound(std::string(ASSET_PATH) + "bangSmall.wav", 0.3f, false);
		delete shield1;
		shield1 = nullptr;
		shield1_destroyed == true;
	}

	 
	shield2 = new Shield();

	shield2->setP(CANVAS_WIDTH / 2 - 415, CANVAS_HEIGHT / 2 + 200);

	shield2->set_hp(health_2);

	if (health_2 == 0) {

		graphics::playSound(std::string(ASSET_PATH) + "bangSmall.wav", 0.3f, false);
		delete shield2;
		shield2 = nullptr;
		shield2_destroyed == true;
	}

	 

	shield3 = new Shield();

	shield3->setP(CANVAS_WIDTH / 2 + 140, CANVAS_HEIGHT / 2 + 200);

	shield3->set_hp(health_3);

	if (health_3 == 0) {

		graphics::playSound(std::string(ASSET_PATH) + "bangSmall.wav", 0.3f, false);
		delete shield3;
		shield3 = nullptr;
		shield3_destroyed == true;
	}

	 
	shield4 = new Shield();

	shield4->setP(CANVAS_WIDTH / 2 + 415, CANVAS_HEIGHT / 2 + 200);

	shield4->set_hp(health_4);

	if (health_4 == 0) {

		graphics::playSound(std::string(ASSET_PATH) + "bangSmall.wav", 0.3f, false);
		delete shield4;
		shield4 = nullptr;
		shield4_destroyed == true;
	}

	shields_created_once = true;
	 
}
void Game::shoot_pr()
{
 


	if (graphics::getKeyState(graphics::SCANCODE_SPACE)) {

		isFiring = true;

	
	}
	
 
	if (isFiring == true){

		pr = new Projectile();

		pr->set_projectile_X(player->get_player_x());

		bullet_hell.push_back(pr);

		isFiring = false;

	}

		for (int i = 0; i < bullet_hell.size(); i += 53) {

			if (bullet_hell[i] != nullptr) {
				 
				bullet_hell[i]->update();

				


				if (bullet_hell[i]->get_projectile_Y() < 20) {

					delete bullet_hell[i];
					bullet_hell[i] = nullptr;

				}
			}
		}

		for (int i = 0; i < bullet_hell.size(); i += 53) {

			if (bullet_hell[i] != nullptr) {

				if (Collision_Projectile_Shield(i, shield1) == true || Collision_Projectile_Shield(i, shield2) == true || Collision_Projectile_Shield(i, shield3) == true || Collision_Projectile_Shield(i, shield4) == true) {

					delete bullet_hell[i];
					bullet_hell[i] = nullptr;

				}

				
				for (int j = 0; j <= 54; j++) {

					if (Collision_Projectile_Enemies(i, j) == true) {
						
						graphics::playSound(std::string(ASSET_PATH) + "Alien_Array.mp3", 0.05f, false);
						player_score += points[j];
						delete multiple[j];
						multiple[j] = nullptr;

						delete bullet_hell[i];
						bullet_hell[i] = nullptr;

						player_score += points[j];

					}
				}

			}
			 
		}
}

int Game::remaining_enemies()
{
	int counter = 0;

	for (int r = 0; r <= 54; r++) {

		if (multiple[r] != nullptr) {

			counter += 1;
		}
	}

	return counter;

}

void Game::shoot_bull()
{
	if (enemies_spawned == true) {

		enemy_isFiring = true;
	}

	if (enemy_isFiring == true) {

		bull = new Bullet();
 
		random_number = rand() % 55;

		while(multiple[random_number] == nullptr && remaining_enemies() != 0) {

			random_number = rand() % 55;
		}

		int temp_num = random_number;

		if (multiple[temp_num] != nullptr) {

			bull->set_bullet_X(multiple[temp_num]->getXE());
			
			bull->set_bullet_Y(multiple[temp_num]->getYE());

			enemy_bullet_hell.push_back(bull);

			enemy_isFiring = false;
		}

		for (int i = 0; i < enemy_bullet_hell.size(); i += 53) {

			if (enemy_bullet_hell[i] != nullptr) {

				enemy_bullet_hell[i]->set_Bullet_Speed(b_speed);

				enemy_bullet_hell[i]->update();

				if (enemy_bullet_hell[i]->get_bullet_Y() < 0) {

					delete enemy_bullet_hell[i];

					enemy_bullet_hell[i] = nullptr;

				}
			}

		}



		for (int i = 0; i < enemy_bullet_hell.size(); i += 53) {

			if (enemy_bullet_hell[i] != nullptr) {

				 

			if (Collision_Bullet_Player(i) == true) {
 
						delete enemy_bullet_hell[i];
						enemy_bullet_hell[i] = nullptr;

						graphics::playSound(std::string(ASSET_PATH) + "shooting_sound.wav", 0.5f, false);

						remaining_health = remaining_health - 1;

						player->set_hp(remaining_health);

					}
				}

			}

		for (int i = 0; i < enemy_bullet_hell.size(); i += 53) {

			if (enemy_bullet_hell[i] != nullptr) {



				if (Collision_Bullet_Shield(i,shield1) == true) {

					delete enemy_bullet_hell[i];
					enemy_bullet_hell[i] = nullptr;

					health_1 = health_1 - 1;
					shield1->set_hp(health_1);

					if (health_1 == 0) {

						delete shield1;
						shield1 = nullptr;
						shield1_destroyed == true;
					}

 

				}

				if (Collision_Bullet_Shield(i, shield2) == true) {

					delete enemy_bullet_hell[i];
					enemy_bullet_hell[i] = nullptr;

					health_2 = health_2 - 1;
					shield2->set_hp(health_2);

					if (health_2 == 0) {

						delete shield2;
						shield2 = nullptr;
						shield2_destroyed == true;
					}



				}

				if (Collision_Bullet_Shield(i, shield3) == true) {

					delete enemy_bullet_hell[i];
					enemy_bullet_hell[i] = nullptr;

					health_3 = health_3 - 1;
					shield3->set_hp(health_3);

					if (health_3 == 0) {

						delete shield3;
						shield3 = nullptr;
						shield3_destroyed == true;
					}



				}

				if (Collision_Bullet_Shield(i, shield4) == true) {

					delete enemy_bullet_hell[i];
					enemy_bullet_hell[i] = nullptr;

					health_4 = health_4 - 1;
					shield4->set_hp(health_4);

					if (health_4 == 0) {

						delete shield4;
						shield4 = nullptr;
						shield4_destroyed == true;
					}



				}
			}

		}
		}
		 
	}
	

bool Game::Collision_Projectile_Enemies(int projectile_index, int enemy_index)
{
	if (!bullet_hell[projectile_index] || !multiple[enemy_index]) {

		return false;
	}
	 
	Disk d1 = bullet_hell[projectile_index]->getCollisionHull();
	Disk d2 = multiple[enemy_index]->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;

}

bool Game::Collision_Bullet_Player(int bullet_index)
{
	if (!enemy_bullet_hell[bullet_index] || !player) {

		return false;
	}

	Disk d1 = enemy_bullet_hell[bullet_index]->getCollisionHull();
	Disk d2 = player->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)

		return true;
	else
		return false;

}

bool Game::Collision_Bullet_Shield(int bullet_index, Shield* shield)
{
	if (!enemy_bullet_hell[bullet_index] || !shield) {

		return false;
	}

	Disk d1 = enemy_bullet_hell[bullet_index]->getCollisionHull();
	Disk d2 = shield->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}

bool Game::Collision_Projectile_Shield(int projectile_index, Shield* shield)
{
	if (!bullet_hell[projectile_index] || !shield) {

		return false;
	}

	Disk d1 = bullet_hell[projectile_index]->getCollisionHull();
	Disk d2 = shield->getCollisionHull();

	float dx = d1.cx - d2.cx;
	float dy = d1.cy - d2.cy;

	if (sqrt(dx * dx + dy * dy) < d1.radius + d2.radius)
		return true;
	else
		return false;
}

void Game::init()
{ 
	if (restart == true && status == GAMEPLAY_SCREEN) {

		graphics::setFont(std::string(ASSET_PATH) + "ARCADE.TTF");

	}
	 
	 
}

Game::Game()
{
	init();
}

Game::~Game()
{
	if (player)
	{
		delete player;
	}
 
}

	 
