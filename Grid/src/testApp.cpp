#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
    ofEnableSmoothing(); 
        
    //initial settings
    numHorz     = 50; 
    incHorz     = 10; 
    lenHorz     = 10; 
    
    incVertz    = 10; 
    numVertz    = 10; 
    lenVertz    = .2; 
    
    
    circleSize  = 4; 
    
    startLoc.set(50, ofGetHeight()/2);
    startLocBot.set(startLoc.x, startLoc.y + (numVertz * incVertz)); 
    endLoc.set (startLoc.x + (numHorz * incHorz), startLoc.y); 
    endLocBot.set(endLoc.x, startLocBot.y);
    
    box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	
	startAnchor.setup(box2d.getWorld(), startLoc.x, startLoc.y, circleSize);
    endAnchor.setup(box2d.getWorld(), endLoc.x, endLoc.y, circleSize);
    startAnchorBot.setup(box2d.getWorld(), startLocBot.x, startLocBot.y, circleSize);
    endAnchorBot.setup(box2d.getWorld(), endLocBot.x, endLocBot.y, circleSize);

    //create the top/bot circles
    for (int i=0; i<numHorz-1; i++) {
		ofxBox2dCircle topCircle;
		topCircle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		topCircle.setup(box2d.getWorld(), startLoc.x+((i + 1)*incHorz), startLoc.y, 2);
        topCircle.setFixedRotation(false);
		topCircles.push_back(topCircle);
        
        ofxBox2dCircle bottomCircle;
		bottomCircle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		bottomCircle.setup(box2d.getWorld(), startLoc.x+((i + 1)*incHorz), startLoc.y, 2);
        bottomCircle.setFixedRotation(false);
		bottomCircles.push_back(bottomCircle);
	}
    
    //create the top/bot joints
    for (int i = 0; i < topCircles.size(); i++) {
        ofxBox2dJoint topJoint; 
        ofxBox2dJoint heightJoint;
        ofxBox2dJoint bottomJoint; 
        ofxBox2dJoint connectJointTop; 
        ofxBox2dJoint connectJointBot; 
        
        if (i == 0 ) {
            topJoint.setup (box2d.getWorld(), startAnchor.body, topCircles[i].body); 
            topJoint.setLength(lenVertz);
            connectJointTop.setup(box2d.getWorld(), topCircles[i].body, topCircles[i+1].body);
        }
        
        
        else if (i == topCircles.size() -1) {
            topJoint.setup(box2d.getWorld(), topCircles[i].body, endAnchor.body);
            topJoint.setLength(lenVertz);
            heightJoint.setup(box2d.getWorld(), topCircles[i-1].body, bottomCircles[i].body);
            heightJoint.setLength(50); 
        }
        
        else {
            
            topJoint.setup(box2d.getWorld(), topCircles[i].body, topCircles[i+1].body);
            topJoint.setLength(lenVertz);
            heightJoint.setup(box2d.getWorld(), topCircles[i-1].body, bottomCircles[i].body);
            heightJoint.setLength(50);   
        }
        
        topJoints.push_back(connectJointTop); 
        topJoints.push_back(topJoint); 
        heightJoints.push_back(heightJoint);
    }

    
}

//--------------------------------------------------------------
void testApp::update(){
    
	box2d.update();	
    
}

//--------------------------------------------------------------
void testApp::draw(){

    ofSetColor(0);
    startAnchor.draw();
    startAnchorBot.draw();
    endAnchor.draw();
    endAnchorBot.draw(); 
    
    for(int i=0; i<topCircles.size(); i++) {
		ofFill();
		ofSetHexColor(0x01b1f2);
		topCircles[i].draw();
        topCircles[i].setRadius(1);
        ofSetHexColor(0x01b1f2);
	}
    
    ofSetColor(0); 
    for (int i = 0; i < topJoints.size(); i++) {
        topJoints[i].draw();         
    }
    
}
//--------------------------------------------------------------
void testApp::exit()
{

}

//--------------------------------------------------------------
void testApp::guiEvent(ofxUIEventArgs &e)
{


}
//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void testApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void testApp::dragEvent(ofDragInfo dragInfo){ 

}