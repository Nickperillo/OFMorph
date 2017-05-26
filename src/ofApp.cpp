#include "ofApp.h"
//--------------------------------------------------------------

void ofApp::setup() {
	/*mesh.setMode(OF_PRIMITIVE_POINTS);*/
	glEnable(GL_POINT_SMOOTH);
	glPointSize(1);
		///size(50, 50);    set in main.cpp // this has to match SWIDTH and SHEIGHT!

	serial.listDevices();
	vector <ofSerialDeviceInfo> deviceList = serial.getDeviceList();
	int baud = 115200;
	serial.setup(0, baud);

	//string portName = serial.listD()[0]; //change the 0 to a 1 or 2 etc. to match your port
	//serial.setup(portName, 115200);

	//delay(1000);    // wait a while before we start – let the serial port settle down first!

}
void ofApp::serialEvent(ofSerial myPort) {

	//// get the byte:
	//inByte = serial.readBytes();
	//// print it:
	//serial.writeBytes(inByte);
	//if (inByte == 100) {
	//	newFreq = 0.04;
	//}
	//else if (inByte == 60) {
	//	newFreq = 0.005;
	//}
	//else if (inByte == 40) {
	//	newFreq = 0.002;
	//}
	//else if (inByte == 20) {
	//	newFreq = 0.08;
	//	//inByte    // 0-100
	//	//newFreq = MINFREQ + ((MAXFREQ-MINFREQ)*inByte/100);
	//}

}



//--------------------------------------------------------------
void ofApp::update(){
	image.grabScreen(0,0,SWIDTH, SHEIGHT);
	image.getPixels();
	
}

//--------------------------------------------------------------
void ofApp::draw(){

	int sections = 3;
	vector<ofPoint> sample_points;
	for(int x = 0; x < sections; x++) {
		for (int y = 0; y < sections; y++) {
			int w = ofGetWidth() / sections;
			int h = ofGetHeight() / sections;
			int mx = (int)ofMap(mouseX, 0, ofGetWidth(), 0, sections);
			int my = (int)ofMap(mouseY, 0, ofGetHeight(), 0, sections);
			if (mx == x && my == y) fill(255, 0, 0);
			else fill(0, 255, 0);
			sample_points.push_back(ofPoint(w*x, h*y));
			//rect(w*x, h*y, w, h);
		}
	}
	
	int x = 0;
	ofColor c;
	int res = ofGetWidth();
	ofVec2f freq = ofVec2f(ofMap(ofGetMouseX(), 0, ofGetWidth(), 0.0001, 0.05),
		ofMap(ofGetMouseY(), 0, ofGetHeight(), 0.0001, 0.05));
	// noise algorithm

	float brightness[9];
	int b_idx = 0;
	while (x < ofGetWidth()) { 
		float y = 0;
		while (y < ofGetHeight()) {
			//float b = 255 * (float) ofNoise(x / 80, y / 80, z); // b changes gradient. adjust /500 to change nose size
			ofVec2f pos = ofVec2f(ofMap(x, 0, res, 0, ofGetWidth()),y);
			ofVec2f noisePos = (pos * freq);

			float noiseVal = ofSignedNoise(noisePos.x,noisePos.y,z) * 255;
			float b = 255 * (float)ofSignedNoise(x / 80, y , z); // b changes gradient. adjust /500 to change nose size
															   
	       //stroke(0, 0, c); // strokePath??
			for (int i = 0; i < sample_points.size(); i++) {
				if (sample_points[i] == ofPoint(x, y)) {
					brightness[b_idx] = b;
					b_idx++;
				}
				int pixVal;
		
				unsigned char bright[9] = {b = ofMap(b,0,255,0,100)};
				serial.writeBytes(&bright[0], 9);

				//float bright = ofMap(b, 0, 255, 0, 100);


			c.setHsb(0, 0, noiseVal); //was fill
			//ofPoint(x, y); //point size
			//ofDrawEllipse(x, y,1,1);
			ofRect(x, y, 1, 1);
			//mesh.
			y = y+1;
			ofSetColor(c);
		}
		x = x+1;
	}
	//z += newFreq;

	z +=.08; //changes frequency
	
	
	//	pixValue = ofClamp(brightness, PERLINMIN, PERLINMAX); //was constrain in processing
	//	pixValue = ofMap(brig, PERLINMIN, PERLINMAX, 0, 100);    // we'll map to 0-100%: easier to translate this range via Serial to the Arduino


		//serial.writeBytes(bright[9], 9);
		//print(newFreq); //printf???
	}

	serial.writeByte(127);  // a char code of 127 is used as the 'terminating' character so the Arduino knows we're done with one line of data

	////delay(5);
	
}
//--------------------------------------------------------------
