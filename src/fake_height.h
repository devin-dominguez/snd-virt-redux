#pragma once

#include "ofMain.h"

class FakeHeight {
  public:
    static double getHeightAt(ofPoint position);
    static void setup(double worldWidth, double worldHeight);
    static void draw(double width, double height);

  private:
    static ofImage heightmap;
    static int width;
    static int height;
    static double worldWidth;
    static double worldHeight;
    static ofVec2f ratio;
};
