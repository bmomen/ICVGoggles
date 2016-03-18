#include "ofApp.h"

//--------------------------------------------------------------
vector<ofVideoGrabber*> cameras;
int camCounter;

void ofApp::setup(){
	ofToggleFullscreen();
	ofBackground(250, 250, 250);
	ofSetVerticalSync(true);
	oculusRift.baseCamera = &ofcam;
	oculusRift.setup();
	cam.listDevices();
	cam.setDeviceID(0); //right eye
	//cam2.listDevices();
	//cam2.setDeviceID(1); //left eye	
	cam.initGrabber(640,480);
	//cam2.initGrabber(640,480);
	


	//enable mouse;
    ofcam.begin();
    ofcam.end();
	//oculusRift.dismissSafetyWarning();
}

void ofApp::drawSceneLeftEye() {
	
	//cam2.draw(ofGetWidth() / 2, ofGetHeight(), ofGetWidth() / 2, -ofGetHeight());
}

void ofApp::drawSceneRightEye() {
	

		ofPushMatrix();
        
		ofDrawPlane(ofGetWidth() * .5, ofGetHeight()* .5, 100, 200);
        ofScale(1,1,1);
        ofRotate(90, 0, 0, -1);
            
            ofTranslate(1, 1, 100);
            cam.draw(0, 0, 640, 480);
            //ofTranslate(1, 1, 1);
        ofPopMatrix();
	
	//cam.draw(0, 0, ofGetWidth(),ofGetHeight());
	
}
//--------------------------------------------------------------
void ofApp::update(){
	cam.update();
	//cam2.update();    
    
    if(oculusRift.isSetup())
    {
        ofRectangle viewport = oculusRift.getOculusViewport();
        
    }
}

//--------------------------------------------------------------
void ofApp::draw(){
	if(oculusRift.isSetup())
    {

	ofSetColor(255);
        glEnable(GL_DEPTH_TEST);
        
        oculusRift.beginLeftEye();
        //drawSceneLeftEye(); //rename the methods for these
        oculusRift.endLeftEye();
        
        oculusRift.beginRightEye();
        drawSceneRightEye(); //rename the methods for these
        oculusRift.endRightEye();
        
        oculusRift.draw();
        
        glDisable(GL_DEPTH_TEST);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
    if( key == 'f' )
    {
        //gotta toggle full screen for it to be right
        ofToggleFullscreen();
    }
	if(key == 'r'){
        oculusRift.reset();
        
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
