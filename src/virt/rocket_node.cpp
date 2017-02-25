#include "rocket_node.h"

RocketNode::RocketNode() {
  coolDownTime = 3.0;
  coolDown = 0.0;
  colliding = false;
  collided = false;
  ready = false;

  color = Entity::colors[2];

  numRockets = 9;

  maxSize = 24.0;
  size = 0.0;
  sizeTarget = 0.0;
  rotation = 0.0;
  rotationRate = 360.0 / -6.0;
  lerpRate = 10.0;
}

void RocketNode::action(double dt) {
  cooling(dt);
  collisionAction();
  rotation += rotationRate * dt;

  sizeTarget = ready ? maxSize : maxSize * 0.8;
  size = ofLerp(size, sizeTarget, lerpRate * dt);
}

void RocketNode::collideWith(Entity* entity) {
  colliding = true;
}

void RocketNode::cooling(double dt) {
  if (coolDown > 0.0) {
    coolDown -= dt;
    ready = false;
  } else {
    ready = true;
    coolDown = 0.0;
  }
}

void RocketNode::collisionAction() {
  if (collided != colliding) {
    collided = colliding;
    if (collided && ready) {
      coolDown = coolDownTime;
      // spawn rockets
      cout << "ROCKETS!" << endl;
    }
  }

  colliding = false;
}

void RocketNode::draw(double fadeLevel) {
  double screenSize = Projector::getScale(size);
  double screenDistance = Projector::getScale(3.0);

  ofPushStyle();
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(color, 255.0 * fadeLevel);
    for (size_t i = 0; i < numRockets; i++) {
      double angle = 360.0 * (double)i / (double)numRockets + rotation;
      ofPushMatrix();
      ofRotate(angle);
        ofBeginShape();
          ofVertex(screenSize * 1.5, 0);
          ofVertex(0, -screenDistance);
          ofVertex(0, screenDistance);
        ofEndShape();
      ofPopMatrix();
    }
  ofPopStyle();
}

