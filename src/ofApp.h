#pragma once

#include "ofMain.h"
#include "ofSerial.h"
#include "ofMath.h"


class ofApp : public ofBaseApp{

	public:

		void serialEvent(ofSerial myPort);

		void setup();
		void update();
		void draw();

		ofSerial serial;
		ofImage image;
		
		
		float y = 0;
		float z = 0;
		float newFreq;
		int SERVOROW = 3;
		int SERVOCOL = 3;
		int NUMSERVOS = SERVOROW*SERVOCOL;

		// perlin modifiers: tweak these to get more dynamic 'contrast' sent to the Arduino
		// (visual in Processing will still look the same!)
		int PERLINMIN = 0;   //0
		int PERLINMAX = 255;	//255

								// simplex/perlin noise generator dimensions - the larger this is the more taxing on your computer
		int SWIDTH = 300;
		int SHEIGHT = 300;
		// for every increment SERVOPIXELs, set to next servo's position
		int SERVOPIXELS = (SWIDTH*SHEIGHT) / NUMSERVOS;

		int inByte;


};
