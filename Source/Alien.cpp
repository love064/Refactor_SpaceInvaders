#include "Alien.h"
#include "Util.h"

Alien::Alien(Vector2 position) noexcept {
	pos = position;
}

void Alien::Update() noexcept {
	pos.x += ALIEN_SPEED * vel;

	if (pos.x >= GetScreenWidthF() - ALIEN_SIZE || pos.x <= 0) {
		vel = -vel;
		pos.y += ALIEN_Y_DROP_AMOUNT;
	}
}

void Alien::Collision() noexcept {
    active = false;
}

void Alien::Render(Texture2D texture) const noexcept{
	DrawTextureV(texture, pos, WHITE);
}

float Alien::getPositionY() const noexcept {
	return pos.y;
}
Rectangle Alien::getRec() const noexcept {
	return { pos.x, pos.y, ALIEN_SIZE, ALIEN_SIZE };
}
