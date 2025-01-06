#pragma once
#include "raylib.h"


struct Window { 

	Window(int screenWidth, int screenHeight) noexcept { //TODO: maybe add "title" to arguments?
		InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
		SetTargetFPS(60);
		//TODO: error handling
	}
	~Window() noexcept {
		CloseWindow();
	}

	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
};