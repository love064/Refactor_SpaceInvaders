#pragma once
#include "raylib.h"


struct Window { //REAL ONE
	
	Window(int screenWidth, int screenHeight) { //TODO: noexcept?
		InitWindow(screenWidth, screenHeight, "SPACE INVADERS");
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