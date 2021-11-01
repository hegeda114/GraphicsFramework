//
// Created by hegeda on 2021-09-28.
//

#include <memory>
#include "Application.h"

int main()
{
    auto app = std::make_unique<Application>("Simulator");
    app->loop();

    return 0;
}