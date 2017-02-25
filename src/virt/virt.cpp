#include "virt.h"

#include "virt/entity.h"
#include "virt/entity_templates.h"
#include "virt/node.h"
#include "virt/pulse.h"
#include "virt/pulsar.h"

void Virt::setup() {
  ofSetCircleResolution(100);
  Node::create(ofPoint(120, 120));
  Node::create(ofPoint(220, 220));
  Pulsar::create(ofPoint(320, 240));
}

void Virt::update(double dt) {
  Entity::updateCollection(Pulse::collection, dt);
  Entity::updateCollection(Node::collection, dt);
  Entity::updateCollection(Pulsar::collection, dt);

  Entity::pruneCollection(Pulse::collection);
  Entity::pruneCollection(Node::collection);
  Entity::pruneCollection(Pulsar::collection);

  Entity::collideCollection(Pulse::collection, Node::collection);

}

void Virt::draw() {
  Entity::drawCollection(Pulse::collection);
  Entity::drawCollection(Node::collection);
  Entity::drawCollection(Pulsar::collection);
}
