#pragma once
#include "GameStates.h"

struct StartScreen {

	GameState update() noexcept;
	void render() const noexcept;
};