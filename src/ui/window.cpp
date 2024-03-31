#include <SDL2/SDL.h>

#include "formats/bmp.h"
#include "ui/window.h"
#include "util/log.h"

namespace ui {

Window::Window(std::string imagePath, int xPos, int yPos, int width, int height)
    : mWidth{width}, mHeight{height}, mMenuHeight{50}, mViewMenu{0, 0,
                                                                 mMenuHeight,
                                                                 width},
      mViewPreview{0, mMenuHeight, height - mMenuHeight, width} {

    mImage = new formats::Image;
    if (mImage->loadImage(imagePath) != 0) {
        LOG(ERROR, "Window: Unable to load image %s.\n", imagePath.c_str());
    }

    // Create the window
    mWindow = SDL_CreateWindow("Viewer", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width, height,
                               SDL_WINDOW_RESIZABLE);
    if (mWindow == NULL) {
        LOG(ERROR, "Window: Unable to create window, %s.\n", SDL_GetError());
    } else {
        LOG(VERBOSE, "Window: Succesfully made window.\n");
    }

    // Set minimum window size
    SDL_SetWindowMinimumSize(mWindow, 300, 60);

    // Create the renderer
    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_SOFTWARE);
    if (mRenderer == NULL) {
        LOG(ERROR, "Window: Unable to create renderer, %s.\n", SDL_GetError());
    } else {
        LOG(VERBOSE, "Window: Succesfully made renderer.\n");
    }
}

Window::~Window() {
    delete mImage;
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    LOG(VERBOSE, "Window: Destroyed window.\n");
}

void Window::handleWindowEvent(const SDL_Event& e) {
    // Type == SDL_WINDOWEVENT
    switch (e.window.event) {
    case SDL_WINDOWEVENT_SIZE_CHANGED: {
        mWidth = e.window.data1;
        mHeight = e.window.data2;
        mViewMenu.w = mWidth;
        mViewPreview.h = mHeight - mMenuHeight;
        mViewPreview.w = mWidth;

        LOG(VERBOSE, "Window: Size changed to %ix%i\n", mWidth, mHeight);
        break;
    }
    }
}

} // namespace ui
