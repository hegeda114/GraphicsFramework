//
// Created by hegeda on 2021-11-01.
//

#ifndef GRAPHICSFRAMEWORK_ORTHOGONALCAMERA_H
#define GRAPHICSFRAMEWORK_ORTHOGONALCAMERA_H

#include "glm.hpp"
#include "../Shader.h"

class OrthogonalCamera {
private:
    glm::vec3 position = {0, 0, 0};
    float roll = 0;
    glm::mat4 m_viewProjMatrix = {};
public:
    OrthogonalCamera() = default;
    void setAspectRation(float aspectRatio);
    void update(const Shader* shader) const;
};


//struct Camera { // 3D camera
//---------------------------
//    vec3 wEye, wLookat, wVup;   // extrinsic
//    float fov, asp, fp, bp;		// intrinsic
//public:
//    Camera() {
//        asp = (float)windowWidth / windowHeight;
//        fov = 75.0f * (float)M_PI / 180.0f;
//        fp = 1; bp = 20;
//    }
//    mat4 V() { // view matrix: translates the center to the origin
//        vec3 w = normalize(wEye - wLookat);
//        vec3 u = normalize(cross(wVup, w));
//        vec3 v = cross(w, u);
//        return TranslateMatrix(wEye * (-1)) * mat4(u.x, v.x, w.x, 0,
//                                                   u.y, v.y, w.y, 0,
//                                                   u.z, v.z, w.z, 0,
//                                                   0,   0,   0,   1);
//    }
//
//    mat4 P() { // projection matrix
//        return mat4(1 / (tan(fov / 2)*asp), 0,                0,                      0,
//                    0,                      1 / tan(fov / 2), 0,                      0,
//                    0,                      0,                -(fp + bp) / (bp - fp), -1,
//                    0,                      0,                -2 * fp*bp / (bp - fp),  0);
//    }
//};
//
//class OrthoCamera(vararg programs : Program) : UniformProvider("camera") {
//
//val position = Vec2(0.0f, 0.0f)
//val roll = 0.0f
//val windowSize = Vec2(2.0f, 2.0f)
//
//val viewProjMatrix by Mat4()
//init{
//updateViewProjMatrix()
//addComponentsAndGatherUniforms(*programs)
//}
//
//fun updateViewProjMatrix() {
//    viewProjMatrix.set().
//            scale(0.5f, 0.5f).
//            scale(windowSize).
//            rotate(roll).
//            translate(position).
//            invert()
//}
//
//    fun setAspectRatio(ar : Float) {
//        windowSize.x = windowSize.y * ar
//        updateViewProjMatrix()
//    }
//}


#endif //GRAPHICSFRAMEWORK_ORTHOGONALCAMERA_H
