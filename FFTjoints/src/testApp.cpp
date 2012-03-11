#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);

	box2d.init();
	box2d.setGravity(0, 10);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	
	startAnchor.setup(box2d.getWorld(), 50, ofGetHeight()/2, 4);
    endAnchor.setup(box2d.getWorld(), ofGetWidth() - 50, ofGetHeight()/2, 4);
	
	// first we add just a few circles
	for (int i=0; i<35; i++) {
		ofxBox2dCircle circle;
		circle.setPhysics(30.0, 0.003, 10);//density, bounce, friction
		circle.setup(box2d.getWorld(), ofGetWidth()/2, 100+(i*20), 8);
        
		circles.push_back(circle);
	}


    
	// now connect each circle with a joint
	for (int i=0; i<circles.size(); i++) {
		
		ofxBox2dJoint joint;
        ofxBox2dJoint anchorJoint; 
		
		// if this is the last point connect to the end anchor.
        
        //if you're the first, connect to the anchor. 
        if (i == 0) {
            anchorJoint.setup(box2d.getWorld(), circles[i].body, startAnchor.body);
            joint.setup(box2d.getWorld(), circles[i].body, circles[i+1].body);

        }

        else if (i == circles.size()-1) {
            joint.setup(box2d.getWorld(),circles[circles.size()-1].body, endAnchor.body); 
        }
        
        else {
            joint.setup(box2d.getWorld(), circles[i].body, circles[i+1].body);
        }
        
        int jointLength =  1; 
        anchorJoint.setLength(jointLength);
        joint.setLength(jointLength);
        joint.setDamping(6);
        //joint.setFrequency(10);
        joints.push_back(anchorJoint);
		joints.push_back(joint);
	}
}

//--------------------------------------------------------------
void testApp::update() {
	box2d.update();	
    ofVec2f mouse(ofGetMouseX(), ofGetMouseY());
	//float minDis = ofGetMousePressed() ? 300 : 200;
    float minDis = 100; 
    
    /*
	for(int i=0; i<circles.size(); i++) {
		float dis = mouse.distance(circles[i].getPosition());
		if(dis < minDis) 
            circles[i].addAttractionPoint(mouse, 10);
	}
     */
    
    if (circles.size() > 0) {
        for (int i = 0; i<circles.size(); i++) {
            for(int j=0; j<attractors.size(); j++) {
                float dis = attractors[j].getPosition().distance(circles[i].getPosition());
                if(dis < minDis) 
                circles[i].addRepulsionForce(attractors[j].getPosition(), 20);
            }
        }
    }
}


//--------------------------------------------------------------
void testApp::draw() {
	
	ofSetHexColor(0xf2ab01);
	startAnchor.draw();
    endAnchor.draw(); 
	
	for(int i=0; i<circles.size(); i++) {
		ofFill();
		ofSetHexColor(0x01b1f2);
		circles[i].draw();
        circles[i].setRadius(5);
	}
	
	for(int i=0; i<joints.size(); i++) {
		ofSetHexColor(0x444342);
		joints[i].draw();
	}
    
    for (int i = 0; i<attractors.size(); i++) {
        attractors[i].draw(); 
    }
	
	string info = "";
	info += "Press [n] to add a new joint\n";
	info += "click and pull the chain around\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
	if(key == 'n') {
		
		// add a new circle
		ofxBox2dCircle circle;
		circle.setPhysics(3.0, 0.53, 0.1);
		circle.setup(box2d.getWorld(), circles.back().getPosition().x+ofRandom(-30, 30), circles.back().getPosition().y-30, 8);
		circles.push_back(circle);
	
		// get this cirlce and the prev cirlce
		int a = (int)circles.size()-2;
		int b = (int)circles.size()-1; 

		// now connect the new circle with a joint
		ofxBox2dJoint joint;
		joint.setup(box2d.getWorld(), circles[a].body, circles[b].body);
		joint.setLength(25);
		joints.push_back(joint);
	}
	
	if(key == 't') ofToggleFullscreen();
}

//--------------------------------------------------------------
void testApp::keyReleased(int key) {
}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ) {
	
}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button) {
	
    // add a new circle
    ofxBox2dCircle att;
    att.setup(box2d.getWorld(), x, y, 8);
    attractors.push_back(att);
    
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

