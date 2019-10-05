#include "ofApp.h"

void ofApp::initSensor(){
	try {
		// Initialize the sensor
		sensor.initialize();
		// Set measurement timeout value
		sensor.setTimeout(200);
	} catch (const std::exception & error) {
		std::cerr << "Error initializing sensor with reason:" << std::endl << error.what() << std::endl;
		ofExit();
	}

	#ifdef LONG_RANGE
		try{
			// lower the return signal rate limit (default is 0.25 MCPS)
			sensor.setSignalRateLimit(0.1);
			// increase laser pulse periods (defaults are 14 and 10 PCLKs)
			sensor.setVcselPulsePeriod(VcselPeriodPreRange, 18);
			sensor.setVcselPulsePeriod(VcselPeriodFinalRange, 14);
		} catch (const std::exception & error){
			std::cerr << "Error enableing long range mode with reason: " << endl << error.what() << endl;
			// return 2;
			ofExit();
		}
	#endif

	#if defined HIGH_SPEED
		try {
			// reduce timing budget to 20 ms (default is about 33 ms)
			sensor.setMeasurementTimingBudget(20000);
		} catch (const std::exception & error){
			std::cerr << "Error enabling high speed mode with reason: " << endl << error.what() << endl;
			// return 3;
		}
	#elif defined HIGH_ACCURACY
		try {
			//increase timing budget to 200ms
			sensor.setMeasurementTimingBudget(200000);
		} catch (const std::exception & error){
			std::cerr << "Error enabling high accuracy mode with reason: " << endl << error.what() << endl;
			// return 3;
		}
	#endif

	// lastPollTimer = ofGetElapsedTimeMillis();
}

//--------------------------------------------------------------
void ofApp::setup(){
	ofSetFrameRate(30);
	ofSetVerticalSync(true);
	initSensor();

	ofBackground(0);
}

//--------------------------------------------------------------
void ofApp::update(){
	// if(ofGetElapsedTimeMillis() - lastPollTimer > 500){
		try {
			// Read the range. Note that it's a blocking call
			distance = sensor.readRangeSingleMillimeters();
		} catch (const std::exception & error) {
			std::cerr << "Error geating measurement with reason:" << std::endl << error.what() << std::endl;
			// You may want to bail out here, depending on your application - error means issues on I2C bus read/write.
			// return 3;
			distance = 8096;
		}

		// Check IO timeout and print range information
		if (sensor.timeoutOccurred())  	cout << "Reading" << " - timeout!" << endl;
		else 							cout << "Reading" << " - " << distance << endl;

		// lastPollTimer = ofGetElapsedTimeMillis();
	// }

	distancePercentage = ofMap(distance, minDistance, maxDistance, 0, 100, true);
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofPushMatrix();
	ofTranslate(20, 20);
	ofPushStyle();
	ofSetColor(ofColor::fromHex(0x00FFFF));
	ofFill();
	ofDrawRectangle(0, 0, ofMap(distancePercentage, 0, 100, 0, 200, true), 10);

	ofSetColor(ofColor::fromHex(0xFFFFFF));
	ofNoFill();
	ofDrawRectangle(0, 0, 200, 10);
	ofPopMatrix();
	ofPopStyle();
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
