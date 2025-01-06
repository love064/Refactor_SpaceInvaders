#pragma once
#include "GameStates.h"

struct StartScreen {
	GameState update() const noexcept;
	void render() const noexcept;
};