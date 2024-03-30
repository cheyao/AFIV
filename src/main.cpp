#include <SDL2/SDL.h>
#include <SDL2/SDL_shape.h>
#include <string>
#include <vector>

#include "ui/app.h"
#include "ui/window.h"
#include "util/log.h"

int wWidth = 0;
int wHeight = 0;

std::vector<ui::Window*> windows{};

int main(int argc, char* argv[]) {
    // Setup log
    util::set_log_filename("log.log");
#ifdef _DEBUG
    util::set_log_level(VERBOSE);
#else
    util::set_log_level(ERROR);
#endif
    LOG(VERBOSE, "Main: Starting program.\n");

    // Init SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        LOG(ERROR, "Main: Failed to init SDL %s.\n", SDL_GetError());
    }

    windows.push_back(new ui::Window());
    windows.push_back(new ui::Window());

    SDL_Event e;
    while (true) {
        SDL_WaitEvent(&e);

        // Quit app
        if (e.type == SDL_QUIT)
            break;

        // Something for the window to handle
        if (e.type == SDL_WINDOWEVENT) {
            for (int i = 0; i < windows.size(); i++) {
                if (windows[i]->id() == e.window.windowID) {
                    if (e.window.event == SDL_WINDOWEVENT_CLOSE) {
                        delete windows[i];
                        windows.erase(windows.begin() + i);
                    } else {
                        windows[i]->handleWindowEvent(e);
                    }
                }
            }
        }
    }

    windows.clear();

    /*
                    SDL_Event e = {SDL_QUIT};
                    e.quit.timestamp = SDL_GetTicks();
                    e.quit.type = SDL_QUIT;
                    SDL_PushEvent(&e);
    */

    SDL_Quit();
    return 0;
}