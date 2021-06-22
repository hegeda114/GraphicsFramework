//
// Created by hegeda on 2021-02-11.
//

#include "Scene.h"
#include "Circle.h"
#include "Point.h"

void Scene::Build() {
    //ide jöhetnek a cuccok

    auto* c = new Circle({0.0, 0.0}, 1, {0.8, 0.8, 0.8, 1});
    c->create(); //TODO ezt NE így!
    geometries.push_back(c);

}

void Scene::Render() const{
    for(Geometry* g : geometries) {
        g->Draw();
    }
}

void Scene::addPoint(Geometry* geom) {
    geom->create();
    geometries.push_back(geom);
}

Geometry* Scene::getTopGeometry(vec2 position) const{
    for(int i = geometries.size()-1; i > -1; i--) {
        if(geometries[i]->isMovable() && geometries[i]->isInside(position.x, position.y)) {
            return geometries[i];
        }
    }
}

void Scene::Animate() {
    for(Geometry* g : geometries) {
        if(g->isMovable()) {
            g->create();
            g->Draw();
        }
    }
}
