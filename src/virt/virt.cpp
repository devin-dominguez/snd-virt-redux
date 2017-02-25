#include "virt.h"

#include "virt/entity.h"
#include "virt/entity_templates.h"
#include "virt/node.h"
#include "virt/pulse.h"

void Virt::setup() {
  ofSetCircleResolution(100);
  Node::create(ofPoint(120, 120));
  Node::create(ofPoint(220, 220));
}

void Virt::update(double dt) {
  Entity::updateCollection(Pulse::collection, dt);
  Entity::updateCollection(Node::collection, dt);

  Entity::pruneCollection(Pulse::collection);
  Entity::pruneCollection(Node::collection);

  Entity::collideCollection(Pulse::collection, Node::collection);

  if (ofGetFrameNum() % 120 == 0) {
    Pulse::create(ofPoint(120, 120), 20, Pulse::DEFAULT);
    Pulse::create(ofPoint(220, 220), 20, Pulse::ORIGIN);
  }
}

void Virt::draw() {
  Entity::drawCollection(Pulse::collection);
  Entity::drawCollection(Node::collection);
}
