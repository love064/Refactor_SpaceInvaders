#pragma once
#include "raylib.h"
#include "vector"
#include <string_view>
#include <stdexcept>
//#include <memory>

struct Resources //TODO: RAII
{
	Texture2D texture;

	explicit Resources(std::string_view fileName) {
		texture = LoadTexture(fileName.data());
		//TODO: ERROR handling
	}

	~Resources() noexcept {
		UnloadTexture(texture);
	}

	auto& get() noexcept{
		return texture;
	}

	Resources(const Resources&) = delete;
	Resources(Resources&&) = delete;
	Resources& operator=(const Resources&) = delete;
	Resources& operator=(Resources&&) = delete;
};