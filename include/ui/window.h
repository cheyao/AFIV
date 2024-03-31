#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <SDL2/SDL.h>

#include "formats/image.h"

namespace ui {

class Window {
  private:
    // Default values
    int mWidth, mHeight;
    int mMenuHeight;
    // Window
    SDL_Window* mWindow;
    SDL_Surface* mMask;
    SDL_Renderer* mRenderer;
    formats::Image* mImage;
    // Viewport rectangles
    SDL_Rect mViewMenu;
    SDL_Rect mViewPreview;

  public:
    Window(std::string imagePath, int xPos = SDL_WINDOWPOS_UNDEFINED, int yPos = SDL_WINDOWPOS_UNDEFINED, int width = 1024, int height = 768);

    void handleWindowEvent(const SDL_Event& e);

    Uint32 id() const { return SDL_GetWindowID(mWindow); };
    SDL_Renderer* renderer() { return mRenderer; };

    ~Window();
};

} // namespace ui

#endif // WINDOW_H