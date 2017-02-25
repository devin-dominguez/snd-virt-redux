#include "projector.h"

// Data
double Projector::worldWidth = 640;
double Projector::worldHeight = 480;
int Projector::width = 640;
int Projector::height = 480;
double Projector::left = 1;
double Projector::right = Projector::width;
double Projector::top = 1;
double Projector::bottom = Projector::height;
double Projector::rotation = 0;

// Objects
ofPoint Projector::position = ofPoint(0, 0);
ofRectangle Projector::bounds = ofRectangle(
  0, 0, Projector::width, Projector::height
);


// Lifecycle Methods
void Projector::setup() {} // TODO

void Projector::startDraw() {
    ofPushMatrix();
      ofTranslate(position + bounds.getCenter());
      ofRotate(rotation);
}

void Projector::endDraw() {
      drawMasking();
  ofPopMatrix();
}

// Data Interface

void Projector::setWorldDimensions(double width, double height) {
  worldWidth = width;
  worldHeight = height;
}

void Projector::changeSize(int dLeft, int dRight, int dTop, int dBottom) {
  left = ofClamp(left + dLeft, 0, width / 2);
  right = ofClamp(right + dRight, width / 2 + 1, width);
  top = ofClamp(top + dTop, 0, height / 2);
  bottom = ofClamp(bottom + dBottom, height / 2 + 1, height);
  updateBounds();
}

void Projector::changeRotation(double dRot) {
  rotation += dRot;
}

void Projector::changePosition(ofVec2f offset) {
  position += offset;
}

void Projector::drawBounds() {
  ofPushStyle();

  ofNoFill();
  ofDrawRectangle(-bounds.getCenter(), bounds.width, bounds.height);
  ofDrawCircle(0, 0, 10);
  ofPopStyle();
}

ofPoint Projector::getCoords(ofPoint position) {
  double ratioX = bounds.width / worldWidth;
  double ratioY = bounds.height / worldHeight;
  double x = ratioX * position.x + bounds.x;
  double y = ratioY * position.y + bounds.y;

  return ofPoint(x, y) - bounds.getCenter();
}

double Projector::getScale(double size) {
  double ratioX = bounds.width / worldWidth;
  double ratioY = bounds.height / worldHeight;

  return size * fmax(ratioX, ratioY);
}

// Internal Methods
void Projector::drawMasking() {
  ofPoint offset = bounds.getCenter();
  ofPushStyle();
  ofSetColor(0);
  ofFill();
  ofDrawRectangle(ofPoint(-25000, 0) - offset, 50000, -25000);
  ofDrawRectangle(ofPoint(-25000, bounds.height) - offset, 50000, 25000);
  ofDrawRectangle(ofPoint(0, -25000) - offset, -25000, 50000);
  ofDrawRectangle(ofPoint(bounds.width, -25000) - offset, 25000, 50000);

  ofPopStyle();
}

void Projector::updateBounds() {
  bounds.y = top;
  bounds.x = left;
  bounds.height = bottom - top;
  bounds.width = right - left;
}
