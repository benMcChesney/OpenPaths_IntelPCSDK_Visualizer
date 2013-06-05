#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{

	ofBackground( 0 , 0 , 0 ) ; 

	//Path to the comma delimited file
	string filePath = "openpaths.csv";
	
	//Load file placed in bin/data
	ofFile file(filePath);
	
	if(!file.exists()){
		ofLogError("The file " + filePath + " is missing");
	}
	
	ofSetFrameRate(30);
	ofEnableAlphaBlending();
	ofNoFill();

	ofBuffer buffer(file);

	int numLines = 0 ; 
	while ( numLines < 10 ) 
	{
		//lat ,	lon ,	alt ,	date, device ,	os ,	version
		string line = buffer.getNextLine() ; 
		vector<string> words = ofSplitString( line , "," ) ;

		for ( int i = 0 ; i < words.size() ; i++ ) 
		{
		//	cout << " word : " << words[i] << endl ; 
		}
		
		LocationPoint lp ; 
		lp.setup( locations.size() , ofToFloat( words[0] ) , ofToFloat( words[0] ) ) ; 
		locations.push_back( lp ) ; 
		numLines++ ; 
	}


}

//--------------------------------------------------------------
void testApp::update(){

}

//--------------------------------------------------------------
void testApp::draw()
{

	ofPushMatrix();
	
		//translate so that the center of the screen is 0,0
		ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
		ofSetColor(255, 255, 255, 20);
	
		//float _scale = ( sin( ofGetElapsedTimef()) + 2.0f ) * 3.0f ;  
		//ofScale( _scale , _scale , _scale ) ; 
		float rotationAmount = ( (float)mouseX / (float)ofGetWidth() ) * 360.0f ; 
		cout << "rotationAmount : " << rotationAmount << endl ; 
		//draw a translucent wireframe sphere (ofNoFill() is on)
		ofPushMatrix();
			//add an extra spin at the rate of 1 degree per frame
			ofRotate(rotationAmount, 0, 1, 0);
			ofSphere(0, 0, 0, 300);
		ofPopMatrix();
	

		
		for ( int i = 0 ; i < locations.size() ; i++ ) 
		{
			locations[ i ].draw( rotationAmount ) ; 
		}

	ofPopMatrix() ; 
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