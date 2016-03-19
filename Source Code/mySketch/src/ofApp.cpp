#include "ofApp.h"

//--------------------------------------------------------------
vector<ofVideoGrabber*> cameras;
int camCounter;
ofTexture mirrorTexture;
unsigned char * videoMirror;
int camWidth;
int camHeight; 


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
	//cam.initGrabber(640,480);
	//cam2.initGrabber(640,480);
	camWidth = 640;
	camHeight = 480;
	cam.setVerbose(true);
	cam.initGrabber(camWidth, camHeight);
	videoMirror = new unsigned char[camWidth*camHeight*3];
	mirrorTexture.allocate(camWidth, camHeight, GL_RGB); 
	

	//enable mouse;
    ofcam.begin();
    ofcam.end();
	oculusRift.dismissSafetyWarning();
}

void ofApp::drawSceneLeftEye() {
	
	//cam2.draw(ofGetWidth() / 2, ofGetHeight(), ofGetWidth() / 2, -ofGetHeight());
}

void ofApp::drawSceneRightEye() {
	

		ofPushMatrix();
        
        ofScale(1,1,1);
        ofRotate(0, 0, 0, -1);        
        ofTranslate(1, 0, -300);

		ofSetColor(255, 255, 255);

		mirrorTexture.draw(-camWidth/2, -camHeight/2, camWidth, camHeight); 
        ofTranslate(1, 1, 1);
        ofPopMatrix();
	ofPushStyle();
    ofNoFill();
	
}
//--------------------------------------------------------------
void ofApp::update(){
	//cam.update();

	ofBackground(0, 0, 0);

if (cam.isFrameNew()) {
    unsigned char * pixels = cam.getPixels();
    for (int i = 0; i < camHeight; i++) {
        for (int j = 0; j < camWidth*3; j+=3) {
            // pixel number
            int pix1 = (i*camWidth*3) + j;
            int pix2 = (i*camWidth*3) + (j+1);
            int pix3 = (i*camWidth*3) + (j+2);
            // mirror pixel number
            int mir1 = (i*camWidth*3)+1 * (camWidth*3 - j-3);
            int mir2 = (i*camWidth*3)+1 * (camWidth*3 - j-2);
            int mir3 = (i*camWidth*3)+1 * (camWidth*3 - j-1);
            // swap pixels
            videoMirror[pix1] = pixels[mir1];
            videoMirror[pix2] = pixels[mir2];
            videoMirror[pix3] = pixels[mir3];    
        }
    }
    mirrorTexture.loadData(videoMirror, camWidth, camHeight, GL_RGB);    
} 
	cam.update();    
    
  
}

//--------------------------------------------------------------
void ofApp::draw(){
	if(oculusRift.isSetup())
    {

	ofSetColor(255);
        glEnable(GL_DEPTH_TEST);
        
        oculusRift.beginLeftEye();
        drawSceneRightEye();
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
