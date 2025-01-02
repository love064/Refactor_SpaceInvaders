#include "Wall.h"

Wall::Wall(Vector2 pos) noexcept {
	position = pos;
}

void Wall::Update() noexcept {
	if (health <= 0){
		active = false;
	}
}

void Wall::Render(Texture2D texture) const noexcept {
	DrawTexturePro(texture,
		{ 0, 0, WALL_SPRITE_SIZE, WALL_SPRITE_SIZE },
		{ position.x, position.y, WALL_SIZE, WALL_SIZE },
		{ 100, 100 },
		0, WHITE);

	DrawText(TextFormat("%i", health), getPosXI() - WALL_TEXT_OFFSET_X, getPosYI() + WALL_TEXT_OFFSET_Y, WALL_TEXT_SIZE, RED);
}

int Wall::getPosXI() const noexcept{
	return static_cast<int>(position.x);
}
int Wall::getPosYI() const noexcept {
	return static_cast<int>(position.y);
}
