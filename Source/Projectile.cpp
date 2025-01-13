#include "Projectile.h"
#include "Util.h"

Projectile::Projectile(EntityType entityType, Vector2 pos) noexcept {
	type = entityType;
    rec.x = pos.x;
    rec.y = pos.y;
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
    DrawTextureV(texture, { rec.x, rec.y }, WHITE);
}
