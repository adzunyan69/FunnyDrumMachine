#ifndef BUTTON_H
#define BUTTON_H

#include <memory>
#include <functional>
#include "../Stuff/texture.h"

namespace GUI
{

class Button
{
public:
  Button(SDL_Renderer *renderer,
         const std::string &file,
         const SDL_Rect &pos,
         std::function< void(void) > &callback);
  virtual ~Button();

  void render(float timeStep);
  void handleEvent(const SDL_Event &event);
  void setEnabled(bool enable);
  bool isEnabled() const;

private:
  std::unique_ptr<Stuff::Texture> buttonTexture{ nullptr };
  const SDL_Rect pos;
  bool enabled { true };
  std::function< void(void) > callback;

  const Uint8 minTransparency{ 64 };
  const Uint8 maxTransparency{ 255 };
  const Uint8 transparencyChangePerSecond{ 125 };
  float currentTransparency{ static_cast<float>(maxTransparency) };
  bool isIncreasingTransparency{ false };

  void increaseTransparency(float transparencyStep);
  void decreaseTransparency(float transparencyStep);
};

} // GUI

#endif // BUTTON_H
