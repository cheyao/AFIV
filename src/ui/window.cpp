#include <SDL2/SDL.h>

#include "ui/window.h"
#include "util/log.h"

namespace ui {

Window::Window()
    : Window(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1024, 768) {}

Window::Window(int width, int height)
    : Window(SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height) {}

Window::Window(int xPos, int yPos, int width, int height) {
    mWidth = width;
    mHeight = height;

    // Create the window
    mWindow = SDL_CreateWindow("Viewer", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, width, height,
                               SDL_WINDOW_RESIZABLE);
    if (mWindow == NULL) {
        LOG(ERROR, "Window: Unable to create window, %s.\n", SDL_GetError());
    } else {
        LOG(VERBOSE, "Window: Succesfully made window.\n");
    }
}

Window::~Window() {
    SDL_DestroyWindow(mWindow);
    LOG(VERBOSE, "Window: Destroyed window.\n");
}

void Window::handleWindowEvent(const SDL_Event& e) {
    // Type == SDL_WINDOWEVENT
    switch (e.window.event) {
        case SDL_WINDOWEVENT_SIZE_CHANGED: {
            mWidth = e.window.data1;
            mHeight = e.window.data2;
            LOG(VERBOSE, "Window: Size changed to %ix%i\n", mWidth, mHeight);
            break;
        }
    }
}

} // namespace ui
