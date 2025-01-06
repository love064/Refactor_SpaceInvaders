#pragma once

#include "pch.h"
#include <string_view>
#include <stdexcept>
#include <format>

struct Textures
{
	Texture2D texture;

	explicit Textures(std::string_view fileName){
		texture = LoadTexture(fileName.data());
		if (texture.id <= 0) {
			throw std::runtime_error(std::format("ERROR. Failed to load texture: {}", fileName));
		}
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