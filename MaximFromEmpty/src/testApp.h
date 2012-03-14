#pragma once

#include "ofMain.h"
#include "ofxMaxim.h"
#include <Accelerate/Accelerate.h>

/* this doesn't work if fft is enabled! */

class testApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed  (int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    void audioRequested 	(float * input, int bufferSize, int nChannels); /* output method */
    void audioReceived 	(float * input, int bufferSize, int nChannels); /* input method */
	
    int		initialBufferSize; /* buffer size */
    int		sampleRate;
	
	
    /* stick you maximilian stuff below */
    int		drawCounter, bufferCounter;
	float 	* buffer;
    
    float   scaledAve;
    float   smoothedAve;
	
	
	ofxMaxiFFTOctaveAnalyzer oct;
	int nAverages;
	float *ifftOutput;
	int ifftSize;
    
    /*
     ofxMaxiIFFT ifft;
     */
	ofxMaxiFFT mfft;
    
	int fftSize;
    
    
    vector <float>  aveHistory; 
    
    float   numCounted;
    int     highest; 

    
};
