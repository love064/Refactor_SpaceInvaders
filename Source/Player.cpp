#include "Player.h"
#include "Util.h"

Player::Player() noexcept {
	rec.x = GetScreenWidthF() / 2.f;
}

void Player::Update() noexcept{
	Movement();
}

void Player::Movement() noexcept {
	direction = Direction::STATIC;
	if (IsKeyDown(KEY_LEFT)){
		direction = Direction::LEFT;
	}
	if (IsKeyDown(KEY_RIGHT)){
		direction = Direction::RIGHT;
	}

	rec.x += PLAYER_SPEED * static_cast<float>(direction);

	if (rec.x < 0 + PLAYER_RADIUS)
	{
		rec.x = 0 + PLAYER_RADIUS;
	}
	else if (rec.x > GetScreenWidthF() - PLAYER_RADIUS)
	{
		rec.x = GetScreenWidthF() - PLAYER_RADIUS;
	}
}

void Player::Collision() noexcept {
	lives -= 1;
}

void Player::Render(Texture2D texture) const noexcept{ 
	DrawTextureV(texture, getPosition(), WHITE);
}

Vector2 Player::getPosition() const noexcept{
	return { rec.x, rec.y };
}
float Player::getPositionX() const noexcept {
	return rec.x;
}
