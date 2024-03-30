#ifndef APP_H
#define APP_H
#pragma once

#include <SDL2/SDL.h>

namespace ui {

class App {
  private:

  public:
    App();
    App(int width, int height);
    ~App();
};

} // namespace app

#endif // APP_H