#pragma once

#include "ofMain.h"
#include "ofxBox2d.h"
#include "ofxUI.h"

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();
        void exit(); 
    
		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    ofxBox2d						box2d;	
    
        //anchors
    ofxBox2dCircle      startAnchor, startAnchorBot; 
    ofxBox2dCircle      endAnchor, endAnchorBot;
        
    //location & sizes
    ofVec2f             startLoc, endLoc, startLocBot, endLocBot; 
    int                 numHorz, numVertz;
    int                 incHorz, incVertz; 
    int                 lenHorz, lenVertz; 
    int                 circleSize; 
    
    //vectors
    vector<ofxBox2dCircle>  topCircles;
    vector<ofxBox2dCircle>  bottomCircles;
    vector<ofxBox2dCircle>  leftCircles;
    vector<ofxBox2dCircle>  rightCircles;
    
    vector<ofxBox2dJoint>   topJoints;
    vector<ofxBox2dJoint>   bottomJoints;
    vector<ofxBox2dJoint>   heightJoints;
    vector<ofxBox2dJoint>   leftJoints;
    vector<ofxBox2dJoint>   rightJoints;
    
    vector<ofxBox2dCircle>  waters; 
    
    //ofxUI
    ofxUICanvas *gui;   	
	void guiEvent(ofxUIEventArgs &e);
    
    //controls
    bool                    skeleton;
    int                     numNote; 
    
};
