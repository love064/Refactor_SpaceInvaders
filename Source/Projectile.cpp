#include "Projectile.h"
#include "Util.h"

Projectile::Projectile(Vector2 position, float velocity) noexcept {
	pos = position;
	vel = velocity;
}

void Projectile::Update() noexcept {
	pos.y -= PROJECTILE_SPEED * vel;

	if (pos.y < 0 || pos.y > GetScreenHeightF()){
		active = false;
	}
}

void Projectile::Collision() noexcept {
    active = false;
}

void Projectile::Render(Texture2D texture) const noexcept{
    DrawTextureV(texture, pos, WHITE);
}

Rectangle Projectile::getRec() const noexcept {
	return { pos.x, pos.y, PROJECTILE_SIZE_X, PROJECTILE_SIZE_Y };
}