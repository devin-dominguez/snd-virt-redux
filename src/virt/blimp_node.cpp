#include "blimp_node.h"

BlimpNode::BlimpNode() {
  coolDownTime = 3.0;
  coolDown = 0.0;
  colliding = false;
  collided = false;
  ready = false;

  color = Entity::colors[2];

  numBlimps = 3;

  maxSize = 21.0;
  size = 0.0;
  sizeTarget = 0.0;
  rotation = 0.0;
  rotationRate = 360.0 / -6.0;
  lerpRate = 10.0;
}

void BlimpNode::action(double dt) {
  cooling(dt);
  collisionAction();
  rotation += rotationRate * dt;

  sizeTarget = ready ? maxSize : maxSize * 0.8;
  size = ofLerp(size, sizeTarget, lerpRate * dt);
}

void BlimpNode::collideWith(Entity* entity) {
  colliding = true;
}

void BlimpNode::cooling(double dt) {
  if (coolDown > 0.0) {
    coolDown -= dt;
    ready = false;
  } else {
    ready = true;
    coolDown = 0.0;
  }
}

void BlimpNode::collisionAction() {
  if (collided != colliding) {
    collided = colliding;
    if (collided && ready) {
      coolDown = coolDownTime;
      // spawn rockets
      cout << "BLIMPS!" << endl;
    }
  }

  colliding = false;
}

		//for(unsigned int i = 0; i < particleBAmmount; i++) {
			//double angle = 360.0 * (double)i / (double)particleBAmmount + rotation ;
			//ofPushMatrix();
				//ofRotate(angle);
					//ofSetRectMode(OF_RECTMODE_CENTER);
					//ofRectRounded(size, 0, ampB, size * .35, 10);
				//ofPopMatrix();
		//}

void BlimpNode::draw(double fadeLevel) {
  double screenSize = Projector::getScale(size);

  ofPushStyle();
    ofEnableAlphaBlending();
    ofFill();
    ofSetColor(color, 255.0 * fadeLevel);
    for (size_t i = 0; i < numBlimps; i++) {
      double angle = 360.0 * (double)i / (double)numBlimps + rotation;
      ofPushMatrix();
      ofRotate(angle);
        ofBeginShape();
					ofSetRectMode(OF_RECTMODE_CENTER);
					ofDrawRectRounded(screenSize, 0, screenSize, screenSize * 0.35, 10.0);
        ofEndShape();
      ofPopMatrix();
    }
  ofPopStyle();
}

