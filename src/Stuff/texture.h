#ifndef TEXTURE_H
#define TEXTURE_H

#include <memory>
#include "textureloader.h"
#include <SDL_ttf.h>

namespace Stuff
{
class Texture
{
public:

  static std::unique_ptr<Texture> loadTexture(
      SDL_Renderer *renderer,
      const std::string &file,
      SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);

  static std::unique_ptr<Texture> loadTextTexture(
      SDL_Renderer *renderer,
      const std::string &text,
      TTF_Font *font,
      SDL_Color color);

  virtual ~Texture();

  void renderTexture(const SDL_Rect &dst);
  void renderTexture(const SDL_Rect &src, const SDL_Rect &dst);
  void updateTransparency(Uint8 a);

private:
  Texture(SDL_Renderer *renderer,
          const std::string &file,
          SDL_BlendMode blendMode = SDL_BLENDMODE_BLEND);

  Texture(SDL_Renderer *renderer,
          const std::string &text,
          TTF_Font *font,
          SDL_Color color);

  SDL_Renderer *renderer{ nullptr };
  SDL_Texture *texture{ nullptr };
};

} // Stuff
#endif // TEXTURE_H
