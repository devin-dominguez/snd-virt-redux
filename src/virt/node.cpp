#include "node.h"
#include "projector.h"
#include "pulse.h"

vector<Node> Node::collection;
void Node::create(ofPoint position) {
  collection.push_back(Node(position));
}

Node::Node(ofPoint position) : Entity(position) {
  size = 24.0;
  fadeInTime = 1.0;
  fadeOutTime = 1.0;
  type = NODE;
  color = Entity::colors[4];

  pulseNode.setup(position, size);
  rocketNode.setup(position, size);
  blimpNode.setup(position, size);
}

void Node::update(double dt) {
  switch(phase) {
    case NEW:
      fadeIn(dt);
      break;
    case ALIVE:
      collidable = true;
      action(dt);
      break;
    case DYING:
      fadeOut(dt);
      collidable = false;
      break;
    case DEAD:
      break;
  };
}

bool Node::pulseReady() {
  return pulseNode.ready;
}

void Node::collideWith(Entity* entity) {
  switch(entity->type) {
    case PULSE:
      switch( ((Pulse*)entity)->pulseType) {
        case Pulse::ORIGIN:
          rocketNode.collideWith(entity);
          break;
        case Pulse::DEFAULT:
          blimpNode.collideWith(entity);
          break;
      }
      break;
    case ROCKET:
      pulseNode.collideWith(entity);
      break;
    default:
      break;
  }
}

void Node::action(double dt) {
  pulseNode.action(dt);
  rocketNode.action(dt);
  blimpNode.action(dt);
}

void Node::draw() {
  ofPoint screenPosition = Projector::getCoords(position);
  double screenSize = Projector::getScale(size);

  ofPushMatrix();
    ofTranslate(screenPosition);
    rocketNode.draw(fadeLevel);
    pulseNode.draw(fadeLevel);
    blimpNode.draw(fadeLevel);

    // core
    ofPushStyle();
      ofSetColor(color, 255.0 * fadeLevel * 0.5);
      ofDrawCircle(0, 0, screenSize);
      ofSetColor(Entity::colors[0], 255.0 * fadeLevel);
      ofDrawCircle(0, 0, 0.75 * screenSize);
    ofPopStyle();

  ofPopMatrix();
}
