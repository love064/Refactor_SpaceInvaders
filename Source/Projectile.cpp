#include "Projectile.h"
#include "Util.h"

Projectile::Projectile(EntityType entityType, Vector2 pos) noexcept {
	type = entityType;
	position = pos;
	if (entityType == EntityType::ENEMY_PROJECTILE) {
		direction = Direction::DOWN;
	}
}

void Projectile::Update() noexcept {
	position.y -= PROJECTILE_SPEED * static_cast<float>(direction);

	if (position.y < 0 || position.y > GetScreenHeightF()){
		active = false;
	}
}

void Projectile::Render(Texture2D texture) const noexcept{
	DrawTexturePro(texture,
		{ 0, 0, PROJECTILE_SPRITE_SIZE, PROJECTILE_SPRITE_SIZE},
		{ position.x, position.y, PROJECTILE_SIZE, PROJECTILE_SIZE}, 
		{ 25 , 25 },
		0, WHITE);
}

Vector2 Projectile::getLineStart() const noexcept {
	return { position.x, position.y - PROJECTILE_HITBOX_OFFSET };
}
Vector2 Projectile::getLineEnd() const noexcept {
	return { position.x, position.y + PROJECTILE_HITBOX_OFFSET };
}