#include "Animation.h"


Animation::Animation(const std::vector<Texture>& textures) {
    animationTextures = textures;
}

void Animation::addFrame(Texture2D texture) {
    animationTextures.push_back(texture);
}

void Animation::Update(float anitmationTimer) noexcept {
    timer += GetFrameTime();

    if (!animationTextures.empty() && timer > anitmationTimer) {
        frame = (frame + 1) % static_cast<int>(animationTextures.size()); //TODO: gsl::narrow_cast<int>()
        timer = 0;
    }
}

Texture2D Animation::getTexture() const noexcept {
    //TODO: supress and make sure it cant go out of bounds (test/excepts)
    return animationTextures[frame]; //TODO: at()?
}
