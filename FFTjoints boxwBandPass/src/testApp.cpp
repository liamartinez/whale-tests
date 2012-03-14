#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
	
	ofSetVerticalSync(true);
	ofBackgroundHex(0xfdefc2);
	ofSetLogLevel(OF_LOG_NOTICE);
    
    //audio
    initialBufferSize	= 128;
    ofSoundStreamSetup(0,1,this,44100,128,4);
    //added buffer
    buffer = new float[128];
    memset(buffer, 0, 128 * sizeof(float));
    
    amplitude = new float[88];
    
    BP = new float[128];
    BPin1 = new float[89];
    BPin2 = new float[89];
    BPout1 = new float[89];
    BPout2 = new float[89];
    bandw = 0.01;
    
    //box2d
	box2d.init();
	box2d.setGravity(0, 2);
	box2d.setFPS(30.0);
	box2d.registerGrabbing();
	
	startAnchor.setup(box2d.getWorld(), 50, ofGetHeight()/2 - 50, 4);
    endAnchor.setup(box2d.getWorld(), ofGetWidth() - 50, ofGetHeight()/2, 4);
	
    numNote = 0; 
    
	// side circles
	for (int i=0; i<3; i++) {
		ofxBox2dCircle circle;
		circle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		circle.setup(box2d.getWorld(), 50, ofGetHeight()/2 - 50 + i, 8);
        circle.setFixedRotation(true);
		circles.push_back(circle);
	}
    
    // end circles
	for (int i=0; i<3; i++) {
		ofxBox2dCircle endCircle;
		endCircle.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		endCircle.setup(box2d.getWorld(), 550, ofGetHeight()/2 - 50 + i, 8);
        endCircle.setFixedRotation(true);
		endCircles.push_back(endCircle);
	}
    
    // note circles
    for (int i=0; i<50; i++) {
		ofxBox2dCircle note;
		note.setPhysics(30.0, 0.003, 5);//density, bounce, friction
		note.setup(box2d.getWorld(), 50+((i+1)*10), ofGetHeight()/2 - 50 + i, 8);
        note.setFixedRotation(true);
		notes.push_back(note);
	}
    
    //bottom anchors
    for (int i = 0; i < 50; i++) {
        ofxBox2dCircle anchor; 
        anchor.setup(box2d.getWorld(), 50+(i*10), ofGetHeight()/2, 2);
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
    if (i == 0 ) {
        noteJoint.setup (box2d.getWorld(), startAnchor.body, notes[i].body); 
        noteJoint.setLength(10);
        }
    else {
        noteJoint.setup(box2d.getWorld(), notes[i].body, notes[i-1].body);
        noteJoint.setLength(10);
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
	
    //audio
    ofSetColor(255,255,255);
    for(int i = 0; i < 89; i++) ofCircle(i*10,50+ amplitude[i], 4);
    
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
        //lengthJoints[i].draw();
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
	
    
    numNote ++; 
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
    
    
	if( initialBufferSize != bufferSize ){
		ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
		return;
	}	
	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		buffer[i] = input[i];
	}
	bufferCounter++;
    
    
    float notefreq[88] =
    {
        27.50f,    29.14f,    30.87f,
        32.70f,   34.65f,   36.71f,   38.89f,    41.20f,    43.65f,    46.25f,    49.00f,    51.91f,    55.00f,    58.27f,    61.74f,
        65.41f,   69.30f,   73.42f,   77.78f,    82.41f,    87.31f,    92.50f,    98.00f,   103.83f,   110.00f,   116.54f,   123.47f,
        130.81f,  138.59f,  146.83f,  155.56f,   164.81f,   174.61f,   185.00f,   196.00f,   207.65f,   220.00f,   233.08f,   246.94f,
        261.63f,  277.18f,  293.66f,  311.13f,   329.63f,   349.23f,   369.99f,   392.00f,   415.30f,   440.00f,   466.16f,   493.88f,
        523.25f,  554.37f,  587.33f,  622.25f,   659.26f,   698.46f,   739.99f,   783.99f,   830.61f,   880.00f,   932.33f,   987.77f,
        1046.50f, 1108.73f, 1174.66f, 1244.51f,  1318.51f,  1396.91f,  1479.98f,  1567.98f,  1661.22f,  1760.00f,  1864.66f,  1975.53f,
        2093.00f, 2217.46f, 2349.32f, 2489.02f,  2637.02f,  2793.83f,  2959.96f,  3135.96f,  3322.44f,  3520.00f,  3729.31f,  3951.07f,
        4186.01f
    };
    
    for(int i = 0; i < 89;i++){
        amplitude[i] *= 0.95;
        //BandPass(left,BP,bandw,notefreq[i],i);
        BandPass(buffer,BP,bandw,notefreq[i],i);
        for(int j = 0; j < 128; j++){
            if(BP[j] > 0.0)
                amplitude[i] += BP[j];
            if(BP[i] < 0.0)
                amplitude[i] += BP[j]*-1;
            BP[j] = 0.0;
        }
    }
}

//--------------------------------------------------------------
void testApp::BandPass(float *in, float * out,float width, float freq, int note){
    float BW = width;
    float c,a0,a1,a2,a3,b0,b1,b2,w0,f,alpha;
    f = freq;
    w0 = 2*PI*f/44100;
    alpha= sin(w0)*sinh( log(2)/2 * BW * w0/sin(w0) );
    
    b0 =   alpha;
    b1 =   0;
    b2 =  -alpha;
    a0 =   1 + alpha;
    a1 =  -2*cos(w0);
    a2 =   1 - alpha;
    
    for(int i = 0; i < 128; i++){
        
        out[i] =((b0/a0)*in[i] + (b1/a0)*BPin1[note] + (b2/a0)*BPin2[note] - (a1/a0)*BPout1[note] - (a2/a0)*BPout2[note]);
        
        
        BPin2[note] = BPin1[note];
        BPin1[note] = in[i];
        BPout2[note] = BPout1[note];
        BPout1[note] = out[i];
        
    }
}
