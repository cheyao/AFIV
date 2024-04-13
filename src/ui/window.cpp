#include <SDL2/SDL.h>

#include "tinyfiledialogs.h"
#include "ui/window.h"
#include "util/log.h"

namespace ui {

/*
 * Window:
 * Menu
 * Tabs
 * Image
 */
Window::Window(int width, int height)
    : mWidth{width}, mHeight{height}, mMenuHeight{50}, mViewMenu{0, 0, width, mMenuHeight},
      mViewPreview{0, mMenuHeight, width, height - mMenuHeight} {
        // Ask for files
        char* f = tinyfd_openFileDialog("Select images", NULL, 0, NULL, NULL, 1);
        if (f == NULL) {
                return;
        }
        std::string files = f;

        // Split
        std::vector<std::string> listOfFiles{};

        size_t pos = 0;
        std::string token;
        while ((pos = files.find("|")) != std::string::npos) {
                token = files.substr(0, pos);
                listOfFiles.push_back(token);
                files.erase(0, pos + 1);
        }
        listOfFiles.push_back(files);

        // Open the images
        for (std::string s : listOfFiles) {
                try {
                        mImages.push_back(new formats::Image(s));
                        mTab++;
                } catch (...) {
                        continue; // Ha nothing we can do
                }
        }

        // Create the window
        mWindow = SDL_CreateWindow("Viewer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                   width, height, SDL_WINDOW_RESIZABLE);
        if (mWindow == NULL) {
                LOG(ERROR, "Window: Unable to create window, %s.\n", SDL_GetError());
                throw "Window: Unable to create window.\n";
        } else {
                LOG(VERBOSE, "Window: Succesfully made window.\n");
        }

        // Set minimum window size
        SDL_SetWindowMinimumSize(mWindow, 500, 200);

        // Paint surface
        mSurface = SDL_GetWindowSurface(mWindow);
        if (mSurface == NULL) {
                LOG(ERROR, "Window: Unable to get window surface, %s.\n", SDL_GetError());
                throw "Window: Unable to get window surface.\n";
        }

        // Set window icon for windows
#if defined(_WIN32) && defined(GCL_HICON)
        setWindowsIcon(mWindow);
#endif
}

Window::~Window() {
        SDL_FreeSurface(mSurface);
        SDL_DestroyWindow(mWindow);
        LOG(VERBOSE, "Window: Destroyed window.\n");
}

#if defined(_WIN32) && defined(GCL_HICON)
void Window::setWindowsIcon(SDL_Window* sdlWindow) {
        HINSTANCE handle = ::GetModuleHandle(nullptr);
        HICON icon = ::LoadIcon(handle, "AFIV.ico");
        if (icon != nullptr) {
                SDL_SysWMinfo wminfo;
                SDL_VERSION(&wminfo.version);
                if (SDL_GetWindowWMInfo(sdlWindow, &wminfo) == 1) {
                        HWND hwnd = wminfo.info.win.window;
                        ::SetClassLong(hwnd, GCL_HICON, reinterpret_cast<LONG>(icon));
                }
        }
}
#endif

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
