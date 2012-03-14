#pragma once
#include "ofMain.h"
#include "ofxBox2d.h"


// -------------------------------------------------

class testApp : public ofBaseApp {
	
public:
	
	void setup();
	void update();
	void draw();
	
	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void resized(int w, int h);
    void audioIn( float * input, int bufferSize, int nChannels );
    
	
	//box2d
	ofxBox2d						box2d;			  //	the box2d world
	ofxBox2dCircle					startAnchor, endAnchor, anAnchor;			  //	fixed anchor
	vector		<ofxBox2dCircle>	circles;		  //	default box2d circles
    vector      <ofxBox2dCircle>     endCircles;
	vector		<ofxBox2dJoint>		joints;			  //	joints
    vector      <ofxBox2dJoint>     endJoints;
	
    vector      <ofxBox2dCircle>     anchors; 
    
    vector      <ofxBox2dCircle>      notes; 
    vector      <ofxBox2dJoint>     noteJoints;
    vector      <ofxBox2dJoint>     lengthJoints;
    
    vector      <ofxBox2dCircle>    waters; 
    
    //ofxBox2dRevoluteJoint           newJoint;
    
    b2DistanceJointDef                  jointDef;
    
    vector      <ofxBox2dCircle> attractors; 
    
    int         numNote; 
};

