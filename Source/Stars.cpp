#include "Stars.h"

//TODO: REMOVE: ENUMS, WARING SUPRESSION. ADD: FUNCTION OVERLOADS (REMOVE STATIC_CAST). SIMPLIFY: LEADERBAORD IF TIME. GUT PROJECTILE, CHANGE INTO TWO VECTORS

Background::Background(int starAmount){
	for (int i = 0; i < starAmount; i++) {
		Stars.emplace_back();
	}
}

void Background::Update(float offset) noexcept {
	for (auto& star : Stars) {
		star.Update(offset);
	}
}

void Background::Render() const noexcept{
	for (const auto& star : Stars) {
		star.Render();
	}
}

//float GetRandomValueF() {} //TODO

Star::Star() noexcept {
	size = static_cast<float>(GetRandomValue(1, 4)) / 2.f;
	initX = static_cast<float>(GetRandomValue(-150, GetScreenWidth() + 150));
	position.x = initX;
	position.y = static_cast<float>(GetRandomValue(0, GetScreenHeight()));
}

void Star::Update(float starOffset) noexcept {
	position.x = initX + starOffset;
}

//void DrawCircle(Vector2 pos) {}; //TODO. (use overloads)

void Star::Render() const noexcept {
	DrawCircle(getPositionX(), getPositionY(), size, SKYBLUE);
}

int Star::getPositionX() const noexcept {
	return static_cast<int>(position.x);
}
int Star::getPositionY() const noexcept {
	return static_cast<int>(position.y);
}