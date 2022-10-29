#include "texture.h"

namespace Stuff
{

Texture::Texture(SDL_Renderer *renderer, const std::string &file)
    : renderer(renderer),
      texture(StuffPrivate::TextureLoader::loadBMP(renderer, file))
{
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}

void Texture::renderTexture(const SDL_Rect &rect)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

} // Stuff
