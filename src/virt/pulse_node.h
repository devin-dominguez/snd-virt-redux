#pragma once

#include "ofMain.h"
#include "entity.h"
#include "projector.h"

class PulseNode {
  public:
    PulseNode();
    void action(double dt);
    void collideWith(Entity* entity);
    void draw(double fadeLevel);

  private:
    void cooling(double dt);
    void collisionAction();
    ofFloatColor color;
    double coolDownTime;
    double coolDown;

    bool colliding;
    bool collided;
    bool ready;

    double maxSize;
    double size;
    double sizeTarget;
    double lerpRate;
    double rotationRate;
    double rotation;
    int spinnerResolution;
};
