//
// Created by hegeda on 2021-09-28.
//

#ifndef GRAPHICSFRAMEWORK_UICONTEXT_H
#define GRAPHICSFRAMEWORK_UICONTEXT_H


#include "Window.h"
#include <memory>

class UIContext {
public:
    bool init(Window* parentWindow);
    void pre_render();
    void post_render();
//    void end;
private:
    Window* parentWindow;
};


#endif //GRAPHICSFRAMEWORK_UICONTEXT_H
