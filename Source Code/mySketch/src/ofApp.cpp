#include "ofApp.h"
#include "ofMath.h"
//--------------------------------------------------------------
int camCounter;
ofTexture mirrorTexture;
unsigned char * videoMirror;
int camWidth;
int camHeight; 
int type;
int severity;
void ofApp::setup(){
	
	//Setup openframeworks and the Oculus Rift
	//ofToggleFullscreen();
	ofBackground(250, 250, 250);
	ofSetVerticalSync(true);
	oculusRift.baseCamera = &ofcam;
	oculusRift.setup();
	oculusRift.dismissSafetyWarning();
	type=0;
	severity=0;
	
	//This code is for the right camera, due to USB power limitations, this will be included hopefully later.
	//cam2.listDevices();
	//cam2.setDeviceID(1); //left eye	
	//cam.initGrabber(640,480);
	//cam2.initGrabber(640,480);

	//Initialise left OVR Camera
	cam.listDevices();
	cam.setDeviceID(0);
	camWidth = 640;
	camHeight = 480;
	cam.setVerbose(true);
	cam.initGrabber(camWidth, camHeight);
	videoMirror = new unsigned char[camWidth*camHeight*3];
	mirrorTexture.allocate(camWidth, camHeight, GL_RGB); 
	

	//enable mouse;
    ofcam.begin();
    ofcam.end();
	
}

//--------------------------------------------------------------
//drawSceneRightEye()-------------------------------------------
//This method draws the mirrored OVRVision camera to the Oculus Rift.
//Oculus transformations are done automatically by the OculusRiftDK2 addon.
//Currently not completed due to two cameras not loading correctly: TODO

void ofApp::drawSceneRightEye() {
	
	//cam2.draw(ofGetWidth() / 2, ofGetHeight(), ofGetWidth() / 2, -ofGetHeight());
}

float mult[3][11][3][3] = {
  // protan simulation
{
{ { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } },
{ { 0.856167, 0.182038, -0.038205 }, { 0.029342, 0.955115, 0.015544 }, { -0.00288, -0.001563, 1.004443 } },
{ { 0.734766, 0.334872, -0.069637 }, { 0.05184, 0.919198, 0.028963 }, { -0.004928, -0.004209, 1.009137 } },
{ { 0.630323, 0.465641, -0.095964 }, { 0.069181, 0.890046, 0.040773 }, { -0.006308, -0.007724, 1.014032 } },
{ { 0.539009, 0.579343, -0.118352 }, { 0.082546, 0.866121, 0.051332 }, { -0.007136, -0.011959, 1.019095 } },
{ { 0.458064, 0.679578, -0.137642 }, { 0.092785, 0.846313, 0.060902 }, { -0.007494, -0.016807, 1.024301 } },
{ { 0.38545, 0.769005, -0.154455 }, { 0.100526, 0.829802, 0.069673 }, { -0.007442, -0.02219, 1.029632 } },
{ { 0.319627, 0.849633, -0.169261 }, { 0.106241, 0.815969, 0.07779 }, { -0.007025, -0.028051, 1.035076 } },
{ { 0.259411, 0.923008, -0.18242 }, { 0.110296, 0.80434, 0.085364 }, { -0.006276, -0.034346, 1.040622 } },
{ { 0.203876, 0.990338, -0.194214 }, { 0.112975, 0.794542, 0.092483 }, { -0.005222, -0.041043, 1.046265 } },
{ { 0.152286, 1.052583, -0.204868 }, { 0.114503, 0.786281, 0.099216 }, { -0.003882, -0.048116, 1.051998 } }
},

// deutan simulation
{
{ { 1.0, 0.0, 0.0}, { 0.0, 1.0, 0.0}, { 0.0, 0.0, 1.0} },
{ { 0.866435, 0.177704, -0.044139}, { 0.049567, 0.939063, 0.01137}, { -0.003453, 0.007233, 0.99622} },
{ { 0.760729, 0.319078, -0.079807}, { 0.090568, 0.889315, 0.020117}, { -0.006027, 0.013325, 0.992702} },
{ { 0.675425, 0.43385, -0.109275}, { 0.125303, 0.847755, 0.026942}, { -0.00795, 0.018572, 0.989378} },
{ { 0.605511, 0.52856, -0.134071}, { 0.155318, 0.812366, 0.032316}, { -0.009376, 0.023176, 0.9862} },
{ { 0.547494, 0.607765, -0.155259}, { 0.181692, 0.781742, 0.036566}, { -0.01041, 0.027275, 0.983136} },
{ { 0.498864, 0.674741, -0.173604}, { 0.205199, 0.754872, 0.039929}, { -0.011131, 0.030969, 0.980162} },
{ { 0.457771, 0.731899, -0.18967}, { 0.226409, 0.731012, 0.042579}, { -0.011595, 0.034333, 0.977261} },
{ { 0.422823, 0.781057, -0.203881}, { 0.245752, 0.709602, 0.044646}, { -0.011843, 0.037423, 0.974421} },
{ { 0.392952, 0.82361, -0.216562}, { 0.263559, 0.69021, 0.046232}, { -0.01191, 0.040281, 0.97163} },
{ { 0.367322, 0.860646, -0.227968}, { 0.280085, 0.672501, 0.047413}, { -0.01182, 0.04294, 0.968881} }
},

// tritan simulation
{
{ { 1.0, 0.0, 0.0 }, { 0.0, 1.0, 0.0 }, { 0.0, 0.0, 1.0 } },
{ { 0.92667, 0.092514, -0.019184 }, { 0.021191, 0.964503, 0.014306 }, { 0.008437, 0.054813, 0.93675 } },
{ { 0.89572, 0.13333, -0.02905 }, { 0.029997, 0.9454, 0.024603 }, { 0.013027, 0.104707, 0.882266 } },
{ { 0.905871, 0.127791, -0.033662 }, { 0.026856, 0.941251, 0.031893 }, { 0.01341, 0.148296, 0.838294 } },
{ { 0.948035, 0.08949, -0.037526 }, { 0.014364, 0.946792, 0.038844 }, { 0.010853, 0.193991, 0.795156 } },
{ { 1.017277, 0.027029, -0.044306 }, { -0.006113, 0.958479, 0.047634 }, { 0.006379, 0.248708, 0.744913 } },
{ { 1.104996, -0.046633, -0.058363 }, { -0.032137, 0.971635, 0.060503 }, { 0.001336, 0.317922, 0.680742 } },
{ { 1.193214, -0.109812, -0.083402 }, { -0.058496, 0.97941, 0.079086 }, { -0.002346, 0.403492, 0.598854 } },
{ { 1.257728, -0.139648, -0.118081 }, { -0.078003, 0.975409, 0.102594 }, { -0.003316, 0.501214, 0.502102 } },
{ { 1.278864, -0.125333, -0.153531 }, { -0.084748, 0.957674, 0.127074 }, { -0.000989, 0.601151, 0.399838 } },
{ { 1.255528, -0.076749, -0.178779 }, { -0.078411, 0.930809, 0.147602 }, { 0.004733, 0.691367, 0.3039 } }
}
};

