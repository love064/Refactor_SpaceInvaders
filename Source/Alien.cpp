#include "Alien.h"
#include "Util.h"

Alien::Alien(Vector2 pos) noexcept {
	position = pos;
}

void Alien::Update() noexcept {
	position.x += (moveRight ? speed : -speed);

	if (position.x >= GetScreenWidthF() || position.x <= 0) {
		moveRight = !moveRight;  
		position.y += ALIEN_Y_DROP_AMOUNT;
	}
}

void Alien::Render(Texture2D texture) const noexcept{
	DrawTexturePro(texture,
		{ 0, 0, ALIEN_SPRITE_SIZE, ALIEN_SPRITE_SIZE},
		{ position.x, position.y, ALIEN_SIZE, ALIEN_SIZE}, 
		{ ALIEN_SPRITE_ORIGN, ALIEN_SPRITE_ORIGN },
		0,WHITE);
}