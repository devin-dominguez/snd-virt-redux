#include "ofApp.h"

#include "virt/virt.h"
#include "projector.h"

//--------------------------------------------------------------
void ofApp::setup(){
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
  ofBackground(32);
  Projector::startDraw();
  Virt::draw();
  Projector::endDraw();
}
