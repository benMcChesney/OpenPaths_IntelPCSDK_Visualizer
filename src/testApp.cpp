#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup()
{
	//Lat long
	//-180 to 180
	// long
	//-90 - 90
	//Inital settings


	ofBackground( 0 , 0 , 0 ) ; 
	ofSetLogLevel( OF_LOG_VERBOSE ) ; 
	
	Tweenzor::init() ; 

	worldMap.loadImage( "latitude_longitude_world.jpg" ) ; 

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

	//Skip the first line...
	buffer.getNextLine() ; 

	int numLines = 0 ; 
	//float maxLines = 150.0f ; 
	while ( !buffer.isLastLine() ) 
	{
		//lat ,	lon ,	alt ,	date, device ,	os ,	version
		string line = buffer.getNextLine() ; 
		vector<string> words = ofSplitString( line , "," ) ;

		for ( int i = 0 ; i < words.size() ; i++ ) 
		{
		//	cout << " word : " << words[i] << endl ; 
		}
		
		float  ratio = (float) numLines * 10.0f ;
		int hue = (int) ratio % 255 ; 
		LocationPoint lp ; 
		lp.setup( locations.size() , ofToFloat( words[0] ) , ofToFloat( words[0] ) , ofColor::fromHsb( hue , 255 , 255 ) , &locationOffset ) ; 
		locations.push_back( lp ) ; 
		numLines++ ; 
	}
	
	camera.setNearClip( 0.0f ) ; 
	camera.setFarClip( 10000000.0f ) ; 
	//camera.enableMouseInput() ; 
	setup_ofxUI( ) ; 

	ofSetVerticalSync( true ) ; 

	timelineTimer.setup( 1000 ) ; 
	timelineTimer.start( true ); 
	ofAddListener( timelineTimer.TIMER_COMPLETE , this , &testApp::timelineTimerComplete ) ; 

	highlightedLocation = 0 ;
	offsetCameraTarget( 1 ) ; 
	camera.setPosition( locations[0].getGlobalPosition() ) ; 

}

//--------------------------------------------------------------
void testApp::update(){

	Tweenzor::update( ofGetElapsedTimeMillis() ) ; 
	timelineTimer.update() ;

	//camera.lookAt( cameraTarget ) ; 
	//camera.setDistance( cameraDistance ) ; 

	//camera.setAutoDistance( false ) ; 
	ofVec3f camPosition = cameraTarget; 
	//camera.move( 0 , 0, 10 ) ; 
	//camPosition.z -= cameraDistance ; 
	//camera.setPosition( camPosition ) ;
	camera.lookAt( cameraTarget ) ; 
	cameraDistance = minTargetDistance ; 
	//camera.setDistance( cameraDistance ) ; 
	
	float targetDistance = camera.getPosition().distance( cameraTarget ) ;  

	if ( targetDistance >= minTargetDistance ) 
	{
		float dollyAmount = abs(dollySpeed) ; 
		if ( dollyAmount > minTargetDistance )
			dollyAmount = -minTargetDistance ; //dollyAmount - minTargetDistance ; 
		camera.dolly( dollyAmount ) ; 
	}


	
}

//--------------------------------------------------------------
void testApp::draw()
{
	ofBackground( 0 , 0 , 0 ) ;

	ofSetColor( 255 , 255 , 255 ) ; 
	worldMap.draw( 0 , 0 ) ; 
	//camera.begin() ; 
		ofPushMatrix();

		//ofScale( sceneScale , sceneScale, sceneScale ) ; 
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
				ofSphere(0, 0, 0, sphereRadius );
			ofPopMatrix();
	

			//ofPath path ; 
			//ofPolyline line; 
			for ( int i = 0 ; i < locations.size() ; i++ ) 
			{
				locations[ i ].draw( ) ; 
				//line.addVertex( locations[i].getGlobalPosition() ) ; 
				//path.lineTo( locations[i].getGlobalPosition() ) ; 
				//path.curveTo( locations[i].getGlobalPosition() ) ; 
			}

			//line.close() ; 
			//path.setFilled( false ) ; 
			//path.setFillColor( ofColor( 255 , 0 , 0 ) ) ;
			
			//path.setStrokeColor( ofColor( 255 , 255 , 255 ) ) ; 
			//path.setStrokeWidth( 4 ) ; 
			//path.draw() ; 
			//line.draw() ; 


			locations[ highlightedLocation ].drawSelected() ; 

		ofPopMatrix() ; 
	//camera.end() ; 
}


