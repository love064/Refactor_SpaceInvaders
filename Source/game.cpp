#include "game.h"
#include "Util.h"
#include "pch.h"
#include <algorithm>

Game::Game() noexcept(false) {
	reset();
}

void Game::End() noexcept{
	enemyProjectiles.clear();
	playerProjectiles.clear();
	walls.clear();
	aliens.clear();
}

void Game::reset(){
	const auto wall_distance = GetScreenWidthF() / (WALL_COUNT + 1);
	for (int i = 0; i < WALL_COUNT; i++) {
		const Vector2 spawnPoint = { wall_distance * (i + WALL_MARGIN_X), GetScreenHeightF() - WALL_Y_OFFSET };
		walls.emplace_back(spawnPoint);
	}	
	player = {};	
	SpawnAliens();		
	background = Background(STAR_COUNT);
	score = 0;
}


GameState Game::Update(){ //TODO: simplify/shorten
	if (IsKeyReleased(KEY_Q) || player.lives < 1) {
		return GameState::ENDSCREEN;
	}
	
	player.Update();
	playerAnimation.Update(PLAYER_ANIMATION_TIMER);
	
	for (auto& alien : aliens) {
		alien.Update();
		if (alien.getPositionY() > PLAYER_POSITION_Y) {
			return GameState::ENDSCREEN;
		}
	}
	if (aliens.empty()){
		SpawnAliens();
	}
	for (auto& projectile : enemyProjectiles) {
		projectile.Update();
	}
	for (auto& projectile : playerProjectiles) {
		projectile.Update();
	}
	for (auto& wall : walls) {
		wall.Update();
	}
	background.Update(player.getPositionX());

	PlayerShooting();
	AlienShooting();
	Collisions();

	std::erase_if(aliens, [](const Alien& a) { return !a.active; });
	std::erase_if(walls, [](const Wall& w) { return !w.active; });
	std::erase_if(enemyProjectiles, [](const Projectile& p) { return !p.active; });
	std::erase_if(playerProjectiles, [](const Projectile& p) { return !p.active; });
	
	return GameState::GAMEPLAY;
}

void Game::PlayerShooting(){
	if (IsKeyPressed(KEY_SPACE)) {
		Vector2 spawnPoint = { player.getPositionX() + (PLAYER_SIZE / 2), PLAYER_POSITION_Y};
		playerProjectiles.emplace_back(spawnPoint, 1.f);
	}
}

void Game::AlienShooting() {
	if (aliens.empty()) {
		return;
	}
	shootTimer += 1;
	if (shootTimer < 60) {
		return;	
	}		
	const size_t randomNumber = GetRandomValueST(0, aliens.size() - 1);
	enemyProjectiles.emplace_back(aliens[randomNumber].pos, -1.f); //TODO: at(), THERE ARE OTHER WAYS OF DOING THIS ???
	shootTimer = 0;	
}

void Game::checkCollisions(auto& projectile, auto& entities) const noexcept {
	std::ranges::for_each(entities, [&projectile](auto& entity) noexcept {
		if (CheckCollisionRecs(projectile.getRec(), entity.getRec())) {
			projectile.Collision();
			entity.Collision();
		}
	});
};

void Game::Collisions() noexcept {
	std::ranges::for_each(enemyProjectiles, [this](auto& projectile) noexcept {
		checkCollisions(projectile, walls);
		if (CheckCollisionRecs(projectile.getRec(), player.getRec())) {
			projectile.Collision();
			player.Collision();
		}
	});

	std::ranges::for_each(playerProjectiles, [this](auto& projectile) noexcept {
		checkCollisions(projectile, walls);
		std::ranges::for_each(aliens, [&projectile, this](auto& alien) noexcept {
			if (CheckCollisionRecs(projectile.getRec(), alien.getRec())) {
				projectile.Collision();
				alien.Collision();
				score += 100;
			}
		});
	});
}

void Game::Render() const {
	background.Render();

	ui.Render(score, player.lives);

	player.Render(playerAnimation.getTexture());

	for (const auto& p : enemyProjectiles) {
		p.Render(laserTexture.get());
	}
	for (const auto& p : playerProjectiles) {
		p.Render(laserTexture.get());
	}
	for (const auto& w : walls) {
		w.Render(barrierTexture.get());
	}
	for (const auto& a : aliens) {
		a.Render(alienTexture.get());
	}
}

void Game::SpawnAliens(){
	for (int row = 0; row < FORMATION_COLLUM; row++) {
		for (int col = 0; col < FORMATION_ROW; col++) {
			const Vector2 spawnPoint = { FORMATION_X + (col * ALIEN_SPACING), FORMATION_Y + (row * ALIEN_SPACING) };
			aliens.emplace_back(spawnPoint);
		}
	}
}
