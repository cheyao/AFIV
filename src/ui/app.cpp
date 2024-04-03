#include <SDL2/SDL.h>
#include <string>
#include <vector>

#include "formats/bmp.h"
#include "formats/image.h"
#include "tinyfiledialogs.h"
#include "ui/app.h"
#include "ui/window.h"

namespace ui {

void App::newWindow() {
    // Ask for files
    char* f = tinyfd_openFileDialog("Select images", NULL, 0, NULL, NULL, 1);
    if (f == NULL) {
        return;
    }
    std::string files = f;

    // Split
    std::string delimiter = ">=";
    std::vector<std::string> listOfFiles{};

    size_t pos = 0;
    std::string token;
    while ((pos = files.find("|")) != std::string::npos) {
        token = files.substr(0, pos);
        listOfFiles.push_back(token);
        files.erase(0, pos + 1);
    }
    listOfFiles.push_back(files);

    for (std::string s : listOfFiles) {
        try {
            mWindows.push_back(new ui::Window(s));
        } catch (...) {
            continue; // ha nothing we can do
        }
    }
}

App::App() {
    newWindow();
}

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
