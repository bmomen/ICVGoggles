#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	ofToggleFullscreen();
	oculusRift.setup();
	ofBackground(250, 250, 250);
	ofSetVerticalSync(true);
	oculusRift.baseCamera = &ofcam;
	
	cam.setDeviceID(0); //right eye

	cam1.setDeviceID(1); //left eye
	
	cam.listDevices();
	
	cam.initGrabber(640,480);
	cam1.initGrabber(640,480);
	
	//oculusRift.dismissSafetyWarning();
}

void ofApp::drawSceneLeftEye() {
	
	cam1.draw(ofGetWidth() / 2, ofGetHeight(), ofGetWidth() / 2, -ofGetHeight());
}

void ofApp::drawSceneRightEye() {

	cam.draw(0, ofGetHeight(), ofGetWidth() / 2, -ofGetHeight());
}
//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
	cam1.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
	oculusRift.beginLeftEye();
	drawSceneLeftEye();
	oculusRift.endLeftEye();

	oculusRift.beginRightEye();
	drawSceneRightEye();
	oculusRift.endRightEye();

	//pushes the render texture to the viewer
	oculusRift.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
    if( key == 'f' )
    {
        //gotta toggle full screen for it to be right
        ofToggleFullscreen();
    }
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
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