void testApp::setup_ofxUI( ) 
{
	gui = new ofxUIScrollableCanvas();
    gui->addLabel("GLOBE PARAMETERS");
    gui->addSpacer();
    gui->addFPSSlider("FPS");
    gui->addSpacer();
	 
	gui->addSlider ( "SPHERE RADIUS" , 100.0f , 1000000.0f, sphereRadius ) ; 
	gui->addSlider ( "DOLLY SPEED" , -1.0f , -500.0f , sphereRadius ) ; 
	gui->addSlider ( "MIN TARGET DISTANCE" , 1.0f , 500.0f, sphereRadius ) ; 
	gui->addSlider ( "LATITUDE OFFSET" , -180.0f , 180.0f , locationOffset.x ) ; 
	gui->addSlider ( "LONGITUDE OFFSET" , -90.0f , 90.0f , locationOffset.y ) ; 
	/*

	if ( name == "DOLLY SPEED" ) dollySpeed =  ((ofxUISlider * )e.widget)->getScaledValue() ; 
	if ( name == "MIN TARGET DISTANCE" ) minTargetDistance =  ((ofxUISlider * )e.widget)->getScaledValue() ; 


	*/

	gui->autoSizeToFitWidgets();
    ofAddListener(gui->newGUIEvent,this,&testApp::guiEvent);
    
    gui->loadSettings("GUI/guiSettings.xml");
}

void testApp::guiEvent(ofxUIEventArgs &e)
{
	string name = e.widget->getName(); 
	int kind = e.widget->getKind(); 

	if ( name == "SPHERE RADIUS" ) sphereRadius =  ((ofxUISlider * )e.widget)->getScaledValue() ; 
	if ( name == "DOLLY SPEED" ) dollySpeed =  ((ofxUISlider * )e.widget)->getScaledValue() ; 
	if ( name == "MIN TARGET DISTANCE" ) minTargetDistance =  ((ofxUISlider * )e.widget)->getScaledValue() ; 

	if ( name == "LATITUDE OFFSET" ) locationOffset.x =  ((ofxUISlider * )e.widget)->getScaledValue() ; 
	if ( name == "LONGITUDE OFFSET" ) locationOffset.y =  ((ofxUISlider * )e.widget)->getScaledValue() ; 

	/*
		gui->addSlider ( "LATITUDE OFFSET" , -180.0f , 180.0f , locationOffset.x ) ; 
	gui->addSlider ( "LONGITUDE OFFSET" , -90.0f , 90.0f , locationOffset.y ) ; 
	*/

	gui->saveSettings( "GUI/guiSettings.xml" ) ; 
}

void testApp::timelineTimerComplete ( int &args ) 
{

	//cameraTarget = locations[ highlightedLocation ].getGlobalPosition(); 

	highlightedLocation++ ; 
	if ( highlightedLocation > locations.size() - 1) 
		highlightedLocation = 0 ; 

	stringstream ss ; 
	ss << "TIMER COMPLETE !now looking at location : " << highlightedLocation << " of : " << ( locations.size() -1 ) << endl ; 
	ofLog( OF_LOG_VERBOSE , ss.str() ) ; 

	//camTarget

	ofVec3f newTarget = locations[ highlightedLocation ].getGlobalPosition(); 
	Tweenzor::add ( &cameraTarget.x , cameraTarget.x , newTarget.x , 0.0f , 1.5f , EASE_OUT_QUAD ) ; 
	Tweenzor::add ( &cameraTarget.y , cameraTarget.y , newTarget.y , 0.0f , 1.5f , EASE_OUT_QUAD ) ; 
	Tweenzor::add ( &cameraTarget.z , cameraTarget.z , newTarget.z , 0.0f , 1.5f , EASE_OUT_QUAD ) ; 


	camera.lookAt( locations[ highlightedLocation ].getGlobalPosition() ) ; 
}


//--------------------------------------------------------------
void testApp::keyPressed(int key){
	switch ( key ) 
	{
		case 'o':
		case 'O':
			break;

		case 'g':
		case 'G':
			gui->toggleVisible() ; 
			break; 

		//Right arrow
		case 358:
			offsetCameraTarget( 1 ) ; 
			break ; 

		//Left arrow
		case 356:
			offsetCameraTarget( -1 ) ; 
			break ; 
	}


	ofLog( OF_LOG_VERBOSE , "keyPressed::( " + ofToString( key ) + " ) " ) ; 
}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

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

void testApp::offsetCameraTarget ( int indexOffset )
{
	//cameraTarget = locations[ highlightedLocation ].getGlobalPosition(); 


	highlightedLocation+= indexOffset ; 
	if ( highlightedLocation > locations.size() - 1) 
		highlightedLocation = 0 ; 
	if ( highlightedLocation < 0 ) 
		highlightedLocation = ( locations.size() -1 ) ; 

	stringstream ss ; 
	ss << "TIMER COMPLETE !now looking at location : " << highlightedLocation << " of : " << ( locations.size() -1 ) << endl ; 
	ofLog( OF_LOG_VERBOSE , ss.str() ) ; 

	//camTarget

	ofVec3f newTarget = locations[ highlightedLocation ].getGlobalPosition(); 
	Tweenzor::add ( &cameraTarget.x , cameraTarget.x , newTarget.x , 0.0f , 1.5f , EASE_OUT_QUAD ) ; 
	Tweenzor::add ( &cameraTarget.y , cameraTarget.y , newTarget.y , 0.0f , 1.5f , EASE_OUT_QUAD ) ; 
	Tweenzor::add ( &cameraTarget.z , cameraTarget.z , newTarget.z , 0.0f , 1.5f , EASE_OUT_QUAD ) ; 
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