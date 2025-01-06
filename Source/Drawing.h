#pragma once
#include "pch.h"

struct Drawing {
	
	explicit Drawing(Color Background) noexcept{
		BeginDrawing();
		ClearBackground(Background);
	}

	~Drawing() noexcept {
		EndDrawing();
	}

	Drawing(const Drawing&) = delete;
	Drawing(Drawing&&) = delete;
	Drawing& operator=(const Drawing&) = delete;
	Drawing& operator=(Drawing&&) = delete;
};