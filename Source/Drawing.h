#pragma once
#include "raylib.h"

struct Drawing {
	
	Drawing() {
		BeginDrawing();
		ClearBackground(BLACK);
	}

	~Drawing() {
		EndDrawing();
	}

	Drawing(const Drawing&) = delete;
	Drawing(Drawing&&) = delete;
	Drawing& operator=(const Drawing&) = delete;
	Drawing& operator=(Drawing&&) = delete;
};