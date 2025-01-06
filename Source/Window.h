#pragma once
#include "pch.h"
#include <string_view>


struct Window { 

	Window(unsigned screenWidth, unsigned screenHeight, std::string_view title, unsigned fps) noexcept {
		InitWindow(screenWidth, screenHeight, title.data());
		SetTargetFPS(fps);
	}
	~Window() noexcept {
		CloseWindow();
	}
	
	Window(const Window&) = delete;
	Window(Window&&) = delete;
	Window& operator=(const Window&) = delete;
	Window& operator=(Window&&) = delete;
};