#pragma once

#include "ofMain.h"
// #include "I2Cdev.hpp"
// #include "VL53L0X_defines.hpp"
#include "VL53L0X.hpp"

// #define LONG_RANGE
// #define HIGH_SPEED
// #define HIGH_ACCURACY

// #ifdef HIGH_SPEED
// 	#ifdef HIGH_ACCURACY
// 		#err HIGHSPEED and HIGH_ACCURACY cannot be both enabled at once!
// 	#endif
// #endif

class ofApp : public ofBaseApp{
	public:
		void initSensor();
		void setup();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

	VL53L0X sensor;
	uint16_t distance;
	uint64_t lastPollTimer;

	uint16_t minDistance = 55;
	uint16_t maxDistance = 1000;
	uint16_t distancePercentage;
};
