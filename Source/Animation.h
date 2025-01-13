#pragma once
#include "pch.h"
#include "Textures.h"
#include <vector>

struct Animation {
	std::vector<Texture2D> animationTextures;
	float timer = 0;
	size_t frame = 0;

	explicit Animation(const std::vector<Texture>& textures);
	void Update(float anitmationTimer) noexcept;
	Texture2D getTexture() const;
};