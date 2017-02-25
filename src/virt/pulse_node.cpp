#include "pulse_node.h"
PulseNode::PulseNode() {
  coolDownTime = 6.0;
  coolDown = 0.0;
  colliding = false;
  collided = false;
  ready = false;

  color = Entity::colors[2];

  maxSize = 42.0;
  size = 0.0;
  sizeTarget = 0.0;
  rotationRate = 360.0 / 6.0;
  rotation = 0.0;
  spinnerResolution = 6;
  lerpRate = 5.0;
}

void PulseNode::action(double dt) {
  cooling(dt);
  collisionAction();
  rotation += rotationRate * dt;

  sizeTarget = ready ? maxSize : 0.8;
  size = ofLerp(size, sizeTarget, lerpRate * dt);
}

void PulseNode::collideWith(Entity* entity) {
  colliding = true;
}

void PulseNode::cooling(double dt) {
  if (coolDown > 0.0) {
    coolDown -= dt;
    ready = false;
  } else {
    ready = true;
    coolDown = 0.0;
  }
}

void PulseNode::collisionAction() {
  if (collided != colliding) {
    collided = colliding;
    if (collided && ready) {
      coolDown = coolDownTime;
      // spawn pulse
      cout << "PULSE!" << endl;
    }
  }

  colliding = false;
}

void PulseNode::draw(double fadeLevel) {
  double screenSize = Projector::getScale(size);

  ofPushStyle();
    ofEnableAlphaBlending();
    ofNoFill();
    ofSetColor(color, 255.0 * fadeLevel);
    ofSetCircleResolution(spinnerResolution);
    ofPushMatrix();
      ofRotate(rotation);
      ofDrawCircle(0, 0, screenSize);
    ofPopMatrix();
  ofPopStyle();
}
