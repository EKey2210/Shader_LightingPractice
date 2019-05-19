#pragma once

#include "ofMain.h"

using namespace glm;

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();

    void setupTorus(int divideNum,float inRadius,float outRadius);
    
    void keyPressed(int key);
private:
    ofEasyCam cam;
    ofVboMesh mesh;
    ofShader shader;
};
