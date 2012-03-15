#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup(){
    
    ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
    ofEnableSmoothing(); 
        
    //initial settings
    incHorz     = .2;    //spaces between joints
    numHorz     = 100;  //number of circles
    lenHorz     = 820;  //total length
    
    incVertz    = .2;   //spaces between joints
    numVertz    = 3;   //number of circles
    lenVertz    = 30;   //total length
    
    circleSize  = 3; 
    
    numNote = 1; 
    
    startLoc.set(50, ofGetHeight()/2);
    startLocBot.set(startLoc.x, startLoc.y + lenVertz); 
    endLoc.set (startLoc.x + lenHorz, startLoc.y); 
    endLocBot.set(endLoc.x, startLocBot.y);
    
    //box2d stuff----------------------------------------------------//
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
		topCircle.setup(box2d.getWorld(), startLoc.x + ((lenHorz/numHorz)* (i+1)), startLoc.y, 2); //move this by one point so it doesn't get knotted up
        topCircle.setFixedRotation(false);
		topCircles.push_back(topCircle);
        
        ofxBox2dCircle bottomCircle;
		bottomCircle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		bottomCircle.setup(box2d.getWorld(), startLocBot.x+((lenHorz/numHorz)* i), startLocBot.y, 2);
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
            connectJointTop.setup(box2d.getWorld(), topCircles[i].body, topCircles[i+1].body);
            
            bottomJoint.setup (box2d.getWorld(), startAnchorBot.body, bottomCircles[i].body); 
            connectJointBot.setup(box2d.getWorld(), bottomCircles[i].body, bottomCircles[i+1].body);
        }
        
        else if (i == topCircles.size()-1) {
            topJoint.setup(box2d.getWorld(), topCircles[i].body, endAnchor.body);
            
            bottomJoint.setup(box2d.getWorld(), bottomCircles[i].body, endAnchorBot.body);
        }
        
        else {
            topJoint.setup(box2d.getWorld(), topCircles[i].body, topCircles[i+1].body);
            
            bottomJoint.setup(box2d.getWorld(), bottomCircles[i].body, bottomCircles[i+1].body);
        }
        
        //the height joints will grow later depending on octave analysis
        heightJoint.setup(box2d.getWorld(), topCircles[i].body, bottomCircles[i].body);
        heightJoint.setLength(lenVertz);  
        
        connectJointTop.setLength(incHorz);
        topJoint.setLength(incHorz);
        topJoints.push_back(connectJointTop); 
        topJoints.push_back(topJoint); 
        
        connectJointBot.setLength(incHorz);
        bottomJoint.setLength(incHorz);
        bottomJoints.push_back(connectJointBot); 
        bottomJoints.push_back(bottomJoint); 
        
        heightJoints.push_back(heightJoint);
    }

    //create the left/ right circles
    for (int i=0; i<numVertz-1; i++) {
		ofxBox2dCircle leftCircle;
		leftCircle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		leftCircle.setup(box2d.getWorld(), startLoc.x, startLoc.y + ((lenVertz/numVertz) *i ), 2);
        leftCircle.setFixedRotation(false);
		leftCircles.push_back(leftCircle);
        
        ofxBox2dCircle rightCircle;
		rightCircle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		rightCircle.setup(box2d.getWorld(), endLoc.x, endLoc.y + ((lenVertz/numVertz) *i ), 2);
        rightCircle.setFixedRotation(false);
		rightCircles.push_back(rightCircle);
	}
    
    //create the left/ right joints
    for (int i = 0; i < leftCircles.size(); i++) {
        ofxBox2dJoint leftJoint; 
        ofxBox2dJoint rightJoint; 
        ofxBox2dJoint connectJointLeft; 
        ofxBox2dJoint connectJointRight; 
        
        if (i == 0 ) {
            leftJoint.setup (box2d.getWorld(), startAnchor.body, leftCircles[i].body); 
            connectJointLeft.setup(box2d.getWorld(), leftCircles[i].body, leftCircles[i+1].body);
            
            rightJoint.setup (box2d.getWorld(), endAnchor.body, rightCircles[i].body); 
            connectJointRight.setup(box2d.getWorld(), rightCircles[i].body, rightCircles[i+1].body);
        }
        
        else if (i == leftCircles.size()-1) {
            leftJoint.setup(box2d.getWorld(), leftCircles[i].body, startAnchorBot.body);
            
            rightJoint.setup(box2d.getWorld(), rightCircles[i].body, endAnchorBot.body);
        }
        
        else {
            leftJoint.setup(box2d.getWorld(), leftCircles[i].body, leftCircles[i+1].body);
            
            rightJoint.setup(box2d.getWorld(), rightCircles[i].body, rightCircles[i+1].body);
        }
                
        connectJointLeft.setLength(incVertz);
        leftJoint.setLength(incVertz);
        leftJoints.push_back(connectJointLeft); 
        leftJoints.push_back(leftJoint); 
        
        connectJointRight.setLength(incVertz);
        rightJoint.setLength(incVertz);
        rightJoints.push_back(connectJointRight); 
        rightJoints.push_back(rightJoint); 
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
    
    if (!skeleton) {
        
        for(int i=0; i<topCircles.size(); i++) {
            ofFill();
            ofSetHexColor(0x01b1f2);
            topCircles[i].draw();
            topCircles[i].setRadius(circleSize);
            bottomCircles[i].draw();
            bottomCircles[i].setRadius(circleSize);
        }
        
        ofSetColor(0); 
        for (int i = 0; i < topJoints.size(); i++) {
            topJoints[i].draw(); 
            bottomJoints[i].draw(); 
            //drawing these joints will cause errors. Don't know why 
            //heightJoints[i].draw(); 
        }
        
        for(int i=0; i<leftCircles.size(); i++) {
            ofFill();
            ofSetHexColor(0x01b1f2);
            leftCircles[i].draw();
            leftCircles[i].setRadius(circleSize);
            rightCircles[i].draw();
            rightCircles[i].setRadius(circleSize);
        }
        
        ofSetColor(0); 
        for (int i = 0; i < leftJoints.size(); i++) {
            leftJoints[i].draw(); 
            rightJoints[i].draw(); 
        }
    }
    
    if (skeleton) {
        ofFill();
        ofSetColor(79, 178, 245);
        ofBeginShape();
        
        for (int i = 0; i < topCircles.size(); i++) {
            ofVec2f pos; 
            ofVec2f firstPos; 

            if (i == 0) {
                firstPos = topCircles[i].getPosition(); 
                ofCurveVertex(firstPos.x, firstPos.y);
            }
            else if (i == topCircles.size()-1) {
                firstPos = topCircles[i].getPosition(); 
                pos = topCircles[i].getPosition();
                ofCurveVertex(pos.x, pos.y);
                ofCurveVertex(firstPos.x, firstPos.y);
            }
            else {   
            pos = topCircles[i].getPosition();
            ofCurveVertex(pos.x, pos.y);
            }
        }
                
        for (int i = bottomCircles.size()-1; i >= 0; i--) {
            ofVec2f pos; 
            pos = bottomCircles[i].getPosition();
            ofCurveVertex(pos.x, pos.y);
        }
        
        ofEndShape(true); 
        

    }

    for(int i=0; i<waters.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		waters[i].draw();
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

    if (key == ' ') {
        skeleton = !skeleton;
    }
    
    if (key == 'w') {
        float r = ofRandom(10, 20);		// a random radius 4px - 20px
        ofxBox2dCircle water;
        water.setPhysics(3.0, 1, 0.1);
        water.setup(box2d.getWorld(), bottomCircles[numNote].getPosition().x,bottomCircles[numNote].getPosition().y - ((bottomCircles[numNote].getPosition().y - topCircles[numNote].getPosition().y)/2), r);
        waters.push_back(water);
    }
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
    numNote ++; 
    heightJoints[numNote].setLength(ofGetHeight()/2 - ofGetMouseY());
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