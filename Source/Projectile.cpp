#include "Projectile.h"
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

Projectile::Projectile(EntityType entityType, Vector2 pos) noexcept {
	type = entityType;
    rec.x = pos.x;
    rec.y = pos.y;
	//position = pos;
	if (entityType == EntityType::ENEMY_PROJECTILE) {
		direction = Direction::DOWN;
	}
}

void Projectile::Update() noexcept {
	rec.y -= PROJECTILE_SPEED * static_cast<float>(direction);

	if (rec.y < 0 || rec.y > GetScreenHeightF()){
		active = false;
	}
}

void Projectile::Collision() noexcept {
    active = false;
}

void Projectile::Render(Texture2D texture) const noexcept{
	DrawTexturePro(texture,
		{ 0, 0, PROJECTILE_SPRITE_SIZE, PROJECTILE_SPRITE_SIZE},
		{ rec.x, rec.y, PROJECTILE_SIZE, PROJECTILE_SIZE}, 
		{ 25 , 25 },
		0, WHITE);
}

//Vector2 Projectile::getLineStart() const noexcept {
//	return { position.x, position.y - PROJECTILE_HITBOX_OFFSET };
//}
//Vector2 Projectile::getLineEnd() const noexcept {
//	return { position.x, position.y + PROJECTILE_HITBOX_OFFSET };
//}

#define RESTORE_WARNINGS __pragma(warning(pop))