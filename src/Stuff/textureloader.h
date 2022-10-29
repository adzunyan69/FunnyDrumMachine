#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>
#include <SDL.h>

namespace Stuff::StuffPrivate
{

class TextureLoader
{
public:
    TextureLoader() = delete;

    static SDL_Texture* loadBMP(SDL_Renderer *renderer, const std::string &file)
    {
        SDL_Log("Loading texture %s", file.c_str());
        SDL_Texture *texture { nullptr };

        SDL_Surface *textureSurface { nullptr };
        textureSurface = SDL_LoadBMP(file.c_str());
        if(textureSurface == nullptr)
        {
            SDL_Log("Unable to create surface for the texture %s: %s", file.c_str(), SDL_GetError());
            return nullptr;
        }

        texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
        if(texture == nullptr)
        {
            SDL_Log("Unable to load texture %s: %s", file.c_str(), SDL_GetError());
            SDL_FreeSurface(textureSurface);
            return nullptr;
        }

        SDL_FreeSurface(textureSurface);
        return texture;
    }
};

} // Stuff

#endif // TEXTURELOADER_H
