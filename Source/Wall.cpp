#include "Wall.h"

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

Wall::Wall(Vector2 pos) noexcept {
	rec.x = pos.x;
	rec.y = pos.y;
}

void Wall::Update() noexcept {
	if (health <= 0){
		active = false;
	}
}

void Wall::Collision() noexcept {
    health -= 1;
}

void Wall::Render(Texture2D texture) const noexcept {
	DrawTexturePro(texture,
		{ 0, 0, WALL_SPRITE_SIZE, WALL_SPRITE_SIZE },
		{ rec.x, rec.y, WALL_SIZE, WALL_SIZE },
		{ WALL_SPRITE_ORIGN, WALL_SPRITE_ORIGN },
		0, WHITE);

	DrawText(TextFormat("%i", health), getPosXI() - WALL_TEXT_OFFSET_X, getPosYI() + WALL_TEXT_OFFSET_Y, WALL_TEXT_SIZE, RED);
}

int Wall::getPosXI() const noexcept{
	return static_cast<int>(rec.x);
}
int Wall::getPosYI() const noexcept {
	return static_cast<int>(rec.y);
}

#define RESTORE_WARNINGS __pragma(warning(pop))