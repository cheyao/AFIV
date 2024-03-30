#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <SDL2/SDL.h>

namespace ui {

class Window {
  private:
    SDL_Window* mWindow;
    SDL_Surface* mMask;
    int mWidth, mHeight;

  public:
    Window();
    Window(int width, int height);
    Window(int xPos, int yPos, int width, int height);

    void handleWindowEvent(const SDL_Event& e);

    Uint32 id() const { return SDL_GetWindowID(mWindow); };

    ~Window();
};

} // namespace ui

#endif // WINDOW_H