#pragma once

#include "pch.h"
#include <string_view>
#include <stdexcept>
#include <format>

struct TextureResource
{
	Texture2D texture;

	explicit TextureResource(std::string_view fileName){
		texture = LoadTexture(fileName.data());
		if (texture.id <= 0) {
			throw std::invalid_argument(std::format("ERROR. Failed to load texture: {}", fileName));
		}
	}

	~TextureResource() noexcept {
		UnloadTexture(texture);
	}

	auto& get() const noexcept{
		return texture;
	}

	TextureResource(const TextureResource&) = delete;
	TextureResource(TextureResource&&) = delete;
	TextureResource& operator=(const TextureResource&) = delete;
	TextureResource& operator=(TextureResource&&) = delete;
};
