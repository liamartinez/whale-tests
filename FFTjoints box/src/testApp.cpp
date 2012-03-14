#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
    
    
    //box2d
    
    //variables
    numNote = 0; 
    int numHorz = 100; 
    int numVertz = 2; 
    int increment = 8; 
    int startLoc = 50; 
    int endLoc = numHorz * increment + startLoc;
    
    
	box2d.init();
	box2d.setGravity(0, 0);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	
	startAnchor.setup(box2d.getWorld(), startLoc, ofGetHeight()/2 - 50, 4);
    endAnchor.setup(box2d.getWorld(), endLoc, ofGetHeight()/2 - 50, 4);

	// side circles
	for (int i=0; i<numVertz; i++) {
		ofxBox2dCircle circle;
        ofxBox2dCircle endCircle;
        
		circle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
        circle.setFixedRotation(true);
        circle.setup(box2d.getWorld(), 50, ofGetHeight()/2 - 50 + i, 8);
		circles.push_back(circle);
                
		endCircle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		endCircle.setup(box2d.getWorld(), 550, ofGetHeight()/2 - 50 + i, 8);
        endCircle.setFixedRotation(true);
		endCircles.push_back(endCircle);

	}
        
    // note circles
    for (int i=0; i<numHorz-1; i++) {
		ofxBox2dCircle note;
		note.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		note.setup(box2d.getWorld(), 50+((i+1)*increment), ofGetHeight()/2 - 50 + i, 2);
        note.setFixedRotation(true);
		notes.push_back(note);
	}
    
    //bottom anchors
    for (int i = 0; i < numHorz; i++) {
        ofxBox2dCircle anchor; 
        anchor.setup(box2d.getWorld(), 50+(i*increment), ofGetHeight()/2, 2);
        anchors.push_back(anchor);
    }
    
    //side joints
    for (int i = 0; i < 3; i++ ) {
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

        joints.push_back(anchorJoint);
        joints.push_back(sideJoint);
    }
    
    //end joints
    for (int i = 0; i < 3; i++ ) {
        ofxBox2dJoint endJoint; 
        ofxBox2dJoint endAnchorJoint; 
        
        if ( i == 0) {
            endJoint.setup(box2d.getWorld(), endCircles[i].body, endCircles[i+1].body);
            endAnchorJoint.setup(box2d.getWorld(), endCircles[i].body, notes[notes.size()-1].body);
        }
        else if (i == circles.size()-1) {
            endJoint.setup(box2d.getWorld(), endCircles[endCircles.size()-1].body, anchors[anchors.size()-1].body);
        }
        else {
            endJoint.setup(box2d.getWorld(), endCircles[i].body, endCircles[i+1].body);
        }
        
        int jointLength =  .1; 
        endAnchorJoint.setLength(jointLength);
        endJoint.setLength(jointLength);
        
        endJoints.push_back(endAnchorJoint);
        endJoints.push_back(endJoint);
    }
    
    //noteJoints, lenJoints
    for (int i = 0; i < notes.size(); i++) {
        ofxBox2dJoint noteJoint; 
        ofxBox2dJoint lenJoint;
        ofxBox2dJoint connectJoint; 
        
        if (i == 0 ) {
            noteJoint.setup (box2d.getWorld(), startAnchor.body, notes[i].body); 
            noteJoint.setLength(increment);
            connectJoint.setup(box2d.getWorld(), notes[i].body, notes[i+1].body);
        }
        
        
         else if (i == notes.size() -1) {
             noteJoint.setup(box2d.getWorld(), notes[i].body, endAnchor.body);
             noteJoint.setLength(increment);
             lenJoint.setup(box2d.getWorld(), notes[i-1].body, anchors[i].body);
             lenJoint.setLength(50); 
         }
         
         
        else {

            noteJoint.setup(box2d.getWorld(), notes[i].body, notes[i+1].body);
            noteJoint.setLength(increment);
            lenJoint.setup(box2d.getWorld(), notes[i-1].body, anchors[i].body);
            lenJoint.setLength(50);   
        }
        

        noteJoints.push_back(noteJoint); 
        lengthJoints.push_back(lenJoint);
    }
    
    


    
}

//--------------------------------------------------------------
void testApp::update() {
	box2d.update();	

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
        ofSetHexColor(0x01b1f2);
        endCircles[i].draw(); 
        endCircles[i].setRadius(5);
	}
	
	for(int i=0; i<joints.size(); i++) {
		ofSetHexColor(0x444342);
		joints[i].draw();
        endJoints[i].draw(); 
	}
    
    for (int i = 0; i < anchors.size(); i++) {
        anchors[i].draw(); 
    }
    
    for (int i = 0; i < notes.size(); i++) {
        notes[i].setRadius(3);
        notes[i].draw(); 
        noteJoints[i].draw();         
    }
	
    for (int i = 0; i < lengthJoints.size(); i++) {
        lengthJoints[i].draw();
    }
    
    for(int i=0; i<waters.size(); i++) {
		ofFill();
		ofSetHexColor(0xf6c738);
		waters[i].draw();
	}
    
    lengthJoints[numNote].setLength(ofGetHeight()/2 - ofGetMouseY());
    
	string info = "";
	info += "Press [n] to add a new joint\n";
	info += "click and pull the chain around\n";
	info += "FPS: "+ofToString(ofGetFrameRate(), 1)+"\n";
	ofSetHexColor(0x444342);
	ofDrawBitmapString(info, 30, 30);
}

//--------------------------------------------------------------
void testApp::keyPressed(int key) {
	
    /*
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
        lenJoint.setup(box2d.getWorld(), notes[b].body, anchors[b+1].body);
        lengthJoints.push_back(lenJoint);
        
	}
	*/
     
	if(key == 't') ofToggleFullscreen();
    if(key == 'r') {
        numNote --; 
        lengthJoints[numNote].setLength(200);
    }
    if (key == 'w') {
        float r = ofRandom(10, 20);		// a random radius 4px - 20px
        ofxBox2dCircle water;
        water.setPhysics(3.0, 1, 0.1);
        water.setup(box2d.getWorld(), anchors[numNote].getPosition().x,anchors[numNote].getPosition().y - 10, r);
        waters.push_back(water);
    }

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
	
    
    numNote += 3; 
    lengthJoints[numNote].setLength(ofGetHeight()/2 - ofGetMouseY());
     


    
    
    
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

//--------------------------------------------------------------
void testApp::audioIn(float * input, int bufferSize, int nChannels){
    

}

