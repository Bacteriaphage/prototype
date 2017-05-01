#include "ResourceManager.h"

TextureCache ResourceManager::_textureCache;

GLTexture ResourceManager::get_Texture(std::string texturePath) {
    return _textureCache.getTexture(texturePath);
}