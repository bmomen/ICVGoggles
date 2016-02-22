#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofBackground(250, 250, 250);
	ofSetVerticalSync(true);
	centerX = ofGetWidth() / 2;
	centerY = ofGetHeight() / 2;
	centerZ = 0;
	cam.setDeviceID(0);
	
	cam1.setDeviceID(1);
	cam.setup(320, 240);
	cam1.setup(320, 240);
	cam.listDevices();
	
}

//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
	cam1.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	cam.draw(0, 500,640,-480);
	cam1.draw(640,500,640,-480);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
