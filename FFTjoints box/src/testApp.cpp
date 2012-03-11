#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);

	box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	
	startAnchor.setup(box2d.getWorld(), 50, ofGetHeight()/2 - 200, 4);
    endAnchor.setup(box2d.getWorld(), ofGetWidth() - 50, ofGetHeight()/2, 4);
	
	// first we add just a few circles
	for (int i=0; i<15; i++) {
		ofxBox2dCircle circle;
		circle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		circle.setup(box2d.getWorld(), 50, ofGetHeight()/2 - 200 + i, 8);
        circle.setFixedRotation(true);
		circles.push_back(circle);
	}

    for (int i=0; i<1; i++) {
		ofxBox2dCircle note;
		note.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		note.setup(box2d.getWorld(), 50, ofGetHeight()/2 - 200 + i, 8);
        note.setFixedRotation(true);
		notes.push_back(note);
	}
    
    for (int i = 0; i < 50; i++) {
        ofxBox2dCircle anchor; 
        anchor.setup(box2d.getWorld(), 50+(i*10), ofGetHeight()/2, 2);
        anchors.push_back(anchor);
    }

    for (int i = 0; i < 15; i++ ) {
        ofxBox2dJoint sideJoint; 
        ofxBox2dJoint anchorJoint; 
        
        if ( i == 0) {
            sideJoint.setup(box2d.getWorld(), circles[i].body, circles[i+1].body);
            anchorJoint.setup(box2d.getWorld(), circles[i].body, startAnchor.body);
        }
        else if (i == circles.size()-1) {
            sideJoint.setup(box2d.getWorld(), circles[circles.size()-1].body, anchors[0].body);
        }
        else {
            sideJoint.setup(box2d.getWorld(), circles[i].body, circles[i+1].body);
        }
        
        int jointLength =  .1; 
        anchorJoint.setLength(jointLength);
        sideJoint.setLength(jointLength);
        /*
        sideJoint.setDamping(.5);
        sideJoint.setFrequency(3);
         */
        joints.push_back(anchorJoint);
        joints.push_back(sideJoint);
    }
    
    for (int i = 0; i < notes.size(); i++) {
        ofxBox2dJoint noteJoint; 
    if (i == 0 ) {
        noteJoint.setup (box2d.getWorld(), startAnchor.body, notes[i].body); 
        noteJoint.setLength(2);
        }
        noteJoints.push_back(noteJoint); 
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
    /*
    if (circles.size() > 0) {
        for (int i = 0; i<circles.size(); i++) {
            for(int j=0; j<attractors.size(); j++) {
                float dis = attractors[j].getPosition().distance(circles[i].getPosition());
                if(dis < minDis) 
                circles[i].addRepulsionForce(attractors[j].getPosition(), 20);
            }
        }
    }
     */
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
    
    for (int i = 0; i < anchors.size(); i++) {
        anchors[i].draw(); 
    }
    
    for (int i = 0; i < notes.size(); i++) {
        notes[i].draw(); 
        noteJoints[i].draw(); 
        
    }
	
    for (int i = 0; i < lengthJoints.size(); i++) {
        lengthJoints[i].draw();
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
		ofxBox2dCircle note;
		note.setPhysics(3.0, 0.53, 0.1);
		//note.setup(box2d.getWorld(), notes.back().getPosition().x+ofRandom(-30, 30), circles.back().getPosition().y-30, 2);
        note.setup(box2d.getWorld(), notes.back().getPosition().x + 20,  ofGetHeight()/2 - 200, 4);
		notes.push_back(note);
	
		// get this cirlce and the prev cirlce
		int a = (int)notes.size()-2;
		int b = (int)notes.size()-1; 

		// now connect the new circle with a joint
		ofxBox2dJoint noteJoint;
		noteJoint.setup(box2d.getWorld(), notes[a].body, notes[b].body);
		//noteJoint.setLength(ofGetMouseY() - ofGetHeight()/3);
        noteJoint.setLength(10);
		noteJoints.push_back(noteJoint);
        
        ofxBox2dJoint lenJoint;
        lenJoint.setup(box2d.getWorld(), notes[b].body, anchors[b].body);
        lengthJoints.push_back(lenJoint);
        
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
	
    /*
    // add a new circle
    ofxBox2dCircle att;
    att.setup(box2d.getWorld(), x, y, 8);
    attractors.push_back(att);
    */
}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button) {
}

//--------------------------------------------------------------
void testApp::resized(int w, int h){
}

