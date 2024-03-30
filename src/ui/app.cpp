#include <SDL2/SDL.h>

#include "ui/app.h"

namespace ui {

App::App() {
    App(1024, 768); // Default width and height
}

App::App(const int width, const int height) {
    
}

App::~App() {
}

}