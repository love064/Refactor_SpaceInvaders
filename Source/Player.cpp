#include "Player.h"
#include "Util.h"

Player::Player() noexcept {
	x_pos = GetScreenWidthF() / 2.f;
}

void Player::Update() noexcept{
	Movement();
	Animation();
}

void Player::Movement() noexcept {
	direction = Direction::STATIC;
	if (IsKeyDown(KEY_LEFT)){
		direction = Direction::LEFT;
	}
	if (IsKeyDown(KEY_RIGHT)){
		direction = Direction::RIGHT;
	}

	x_pos += PLAYER_SPEED * static_cast<float>(direction);

	if (x_pos < 0 + PLAYER_RADIUS)
	{
		x_pos = 0 + PLAYER_RADIUS;
	}
	else if (x_pos > GetScreenWidthF() - PLAYER_RADIUS)
	{
		x_pos = GetScreenWidthF() - PLAYER_RADIUS;
	}
}

void Player::Animation() noexcept {
	textureTimer += GetFrameTime();

	if (textureTimer > PLAYER_ANIMATION_TIMER && activeTexture == 2)
	{
		activeTexture = 0;
		textureTimer = 0;
	}
	else if (textureTimer > PLAYER_ANIMATION_TIMER)
	{
		activeTexture++;
		textureTimer = 0;
	}
}

void Player::reset() noexcept { //TODO: if we make a new one we dont need this
	x_pos = GetScreenWidthF() / 2.f;
	lives = PLAYER_MAX_HEALTH;
	textureTimer = 0;
	direction = Direction::STATIC;
	activeTexture = 0;
}

void Player::Render(Texture2D texture) const noexcept{ //TODO: maybe make const Texture2D& texture
	DrawTexturePro(texture,
		{0,0, PLAYER_SPRITE_SIZE, PLAYER_SPRITE_SIZE,},
		{x_pos, GetScreenHeightF() - PLAYER_POSITION_Y, PLAYER_RADIUS * 2, PLAYER_RADIUS * 2,},
		{ 50, 50 },
		0, WHITE);
}