#include "game.h"
#include "Util.h"
#include "pch.h"

#define DISABLE_WARNINGS_FROM_RAYLIB \
    __pragma(warning(push)) \
    /* C26812: The enum type '...' is unscoped. Prefer 'enum class' over 'enum' (Enum.3) */ \
    __pragma(warning(disable : 26812)) \
    /* C26446: Prefer to use gsl::at() instead of unchecked subscript operator (bounds.4). */ \
    __pragma(warning(disable : 26446)) \
    /* C26455: Default constructor is not declared as noexcept */ \
    __pragma(warning(disable : 26455)) \
    /* C26426: Global initializer calls a non-constexpr function */ \
    __pragma(warning(disable : 26426)) \
    /* C26409: Avoid calling new and delete explicitly, use smart pointers */ \
    __pragma(warning(disable : 26409)) \
    /* C26477: Use 'override' instead of base class member name */ \
    __pragma(warning(disable : 26477)) \
    /* C26433: Function can be marked as noexcept */ \
    __pragma(warning(disable : 26433)) \
    /* C26818: Prefer std::vector over C array */ \
    __pragma(warning(disable : 26818)) \
    /* C26440: Function can be declared 'const' */ \
    __pragma(warning(disable : 26440))

Game::Game() noexcept(false) {
	reset();
}

void Game::End() noexcept{
	Projectiles.clear();
	Walls.clear();
	Aliens.clear();
}

void Game::reset(){
	const auto wall_distance = GetScreenWidthF() / (WALL_COUNT + 1);
	for (int i = 0; i < WALL_COUNT; i++) {
		const Vector2 spawnPoint = { wall_distance * (i + WALL_MARGIN_X), GetScreenHeightF() - WALL_Y_OFFSET };
		Walls.emplace_back(spawnPoint);
	}	
	player = {};	
	SpawnAliens();		
	background = Background(STAR_COUNT);
	score = 0;
}


GameState Game::Update(){
	if (IsKeyReleased(KEY_Q)) {
		End();
		return GameState::ENDSCREEN;
	}
	
	player.Update();
	playerAnimation.Update(PLAYER_ANIMATION_TIMER);
	if (player.lives < 1){
		End();
		return GameState::ENDSCREEN;
	}
	
	for (auto& alien : Aliens) {
		alien.Update();
		if (alien.getPositionY() > PLAYER_POSITION_Y) {
			End();
			return GameState::ENDSCREEN;
		}
	}
	if (Aliens.empty()){
		SpawnAliens();
	}

	for (auto& projectile : Projectiles) {
		projectile.Update();
	}
	for (auto& wall : Walls) {
		wall.Update();
	}

	const float offset = ((GetScreenWidthF() / 2.f) - player.getPositionX()) / PLAYER_TO_STAR_OFFSET_DIVIDER;
	background.Update(offset);

	PlayerShooting();
	AlienShooting();
	Collisions();

	std::erase_if(Aliens, [](const Alien& a) { return !a.active; });
	std::erase_if(Walls, [](const Wall& w) { return !w.active; });
	std::erase_if(Projectiles, [](const Projectile& p) { return !p.active; });
	
	return GameState::GAMEPLAY;
}

void Game::PlayerShooting(){
	if (IsKeyPressed(KEY_SPACE)) {
		Vector2 spawnPoint = { player.getPositionX() + (PLAYER_SIZE / 2), PLAYER_POSITION_Y};
		Projectiles.emplace_back(EntityType::PLAYER_PROJECTILE, spawnPoint);
	}
}

void Game::AlienShooting() {
	shootTimer += 1;
	if (shootTimer >= 60){
		if (Aliens.empty()) {
			return;
		}
		const int randomNumber = GetRandomValue(0, static_cast<int>(Aliens.size()) - 1); //TODO: gsl::narrow_cast

		Projectiles.emplace_back(EntityType::ENEMY_PROJECTILE, Aliens[randomNumber].getPosition()); //TODO: at()
		shootTimer = 0;
	}
}

void Game::Collisions() noexcept {
	for (auto& projectile : Projectiles) {
		for (auto& wall : Walls) {
			if (CheckCollisionRecs(projectile.rec, wall.rec)) {
				projectile.Collision();
				wall.Collision();
			}
		}

		if (projectile.type == EntityType::ENEMY_PROJECTILE && CheckCollisionRecs(projectile.rec, player.rec)) {
			projectile.Collision();
			player.Collision();
		}

		for (auto& alien : Aliens) {
			if (projectile.type == EntityType::PLAYER_PROJECTILE && CheckCollisionRecs(projectile.rec, alien.rec)) {
				projectile.Collision();
				alien.Collision();
				score += 100;
			}
		}
	}
}

void Game::Render() const noexcept {
	background.Render();

	ui.Render(score, player.lives);

	player.Render(playerAnimation.getTexture());

	for (const auto& p : Projectiles) {
		p.Render(laserTexture.get());
	}
	for (const auto& w : Walls) {
		w.Render(barrierTexture.get());
	}
	for (const auto& a : Aliens) {
		a.Render(alienTexture.get());
	}
}

void Game::SpawnAliens(){
	for (int row = 0; row < FORMATION_COLLUM; row++) {
		for (int col = 0; col < FORMATION_ROW; col++) {
			Vector2 spawnPoint = { FORMATION_X + (col * ALIEN_SPACING), FORMATION_Y + (row * ALIEN_SPACING) };
			Aliens.emplace_back(spawnPoint);
		}
	}
}

#define RESTORE_WARNINGS __pragma(warning(pop))