#include "Player.h"
#include "Util.h"

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

void Player::Collision() noexcept {
	lives -= 1;
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
		{x_pos, PLAYER_POSITION_Y, PLAYER_RADIUS * 2, PLAYER_RADIUS * 2,},
		{ 50, 50 },
		0, WHITE);
}

#define RESTORE_WARNINGS __pragma(warning(pop))