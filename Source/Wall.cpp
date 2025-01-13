#include "Wall.h"

Wall::Wall(Vector2 pos) noexcept {
	rec.x = pos.x;
	rec.y = pos.y;
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
    DrawTextureV(texture, { rec.x, rec.y }, WHITE);
	DrawText(TextFormat("%i", health), getPosXI() + WALL_TEXT_OFFSET_X, getPosYI() + WALL_TEXT_OFFSET_Y, WALL_TEXT_SIZE, RED);
}

int Wall::getPosXI() const noexcept{
	return static_cast<int>(rec.x);
}
int Wall::getPosYI() const noexcept {
	return static_cast<int>(rec.y);
}
