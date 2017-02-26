#include "virt.h"

#include "virt/entity.h"
#include "virt/entity_templates.h"
#include "virt/node.h"
#include "virt/pulse.h"
#include "virt/pulsar.h"
#include "virt/rocket.h"
#include "virt/blimp.h"
#include "virt/explosion.h"
#include "virt/trail.h"

void Virt::setup() {
  ofSetCircleResolution(100);
  ofEnableAlphaBlending();
  Node::create(ofPoint(120, 120));
  Node::create(ofPoint(220, 220));
  Pulsar::create(ofPoint(320, 240));
}

void Virt::update(double dt) {
  Entity::updateCollection(Blood::collection, dt);
  Entity::updateCollection(Debris::collection, dt);
  Entity::updateCollection(BlimpDebris::collection, dt);
  Entity::updateCollection(RocketTrail::collection, dt);
  Entity::updateCollection(BlimpTrail::collection, dt);
  Entity::updateCollection(Pulse::collection, dt);
  Entity::updateCollection(Node::collection, dt);
  Entity::updateCollection(Pulsar::collection, dt);
  Entity::updateCollection(Rocket::collection, dt);
  Entity::updateCollection(Blimp::collection, dt);

  Entity::pruneCollection(Blood::collection);
  Entity::pruneCollection(Debris::collection);
  Entity::pruneCollection(BlimpDebris::collection);
  Entity::pruneCollection(RocketTrail::collection);
  Entity::pruneCollection(BlimpTrail::collection);
  Entity::pruneCollection(Pulse::collection);
  Entity::pruneCollection(Node::collection);
  Entity::pruneCollection(Pulsar::collection);
  Entity::pruneCollection(Rocket::collection);
  Entity::pruneCollection(Blimp::collection);

  Entity::collideCollection(Pulse::collection, Node::collection);
  Entity::collideCollection(Rocket::collection, Node::collection);
  Entity::collideCollection(Blimp::collection, Node::collection);

}

void Virt::draw() {
  Entity::drawCollection(Blood::collection);
  Entity::drawCollection(Debris::collection);
  Entity::drawCollection(BlimpDebris::collection);
  Entity::drawCollection(RocketTrail::collection);
  Entity::drawCollection(BlimpTrail::collection);
  Entity::drawCollection(Pulse::collection);
  Entity::drawCollection(Node::collection);
  Entity::drawCollection(Pulsar::collection);
  Entity::drawCollection(Rocket::collection);
  Entity::drawCollection(Blimp::collection);
}
