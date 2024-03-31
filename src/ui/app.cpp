#include <SDL2/SDL.h>

#include "ui/app.h"
#include "ui/window.h"
#include "formats/bmp.h"
#include "formats/image.h"

namespace ui {

App::App() { mWindows.push_back(new ui::Window("assets/roundSquare.bmp")); }

App::~App() { mWindows.clear(); }

void App::startLoop() {

    SDL_Event e;
    while (true) {
        SDL_WaitEvent(&e);

        // Quit app
        if (e.type == SDL_QUIT)
            break;

        // Something for the window to handle
        if (e.type == SDL_WINDOWEVENT) {
            for (int i = 0; i < mWindows.size(); i++) {
                if (mWindows[i]->id() == e.window.windowID) {
                    if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
                        delete mWindows[i];
                        mWindows.erase(mWindows.begin() + i);
                    } else {
                        mWindows[i]->handleWindowEvent(e);
                    }
                }
            }
        }
    }
}

} // namespace ui
