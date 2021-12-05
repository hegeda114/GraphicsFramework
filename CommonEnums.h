//
// Created by hegeda on 2021-10-03.
//

#ifndef GRAPHICSFRAMEWORK_COMMONENUMS_H
#define GRAPHICSFRAMEWORK_COMMONENUMS_H

enum Direction {Top, Right, Bottom, Left};

enum ViewportMode {Default, Grab, PointCreation, SpringCreation, ViewPan};

enum SimulationApproach { MassSpringSystem, PositionBasedDynamics, ShapeMatching };

enum SimulationMode { ExplicitEuler, SemiImplicitEuler, RungeKuttaSecondOrder, RungeKuttaFourthOrder };

enum PBDConstraint { Stretching};

enum MenuCommand { OpenScene, SaveScene, AddPoint, AddStaticPoint, AddSpring, None };

#endif //GRAPHICSFRAMEWORK_COMMONENUMS_H
