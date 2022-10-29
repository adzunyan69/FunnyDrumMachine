#ifndef TEXTURE_H
#define TEXTURE_H

#include "textureloader.h"
namespace Stuff
{
class Texture
{
public:
    Texture(SDL_Renderer *renderer,
            const std::string &file,
            SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);
    Texture(const Texture&) = delete;
    virtual ~Texture();

    void renderTexture(const SDL_Rect &rect);
    void updateTransparency(Uint8 a);

private:
    SDL_Renderer *renderer{ nullptr };
    SDL_Texture *texture{ nullptr };
};

} // Stuff
#endif // TEXTURE_H
