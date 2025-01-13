#include "Util.h"
#include "pch.h"

float GetScreenWidthF() noexcept {
	return static_cast<float>(GetScreenWidth());
}

float GetScreenHeightF() noexcept {
	return static_cast<float>(GetScreenHeight());
}
