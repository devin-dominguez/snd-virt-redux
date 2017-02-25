#pragma once

#include "ofMain.h"
#include "entity.h"

class Pulsar : public Entity {
  public:
    ////////////////////////////
    // STATIC METHODS //////////
    ////////////////////////////
    static void create(ofPoint position);

    ////////////////////////////
    // STATIC DATA /////////////
    ////////////////////////////
    static vector<Pulsar> collection;

    ////////////////////////////
    // CONSTRUCTOR /////////////
    ////////////////////////////
    Pulsar(ofPoint position);

    ////////////////////////////
    // FRAME METHODS ///////////
    ////////////////////////////
    void update(double dt);
    void draw();

  private:
    void action(double dt);
    void wobble(double dt);

    ofFloatColor color;

    double timeElapsed;
    double minInterval;
    double maxInterval;
    double criticalRange;
    double phasor;
    double minFrequency;
    double maxFrequency;

    ofVec2f freqScale;
    ofVec2f ampScale;

    ofVec2f wobbleFreq;
    ofVec2f wobbleAmp;
    ofVec2f wobbleOffset;


};
