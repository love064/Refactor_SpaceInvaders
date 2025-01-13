#include "Wall.h"
#include "Util.h"

Wall::Wall(Vector2 position) noexcept {
	pos.x = position.x;
	pos.y = position.y;
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
    DrawTextureV(texture, pos, WHITE);
	DrawTextF(TextFormat("%i", health), pos.x + WALL_TEXT_OFFSET_X, pos.y + WALL_TEXT_OFFSET_Y, WALL_TEXT_SIZE, RED);
}

Rectangle Wall::getRec() const noexcept {
	return { pos.x, pos.y, WALL_SIZE_X , WALL_SIZE_Y };
}

