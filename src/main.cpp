#include <SDL2/SDL.h>
#include <SDL2/SDL_shape.h>
#include <string>

#include "ui/app.h"
#include "ui/window.h"
#include "util/log.h"

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

    ui::App* mainApp = new ui::App();

    mainApp->startLoop();

    delete mainApp;

    SDL_Quit();
    return 0;
}