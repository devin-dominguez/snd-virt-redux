#include "ofApp.h"

#include "virt/virt.h"
#include "projector.h"
#include "fake_height.h"

//--------------------------------------------------------------
void ofApp::setup(){
  FakeHeight::setup(640, 480);
  Virt::setup();
  ofSetWindowShape(ofGetScreenWidth(), ofGetScreenHeight());
  Projector::setWorldDimensions(640, 480);
  Projector::changePosition(ofPoint(120, 120));
}

//--------------------------------------------------------------
void ofApp::update(){
  double dt = ofGetLastFrameTime();
  Virt::update(dt);
}

//--------------------------------------------------------------
void ofApp::draw(){
  Projector::startDraw();
  FakeHeight::draw(640, 480);
  Virt::draw();
  Projector::endDraw();
}
