#include "Stars.h"
#include "Util.h"

Background::Background(unsigned starAmount){
	stars = std::vector<Star>(starAmount);
}

void Background::Update(float playerPositionX) noexcept {
	const float offset = ((GetScreenWidthF() / 2.f) - playerPositionX) / PLAYER_TO_STAR_OFFSET_DIVIDER;
	for (auto& star : stars) {
		star.Update(offset);
	}
}

void Background::Render() const noexcept{
	for (const auto& star : stars) {
		star.Render();
	}
}

Star::Star() noexcept {
	size = GetRandomValueF(STAR_MIN_SIZE, STAR_MAX_SIZE) / 2.f;
	initX = GetRandomValueF(-STAR_X_OFFSET, GetScreenWidth() + STAR_X_OFFSET);
	position.x = initX;
	position.y = GetRandomValueF(0, GetScreenHeight());
}

void Star::Update(float starOffset) noexcept {
	position.x = initX + starOffset;
}

void Star::Render() const noexcept {
	DrawCircleV(position, size, SKYBLUE);
}