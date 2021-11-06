//
// Created by hegeda on 2021-09-28.
//

#include <memory>
#include "Application.h"

int main()
{
    auto app = std::make_unique<Application>("Simulator");
    app->loop();

//    glm::vec2 a = {0.005259f, 0.010518f};
//    glm::vec2 b = {-0.099824, -0.199649};
//    glm::vec2 norm_b = glm::normalize(b);
//    //glm::float32 c = 0.223214f;
//    //glm::vec2 res = {-0.002352, -0.009408};
//    glm::vec2 p = a * norm_b;
//    printf("%f %f", p.x, p.y);
//
//    glm::vec2 res2 = (glm::dot(a, norm_b) / glm::dot(norm_b, norm_b)) * norm_b;
//    printf("\n%f %f", res2.x, res2.y);

    return 0;
}