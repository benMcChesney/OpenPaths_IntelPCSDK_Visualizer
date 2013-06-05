#pragma once

#include "ofMain.h"
#include "LocationPoint.h"
#include "ofxUI.h"
#include "ofxSimpleTimer.h"
#include "ofxTweenzor.h"

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


		
		void loadOpenPathsCSV( ) ; 
		void offsetCameraTarget ( int indexOffset ) ; 

		//ofEasyCam camera ; 
		ofEasyCam camera ; 

		float sceneScale ; 

		vector<LocationPoint> locations ;
		int highlightedLocation ; 

		ofxUIScrollableCanvas *gui;   	
		void guiEvent(ofxUIEventArgs &e);
		void setup_ofxUI() ;

		float sphereRadius ; 
		float cameraDistance ; 
		ofVec3f cameraTarget ; 

		ofxSimpleTimer timelineTimer ; 
		void timelineTimerComplete ( int &args ) ; 


		float dollySpeed ; 
		float minTargetDistance ; 


		ofImage worldMap ; 

		ofPoint locationOffset ; 



};
