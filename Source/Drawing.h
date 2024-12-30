#pragma once
#include "raylib.h"

struct Drawing {
	
	Drawing() noexcept{
		BeginDrawing();
		//TODO: ERROR HANDLING?
		ClearBackground(BLACK);
	}

	~Drawing() noexcept {
		EndDrawing();
	}

	Drawing(const Drawing&) = delete;
	Drawing(Drawing&&) = delete;
	Drawing& operator=(const Drawing&) = delete;
	Drawing& operator=(Drawing&&) = delete;
};