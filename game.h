#pragma once
#include "player.h"
#include "enemy.h"
#include "shield.h"
#include "projectile.h"
#include "bullet.h"
#include <vector>
#include <random>
#include <ctime>
 
 
 

class Game
{
	typedef enum {MENU_SCREEN, GAMEPLAY_SCREEN, GAME_OVER_SCREEN} status_t;

	status_t status;

	int waves = 1;

	void updateMenuScreen();

	void updateGameplayScreen();

	void updateGameOverScreen();

	void drawMenuScreen();

	void drawGameplayScreen();

	void drawGameOverScreen();

	bool restart = true;

	int player_score = 0;
	
	int random_number;

	Player * player = nullptr;

	bool player_created = false;

	float remaining_health = 6;

	Enemy* enemy_ship = nullptr;

	void spawn_enemy_ship();

	bool enemies_spawned = false;

	Enemy** multiple = new Enemy * [55];
 
	int* points = new int[55];

	float speed = 2.0f;
	 
	Shield * shield1 = nullptr;
	
	Shield * shield2 = nullptr;
	
	Shield * shield3 = nullptr;
	
	Shield * shield4 = nullptr;

	int health_1 = 30;

	int health_2 = 30;

	int health_3 = 30;

	int health_4 = 30;

	bool shield1_destroyed = false;

	bool shield2_destroyed = false;

	bool shield3_destroyed = false;

	bool shield4_destroyed = false;

	bool shields_created_once = false;

	void spawn_shields();

	Projectile* pr = nullptr;

	bool isFiring = false;

	std::vector<Projectile*> bullet_hell;

	void shoot_pr();

	Bullet* bull = nullptr;

	bool enemy_isFiring = false;

	std::vector<Bullet*> enemy_bullet_hell;

	float b_speed = 2.0f;

	int remaining_enemies();

	void shoot_bull();

	bool Collision_Projectile_Enemies(int projectile_index, int enemy_index);

	bool Collision_Bullet_Player(int bullet_index);

	bool Collision_Bullet_Shield(int bullet_index, Shield* shield);

	bool Collision_Projectile_Shield(int projectile_index, Shield* shield);
  

public:
	void update();

	void draw();

	void init();

	Game();

	~Game();
};
