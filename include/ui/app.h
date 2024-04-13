#ifndef APP_H
#define APP_H
#pragma once

#include <SDL2/SDL.h>
#include <vector>

#include "ui/window.h"

namespace ui {

class App {
      private:
        std::vector<ui::Window*> mWindows{};
        void newWindow();

      public:
        App();
        ~App();

        void startLoop();
};

} // namespace ui

#endif // APP_H
