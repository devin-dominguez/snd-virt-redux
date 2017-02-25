#include "pulsar.h"
#include "projector.h"
#include "pulse.h"

vector<Pulsar> Pulsar::collection;
void Pulsar::create(ofPoint position) {
  collection.push_back(Pulsar(position));
}

Pulsar::Pulsar(ofPoint position) : Entity(position) {
  size = 20.0;
  color = Entity::colors[0];
  type = PULSAR;

  phasor = 0.0;
  minFrequency = 1.0 / 12.0;
  maxFrequency = 1.0 / 4.0;

  criticalRange = 0.25;

  freqScale = ofVec2f(64, 79);
  ampScale = ofVec2f(2, 3);
  wobbleFreq = ofVec2f(0.0, 0.0);
  wobbleAmp = ofVec2f(0.0, 0.0);
  wobbleOffset = ofVec2f(0.0, 0.0);
}

void Pulsar::update(double dt) {
  switch(phase) {
    case NEW:
      fadeIn(dt);
      break;
    case ALIVE:
      action(dt);
      break;
    case DYING:
      fadeOut(dt);
      break;
    case DEAD:
      break;
  };
}

void Pulsar::action(double dt) {
  double height = 1.0; // TODO
  double frequency = ofLerp(minFrequency, maxFrequency, height);

  if (phasor < 1.0) {
    phasor += dt * frequency;
  } else {
    phasor -= 1.0;
    // TODO trigger action
    cout << "PULSE!" << endl;
  }

  wobble(dt);
}

void Pulsar::wobble(double dt) {
  if (phasor > criticalRange) {
    // normalize phasor outside of critical range
    double nPhase = (phasor - criticalRange) / (1.0 - criticalRange);
    // change curve and apply to freq and amp
    nPhase *= nPhase;
    wobbleFreq = nPhase * freqScale;
    wobbleAmp = nPhase * ampScale;

  } else {
    // linear fade when in critical range
    wobbleAmp -= ofVec2f(3.0 * dt, 3.0 * dt);
    wobbleAmp.x = fmax(0.0, wobbleAmp.x);
    wobbleAmp.y = fmax(0.0, wobbleAmp.y);
  }

	wobbleOffset.x = wobbleAmp.x * cos(phase * M_PI * 2 * wobbleFreq.x);
	wobbleOffset.y = wobbleAmp.y * sin(phase * M_PI * 2 * wobbleFreq.y);
}

void Pulsar::draw() {
  ofPoint screenPosition = Projector::getCoords(position);
  double screenSize = Projector::getScale(size);
  ofVec2f screenWobble = Projector::getCoords(wobbleOffset);

  ofPushMatrix();
    ofTranslate(screenPosition);
    ofPushStyle();
      ofEnableAlphaBlending();
      ofSetColor(color, 255.0 * fadeLevel);
      ofDrawCircle(screenWobble, screenSize);
      ofSetColor(Entity::colors[0], 255.0 * fadeLevel);
      ofDrawCircle(screenWobble, 0.75 * screenSize);
    ofPopStyle();
  ofPopMatrix();

}
