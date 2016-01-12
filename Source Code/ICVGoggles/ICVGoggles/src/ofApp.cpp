#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	oculusRift.baseCamera = &cam; //attach to your camera
								  //opens the device, an Oculus must be plugged in 
								  //as it uses the params returned from the head set to configure 
								  //the resolution settings
	oculusRift.setup();

	//must run in full screen mode
	ofToggleFullScreen();
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	//move your camera wherever you'd like, this becomes the base
	//position of the view

	//now render using oculus flow
	oculusRift.beginLeftEye();
	drawScene();
	oculusRift.endLeftEye();

	oculusRift.beginRightEye();
	drawScene();
	oculusRift.endRightEye();

	//pushes the render texture to the viewer
	oculusRift.draw();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}


//--------------------------------------------------------------
void ofApp::drawScene() {

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
