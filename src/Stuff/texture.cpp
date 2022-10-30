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

Texture::Texture(SDL_Renderer *renderer,
                 const std::string &text,
                 TTF_Font *font,
                 SDL_Color color)
    : renderer(renderer),
      texture(StuffPrivate::TextureLoader::loadTextTexture(renderer, text, font, color))
{
    if(texture == nullptr)
    {
        SDL_Log("Unable to create texture with text %s", text.c_str());
        return;
    }
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

Texture::~Texture()
{
    SDL_DestroyTexture(texture);
}

std::unique_ptr<Texture> Texture::loadTexture(SDL_Renderer *renderer,
                                                     const std::string &file,
                                                     SDL_BlendMode blendMode)
{
    // Чтобы не делать конструктор открытым
    struct MakeUniqueEnable : public Texture
    {
        MakeUniqueEnable(SDL_Renderer *renderer,
                         const std::string &file,
                         SDL_BlendMode blendMode)
            : Texture(renderer, file, blendMode) {}
    };

    return std::make_unique<MakeUniqueEnable>(renderer, file, blendMode);
}

std::unique_ptr<Texture> Texture::loadTextTexture(
        SDL_Renderer *renderer,
        const std::string &text,
        TTF_Font *font,
        SDL_Color color)
{
    struct MakeUniqueEnable : public Texture
    {
        MakeUniqueEnable(SDL_Renderer *renderer,
                         const std::string &text,
                         TTF_Font *font,
                         SDL_Color color)
            : Texture(renderer, text, font, color) {}
    };

    return std::make_unique<MakeUniqueEnable>(renderer, text, font, color);
}

void Texture::renderTexture(const SDL_Rect &dst)
{
    SDL_RenderCopy(renderer, texture, nullptr, &dst);
}

void Texture::renderTexture(const SDL_Rect &src, const SDL_Rect &dst)
{
    SDL_RenderCopy(renderer, texture, &src, &dst);
}

void Texture::updateTransparency(Uint8 a)
{
    SDL_SetTextureAlphaMod(texture, a);
}

} // Stuff
