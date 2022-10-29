#include "texture.h"

namespace Stuff
{

Texture::Texture(SDL_Renderer *renderer,
                 const std::string &file,
                 SDL_BlendMode blendMode)
    : renderer(renderer),
      texture(StuffPrivate::TextureLoader::loadBMP(renderer, file))
{
    if(texture == nullptr)
    {
        SDL_Log("Unable to create texture %s", file.c_str());
        return;
    }

    SDL_SetTextureBlendMode(texture, blendMode);
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}

void Texture::renderTexture(const SDL_Rect &rect)
{
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void Texture::updateTransparency(Uint8 a)
{
    SDL_SetTextureAlphaMod(texture, a);
}

} // Stuff
