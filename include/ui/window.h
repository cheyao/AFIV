#ifndef WINDOW_H
#define WINDOW_H
#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "formats/image.h"
#include "ui/preview.h"

namespace ui {

class Window {
      private:
        // Default values
        int mWidth, mHeight;
        int mMenuHeight;
        int mTab;
        // Window
        SDL_Window* mWindow;
        SDL_Surface* mSurface;
        ui::Preview* mPreview;
        // Viewport rectangles
        SDL_Rect mViewMenu;
        SDL_Rect mViewPreview;
        // Files and stuff
        std::vector<formats::Image*> mImages;

      public:
        Window(int width = 1024, int height = 768);
        ~Window();

        void handleWindowEvent(const SDL_Event& e);
        void drawImage(void);
	void render(void);

#if defined(_WIN32) && defined(GCL_HICON)
        void setWindowsIcon(SDL_Window* sdlWindow);
#endif
        Uint32 id() const { return SDL_GetWindowID(mWindow); };
};

} // namespace ui

#endif // WINDOW_H