//--------------------------------------------------------------
//drawSceneLeftEye()--------------------------------------------
//This method draws the mirrored OVRVision camera to the Oculus Rift.
//Oculus transformations are done automatically by the OculusRiftDK2 addon.

void ofApp::drawSceneLeftEye() {	

		ofPushMatrix();
        ofDrawPlane(-600, -400, 1200, 800);
        ofScale(1,1,1);
        ofRotate(0, 0, 0, 0);        
        ofTranslate(1, -1, -400);

		//ofSetColor(255, 255, 255);

		mirrorTexture.draw(-725, -543.75, 1450, 1087.5); 
        ofTranslate(1, 1, 1);
        ofPopMatrix();
		ofPushStyle();
		ofNoFill();
		oculusRift.reset();

		
}
//--------------------------------------------------------------
//update()------------------------------------------------------
//This method is called X times per second and updates the texture
//which the video is being rendered on.

void ofApp::update(){	
	ofBackground(0, 0, 0);
	cam.update(); 
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
            // swap pixels depending on Mode
			if(type==1) // MonoChromacy
			{
				// 0.21 R + 0.72 G + 0.07 B
            	videoMirror[pix1] = 0.21 * pixels[mir1] + 0.72 * pixels[mir2] + 0.07 * pixels[mir3];
            	videoMirror[pix2] = 0.21 * pixels[mir1] + 0.72 * pixels[mir2] + 0.07 * pixels[mir3];
            	videoMirror[pix3] = 0.21 * pixels[mir1] + 0.72 * pixels[mir2] + 0.07 * pixels[mir3];
			}			
			else //Protan/Deutan/Tritan modes
			{
				videoMirror[pix1] = static_cast<int>(pixels[mir1] * mult[type][severity][0][0]) + (pixels[mir2] * mult[type][severity][0][1]) + (pixels[mir3] * mult[type][severity][0][2]);
           		
				videoMirror[pix2] = static_cast<int>(pixels[mir1] * mult[type][severity][1][0]) + (pixels[mir2] * mult[type][severity][1][1]) + (pixels[mir3] * mult[type][severity][1][2]);
            	
				videoMirror[pix3] = static_cast<int>(pixels[mir1] * mult[type][severity][2][0]) + (pixels[mir2] * mult[type][severity][2][1]) + (pixels[mir3] * mult[type][severity][2][2]);
           		
				
			}
        }
    }
    mirrorTexture.loadData(videoMirror, camWidth, camHeight, GL_RGB);    
}

}

 




//--------------------------------------------------------------
//draw()--------------------------------------------------------
//This method checks if the Rift is setup. If it is, it starts 
//to render for the left and right eye.

void ofApp::draw(){
	if(oculusRift.isSetup())
    {
		ofSetColor(255);
        glEnable(GL_DEPTH_TEST);        
        oculusRift.beginLeftEye();
        drawSceneLeftEye();
        oculusRift.endLeftEye();        
        oculusRift.beginRightEye();
        drawSceneLeftEye();
        oculusRift.endRightEye();        
        oculusRift.draw();        
        glDisable(GL_DEPTH_TEST);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	
    if( key == 'f' ) //Toggle Fullscreen
    {
        ofToggleFullscreen();
    }
	if(key == 'r')//Reset OculusRift position
	{ 
        oculusRift.reset();        
    }
	if(key == 'p')//MonoChromacy Colour Mode
	{ 
       type=0;        
    }
	if(key == 'd')//Normal Colour Vision Mode
	{ 
       type=1;        
    }
	if(key == 't')//Normal Colour Vision Mode
	{ 
       type=2;        
    }
	if(key == '=')//Normal Colour Vision Mode
	{ 
       if(severity<10)
		   severity=severity+1;        
    }
	if(key == '-')//Normal Colour Vision Mode
	{ 
       if(severity>0)
		   severity=severity-1;        
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
