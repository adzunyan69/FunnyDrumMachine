#ifndef TEXTURE_H
#define TEXTURE_H

#include "textureloader.h"

namespace Stuff
{
class Texture
{
public:
    Texture(SDL_Renderer *renderer, const std::string &file);
    Texture(const Texture&) = delete;
    ~Texture();

    void renderTexture(const SDL_Rect &rect);

private:
    SDL_Renderer *renderer{ nullptr };
    SDL_Texture *texture{ nullptr };
};

} // Stuff
#endif // TEXTURE_H
