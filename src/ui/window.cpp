#include <SDL2/SDL.h>

#include "formats/bmp.h"
#include "ui/window.h"
#include "util/log.h"

namespace ui {

Window::Window(std::string imagePath, int xPos, int yPos, int width, int height)
    : mWidth{width}, mHeight{height}, mMenuHeight{50}, mViewMenu{0, 0, width, mMenuHeight},
      mViewPreview{0, mMenuHeight, width, height - mMenuHeight} {

    mImage = new formats::Image;
    if (mImage->loadImage(imagePath) != 0) {
        LOG(ERROR, "Window: Unable to load image %s.\n", imagePath.c_str());
    }

    mImageInfo = {mWidth / 2 - mImage->getWidth() / 2, mHeight / 2 - mImage->getHeight(),
                  mImage->getWidth(), mImage->getHeight()};

    // Create the window
    mWindow = SDL_CreateWindow("Viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width,
                               height, SDL_WINDOW_RESIZABLE);
    if (mWindow == NULL) {
        LOG(ERROR, "Window: Unable to create window, %s.\n", SDL_GetError());
    } else {
        LOG(VERBOSE, "Window: Succesfully made window.\n");
    }

    // Set minimum window size
    SDL_SetWindowMinimumSize(mWindow, 500, 200);

    // Paint surface
    mSurface = SDL_GetWindowSurface(mWindow);
    if (mSurface == NULL) {
        LOG(ERROR, "Window: Unable to get window surface, %s.\n", SDL_GetError());
    }

    SDL_BlitScaled(mImage->getSurface(), NULL, mSurface, &mViewPreview);

    SDL_UpdateWindowSurface(mWindow);
}

Window::~Window() {
    delete mImage;
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
