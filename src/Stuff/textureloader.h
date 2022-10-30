#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <string>
#include <SDL.h>
#include <SDL_ttf.h>

namespace Stuff::StuffPrivate
{

class TextureLoader
{
public:
  TextureLoader() = delete;

  static SDL_Texture* loadBMP(SDL_Renderer *renderer, const std::string &file)
  {
    SDL_Texture *texture { nullptr };
    SDL_Surface *textureSurface { nullptr };

    textureSurface = SDL_LoadBMP(file.c_str());
    if( textureSurface == nullptr )
    {
      SDL_Log("Unable to create surface for the texture %s: %s", file.c_str(), SDL_GetError());
      return nullptr;
    }

    texture = SDL_CreateTextureFromSurface(renderer, textureSurface);
    if( texture == nullptr )
    {
      SDL_Log("Unable to load texture %s: %s", file.c_str(), SDL_GetError());
      SDL_FreeSurface(textureSurface);
      return nullptr;
    }

    SDL_FreeSurface(textureSurface);
    return texture;
  }

  static SDL_Texture* loadTextTexture(SDL_Renderer *renderer,
                                      const std::string &text,
                                      TTF_Font *font,
                                      SDL_Color color)
  {
    SDL_Texture *textTexture { nullptr };
    SDL_Surface *textSurface { nullptr };

    textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
    if( textSurface == nullptr )
    {
      SDL_Log("Unable to create surface for the text %s: %s", text.c_str(), TTF_GetError());
      return nullptr;
    }

    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if( textTexture == nullptr )
    {
      SDL_Log("Unable to load texture for the text %s: %s", text.c_str(), SDL_GetError());
      SDL_FreeSurface(textSurface);
      return nullptr;
    }

    SDL_FreeSurface(textSurface);
    return textTexture;
  }
};

} // Stuff

#endif // TEXTURELOADER_H
