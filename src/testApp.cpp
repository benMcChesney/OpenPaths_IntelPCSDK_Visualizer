#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{

	ofBackground( 0 , 0 , 0 ) ; 
	ofSetLogLevel( OF_LOG_VERBOSE ) ; 

	//Path to the comma delimited file
	string filePath = "openpaths_benDesigning.csv";
	
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
		
		float  ratio = (float) numLines / 10.0f ; 
		LocationPoint lp ; 
		lp.setup( locations.size() , ofToFloat( words[0] ) , ofToFloat( words[0] ) , ofColor::fromHsb( 255.0f * ratio , 255 , 255 ) ) ; 
		locations.push_back( lp ) ; 
		numLines++ ; 
	}

	camera.enableMouseInput() ; 
	setup_ofxUI( ) ; 

	ofSetVerticalSync( true ) ; 

	timelineTimer.setup( 10000 ) ; 
	timelineTimer.start( true ); 
	ofAddListener( timelineTimer.TIMER_COMPLETE , this , &testApp::timelineTimerComplete ) ; 

	highlightedLocation = 0 ;
}



//--------------------------------------------------------------
void testApp::update(){
	timelineTimer.update() ;


	camera.lookAt( cameraTarget ) ; 
	camera.setDistance( cameraDistance ) ; 

}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground( 0 , 0 , 0 ) ;

	camera.begin() ; 
		ofPushMatrix();
			//ofScale( worldScale , worldScale, worldScale ) ; 
			//translate so that the center of the screen is 0,0
			//ofTranslate(ofGetWidth()/2, ofGetHeight()/2);
			ofSetColor(255, 255, 255, 20);
	
			//float _scale = ( sin( ofGetElapsedTimef()) + 2.0f ) * 3.0f ;  
			//ofScale( _scale , _scale , _scale ) ; 
			float rotationAmount = 0.0f ; //( (float)mouseX / (float)ofGetWidth() ) * 360.0f ; 
			//cout << "rotationAmount : " << rotationAmount << endl ; 
			//draw a translucent wireframe sphere (ofNoFill() is on)
			ofPushMatrix();
				ofNoFill() ; 

				//add an extra spin at the rate of 1 degree per frame
				ofRotate(rotationAmount, 0, 1, 0);
				ofSphere(0, 0, 0, 300);
			ofPopMatrix();
	

		
			for ( int i = 0 ; i < locations.size() ; i++ ) 
			{
				locations[ i ].draw( ) ; 
			}

		ofPopMatrix() ; 
	camera.end() ; 
}


void testApp::setup_ofxUI( ) 
{
	gui = new ofxUIScrollableCanvas();
    gui->addLabel("GLOBE PARAMETERS");
    gui->addSpacer();
    gui->addFPSSlider("FPS");
    gui->addSpacer();
	gui->addSlider ( "CAMERA DISTANCE" ,10.f , 300.0f, cameraDistance ) ; 

    gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    gui->loadSettings("GUI/guiSettings.xml");
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 

	//gui->addSlider ( "GLOBE SIZE" , 300.0f , 10000.0f, globeSize ) ; 
	//gui->addSlider ( "WORLD SCALE" , 0.1f , 10.0f, worldScale ) ; 
	//camDistance
	if ( name == "CAM DISTANCE" ) cameraDistance =  ((ofxUISlider * )e.widget)->getScaledValue() ; 
}

void testApp::timelineTimerComplete ( int &args ) 
{
	highlightedLocation++ ; 
	if ( highlightedLocation > locations.size() - 1) 
		highlightedLocation = 0 ; 

	stringstream ss ; 
	ss << "TIMER COMPLETE !now looking at location : " << highlightedLocation << " of : " << ( locations.size() -1 ) << endl ; 
	ofLog( OF_LOG_VERBOSE , ss.str() ) ; 

	//camTarget


	camera.lookAt( locations[ highlightedLocation ].getGlobalPosition() ) ; 
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){
	switch ( key ) 
	{
		case 'o':
		case 'O':
			break; 
	}
}

void testApp::loadOpenPathsCSV( ) 
{
	ofFileDialogResult result = ofSystemLoadDialog( "Choose your CSV" , false ) ; 
	if ( result.bSuccess ) 
	{
		ofLog( OF_LOG_ERROR , "loading path from.. " + result.getPath() ) ; 

	}
	else
	{
		ofLog( OF_LOG_ERROR , "could not load CSV path" ) ; 
	}
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