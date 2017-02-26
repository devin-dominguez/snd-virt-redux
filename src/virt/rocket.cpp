#include "rocket.h"
#include "node.h"
#include "projector.h"
#include "depth_physics.h"

vector<Rocket> Rocket::collection;

void Rocket::create(ofPoint position, double angle) {
  collection.push_back(Rocket(position, angle));
}

Rocket::Rocket( ofPoint position, double angle) : Entity(position) {
  minSize = 10.0;
  maxSize = 20.0;
  size = minSize;
  minSpeed = 8.0;
  allowedDownTime = 0.2;

  initialSpeed = 150.0;

  fadeInTime = 0.125;
  fadeOutTime = 0.25;

  type = ROCKET;
  color = Entity::colors[2];

  penetrating = false;
  penetrationFadeOutTime = 0.1;

  PhysicsSettings settings;
  settings.mass = 12.0;
  settings.gravity = -981;
  settings.friction = 0.1;
  physics.setup(angle, initialSpeed, settings);
}

void Rocket::update(double dt) {
  switch(phase) {
    case NEW:
      fadeIn(dt);
      move(dt);
      break;
    case ALIVE:
      collidable = true;
      move(dt);
      break;
    case DYING:
      fadeOut(dt);
      if (penetrating) {
        move(dt);
      }
      collidable = false;;
      break;
    case DEAD:
      break;
  };
}

void Rocket::move(double dt) {
  ofVec2f velocity = physics.getVelocityAtPoint(position, dt);
  position += velocity * dt;
  ofRectangle bounds(0, 0, 640, 480);
  if (!bounds.inside(position)) {
    explode();
    kill();
  }

  double sqrSpeed = (velocity.x * velocity.x) + (velocity.y * velocity.y);
  if (sqrSpeed <= minSpeed) {
    downTime += dt;
  } else {
    downTime = 0;
  }

  if (downTime >= allowedDownTime) {
    explode();
    kill();
  }

}

void Rocket::collideWith(Entity* entity) {
  switch(entity->type) {
    case NODE:
      if (((Node*)entity)->pulseReady()) {
        penetrating = true;
        penetrate();
      } else {
        explode();
      }
      kill();
      break;
    default:
      break;
  }
}

void Rocket::explode() {
  cout << "BLAM" << endl;
}

void Rocket::penetrate() {
  cout << "SPLAT" << endl;
}

void Rocket::draw() {
  ofPoint screenPosition = Projector::getCoords(position);
  double screenSize = Projector::getScale(size);
  double angle = physics.getAngle();

 	ofPushMatrix();
	ofPushStyle();
		ofTranslate(screenPosition);
		ofRotate(angle * 180 / M_PI);
		ofSetColor(color, 255.0 * fadeLevel);
    ofFill();
		ofBeginShape();
			ofVertex(screenSize, 0);
			ofVertex(-screenSize, screenSize / 2.0);
			ofVertex(0, 0);
			ofVertex(-screenSize, -screenSize / 2.0);
			ofVertex(screenSize, 0);
		ofEndShape();
	ofPopStyle();
	ofPopMatrix();
}
