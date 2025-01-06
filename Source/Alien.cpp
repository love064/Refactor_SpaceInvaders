#include "Alien.h"
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

Alien::Alien(Vector2 pos) noexcept {
    rec.x = pos.x;
    rec.y = pos.y;
}

void Alien::Update() noexcept {
	rec.x += (moveRight ? speed : -speed);

	if (rec.x >= GetScreenWidthF() || rec.x <= 0) {
		moveRight = !moveRight;  
		rec.y += ALIEN_Y_DROP_AMOUNT;
	}
}

//TODO: replace drawtexturepro with the simpler drawtexture
void Alien::Render(Texture2D texture) const noexcept{
	DrawTexturePro(texture,
		{ 0, 0, ALIEN_SPRITE_SIZE, ALIEN_SPRITE_SIZE},
		{ rec.x, rec.y, ALIEN_SIZE, ALIEN_SIZE}, 
		{ ALIEN_SPRITE_ORIGN, ALIEN_SPRITE_ORIGN },
		0,WHITE);
}

void Alien::Collision() noexcept {
    active = false;
}

Vector2 Alien::getPosition() const noexcept {
    return { rec.x, rec.y };
}

float Alien::getPositionX() const noexcept {
	return rec.x;
}
float Alien::getPositionY() const noexcept {
	return rec.y;
}

#define RESTORE_WARNINGS __pragma(warning(pop))