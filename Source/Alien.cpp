#include "Alien.h"
#include "Util.h"

Alien::Alien(Vector2 pos) noexcept {
    rec.x = pos.x;
    rec.y = pos.y;
}

void Alien::Update() noexcept {
	rec.x += (moveRight ? speed : -speed);

	if (rec.x >= GetScreenWidthF() - ALIEN_SIZE || rec.x <= 0) {
		moveRight = !moveRight;  
		rec.y += ALIEN_Y_DROP_AMOUNT;
	}
}

void Alien::Collision() noexcept {
    active = false;
}

void Alien::Render(Texture2D texture) const noexcept{
    DrawTextureV(texture, getPosition(), WHITE);
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
