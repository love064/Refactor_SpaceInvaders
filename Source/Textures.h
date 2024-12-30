#pragma once
#include "raylib.h"
#include "vector"
#include <string_view>
#include <stdexcept> //TODO: ERROR HANDLING

struct Textures //TODO: RAII
{
	Texture2D texture;

	explicit Textures(std::string_view fileName) {
		texture = LoadTexture(fileName.data());
		//TODO: ERROR handling
	}

	~Textures() noexcept {
		UnloadTexture(texture);
	}

	auto& get() noexcept{
		return texture;
	}

	Textures(const Textures&) = delete;
	Textures(Textures&&) = delete;
	Textures& operator=(const Textures&) = delete;
	Textures& operator=(Textures&&) = delete;
};