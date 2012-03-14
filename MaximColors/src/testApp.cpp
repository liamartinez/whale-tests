/* This is an example of how to integrate maximilain into openFrameworks, 
 including using audio received for input and audio requested for output.
 
 
 You can copy and paste this and use it as a starting example.
 
 */

/* this doesn't work with fft enabled! */

#include "testApp.h"



//-------------------------------------------------------------
testApp::~testApp() {
	

	
}


//--------------------------------------------------------------
void testApp::setup(){
	/* some standard setup stuff*/
	
	ofEnableAlphaBlending();
	ofSetupScreen();
	ofBackground(0, 0, 0);
	ofSetVerticalSync(true);
	
	/* This is stuff you always need.*/
	
	sampleRate 			= 44100; /* Sampling Rate */
	initialBufferSize	= 512;	/* Buffer Size. you have to fill this buffer with sound*/
	
    buffer				= new float[initialBufferSize];
	memset(buffer, 0, initialBufferSize * sizeof(float));
	/* Now you can put anything you would normally put in maximilian's 'setup' method in here. */
	
	fftSize             = 1024;
	nAverages = 20;
	oct.setup(sampleRate, fftSize/2, nAverages);
	
	ofxMaxiSettings::setup(sampleRate, 2, initialBufferSize);
	
	ofSoundStreamSetup(2,0,this, sampleRate, initialBufferSize, 4);/* Call this last ! */
}

//--------------------------------------------------------------
void testApp::update(){
	
}

//--------------------------------------------------------------
void testApp::draw(){
    //octave analyser
    numCounted = 0;	
    float xinc = 900.0 / fftSize * 2.0;
    highest = 0; 
    float curAve = 0.0;
	ofSetColor(255, 0, 0,100);
	xinc = 900.0 / oct.nAverages;
	for(int i=0; i < oct.nAverages; i++) {
		float height = oct.averages[i] / 50.0 * 100;
        curAve = oct.averages[i];
        numCounted+=2;
		ofRect( (i*xinc),200 - height,2, height);
        if (height > highest) highest = height; 
        cout << highest << endl; 
	}
    
    highest = int(ofMap(highest, 35, 80, 1, 4));
    if (highest == 1) ofSetColor(100, 100, 100);
    if (highest == 2) ofSetColor(255, 100, 100);
    if (highest == 3) ofSetColor(100, 255, 100);
    if (highest == 4) ofSetColor(100, 100, 255);
    
    ofCircle(100, 100, 50);
	
}

//--------------------------------------------------------------
void testApp::audioRequested 	(float * output, int bufferSize, int nChannels){
	

	
}

//--------------------------------------------------------------
void testApp::audioReceived 	(float * input, int bufferSize, int nChannels){	
    
	
	if( initialBufferSize != bufferSize ){
		ofLog(OF_LOG_ERROR, "your buffer size was set to %i - but the stream needs a buffer size of %i", initialBufferSize, bufferSize);
		return;
	}	
	
	// samples are "interleaved"
	for (int i = 0; i < bufferSize; i++){
		buffer[i] = input[i];
        
        if (mfft.process(input[i])) {  
            mfft.magsToDB(); // calculate all the DBs  
            oct.calculate(mfft.magnitudesDB); // this will store the DBs of each octave range  
            
            
        }  
        
	}
    
    
	bufferCounter++; //lia:what is bufferCounter for?
	

	
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