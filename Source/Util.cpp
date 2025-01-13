#include "Util.h"

float GetScreenWidthF() noexcept {
	return static_cast<float>(GetScreenWidth());
}

float GetScreenHeightF() noexcept {
	return static_cast<float>(GetScreenHeight());
}

float GetRandomValueF(int min, int max) noexcept {
	return static_cast<float>(GetRandomValue(min, max));
}

size_t GetRandomValueST(size_t min, size_t max) noexcept {
	return static_cast<size_t>(GetRandomValue(static_cast<int>(min), static_cast<int>(max)));
}
