#include "Animation.h"
#include <stdexcept>

Animation::Animation(const std::vector<Texture>& textures) {
    animationTextures = textures;
}

void Animation::Update(float anitmationTimer) noexcept {
    timer += GetFrameTime();

    if (!animationTextures.empty() && timer > anitmationTimer) {
        frame = (frame + 1) % animationTextures.size(); 
        timer = 0;
    }
}

Texture2D Animation::getTexture() const {
    if (frame > animationTextures.size()) {
        throw std::out_of_range("Animation frame was out of range");
    }
#pragma warning(push)
#pragma warning(disable: 26446)
    return animationTextures[frame];
#pragma warning(pop)
}
