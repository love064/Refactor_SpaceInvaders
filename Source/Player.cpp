#include "Player.h"
#include "Util.h"

Player::Player() noexcept {
	pos.x = GetScreenWidthF() / 2.f;
}

void Player::Update() noexcept{
	vel = 0;
	if (IsKeyDown(KEY_LEFT)) {
		vel = -1;
	}
	if (IsKeyDown(KEY_RIGHT)) {
		vel = 1;
	}

	pos.x += PLAYER_SPEED * vel;

	if (pos.x < 0 + PLAYER_RADIUS)
	{
		pos.x = 0 + PLAYER_RADIUS;
	}
	else if (pos.x > GetScreenWidthF() - PLAYER_RADIUS)
	{
		pos.x = GetScreenWidthF() - PLAYER_RADIUS;
	}
}

void Player::Collision() noexcept {
	lives -= 1;
}

void Player::Render(Texture2D texture) const noexcept{ 
	DrawTextureV(texture, pos, WHITE);
}

Rectangle Player::getRec() const noexcept{
	return { pos.x, pos.y,  PLAYER_SIZE, PLAYER_SIZE};
}
float Player::getPositionX() const noexcept {
	return pos.x;
}
