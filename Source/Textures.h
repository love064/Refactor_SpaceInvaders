#pragma once

#include "pch.h"
#include "vector"
#include <string_view>
#include <stdexcept> //TODO: ERROR HANDLING

struct Textures
{
	Texture2D texture;

	explicit Textures(std::string_view fileName) noexcept{
		texture = LoadTexture(fileName.data());
		//TODO: ERROR handling
	}

	~Textures() noexcept {
		UnloadTexture(texture);
	}

	auto& get() const noexcept{
		return texture;
	}

	Textures(const Textures&) = delete;
	Textures(Textures&&) = delete;
	Textures& operator=(const Textures&) = delete;
	Textures& operator=(Textures&&) = delete;
};