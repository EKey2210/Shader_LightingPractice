#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(60);
    ofBackground(0);
    ofEnableBlendMode(OF_BLENDMODE_ADD);
    
    setupTorus(80, 120, 360);
    this->shader.load("Vertex.vert","Fragment.frag");
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    this->cam.begin();
    this->shader.begin();
    ofMatrix4x4 modelMatrix;
    modelMatrix.translate(0, 0, 0);
//    modelMatrix.rotate(ofGetFrameNum()*0.02, 1.0, 0.5, 0.0);
    ofMatrix4x4 viewMatrix;
    viewMatrix = ofGetCurrentViewMatrix();
    
    ofMatrix4x4 projectionMatrix;
    projectionMatrix = cam.getProjectionMatrix();
    
    ofMatrix4x4 mvpMatrix;
    mvpMatrix = modelMatrix * viewMatrix * projectionMatrix;
    
    ofMatrix4x4 invMatrix;
    invMatrix = modelMatrix.getInverse();
    this->shader.setUniformMatrix4f("modelViewProjectionMatrix", mvpMatrix);
    this->shader.setUniformMatrix4f("invMatrix", invMatrix);
    this->shader.setUniform3f("lightDirection",vec3(-0.5,0.5,0.5));
    this->shader.setUniform3f("eyeDirection",vec3(20.0*cos(ofGetFrameNum()*0.04),20.0*sin(ofGetFrameNum()*0.04),20.0));
    this->shader.setUniform3f("ambientColor",vec4(0.1,0.1,0.1,1.0));
    this->mesh.draw();
//    this->mesh.drawWireframe();
//    this->mesh.drawVertices();
    this->shader.end();
    this->cam.end();
}

//--------------------------------------------------------------
void ofApp::setupTorus(int divideNum,float inRadius,float outRadius){
    for (float i = 0; i <= divideNum; i++) {
        float theta1 = (TWO_PI / divideNum) * i;
        for (float j = 0; j <= divideNum; j++) {
            ofColor color;
            color.setHsb(ofMap(j ,0, divideNum, 0, 255), 255, 255);
            this->mesh.addColor(color);
            float theta2 = (TWO_PI / divideNum) * j;
            float x = (outRadius + inRadius * cos(theta1)) * cos(theta2);
            float y = (outRadius + inRadius * cos(theta1)) * sin(theta2);
            float z = inRadius * sin(theta1);
            this->mesh.addVertex(vec3(x,y,z));
            float normalX = cos(theta1) * cos(theta2);
            float normalY = sin(theta1);
            float normalZ = cos(theta1) * sin(theta2);
            this->mesh.addNormal(vec3(normalX,normalY,normalZ));
        }
    }
    
    for(int i = 0; i < divideNum; i++) {
        for(int j = 0; j < divideNum; j++) {
            int count = (divideNum + 1) * j + i;
            this->mesh.addTriangle(count, count + divideNum + 2, count + 1);
            this->mesh.addTriangle(count, count + divideNum + 1, count + divideNum + 2);
        }
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
//    if(key == 's'){
//        ofSaveFrame("TorusFill.png");
//    }
}
