#include "LocationPoint.h"

void LocationPoint::setup ( int _id , float _latitude , float _longitude , ofColor _color ,ofPoint * _locationOffset )
{
	id = _id ; 
	latitude = _latitude ;  
	longitude = _longitude ; 
	debugColor = _color; 
	locationOffset = _locationOffset ; 
}
		
void LocationPoint::update ( ) 
{

}

ofPoint LocationPoint::getGlobalPosition() 
{
	/*
		ofQuaternion latRot, longRot, spinQuat;
		latRot.makeRotate( latitude, 1, 0, 0);
		longRot.makeRotate( longitude, 0, 1, 0);
		//spinQuat.makeRotate( rotationAmount , 0, 1, 0);
		
		//our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
		ofVec3f center = ofVec3f(0,0, ( *sphereRadius ) );
		//multiplying a quat with another quat combines their rotations into one quat
		//multiplying a quat to a vector applies the quat's rotation to that vector
		//so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
		ofVec3f worldPoint = latRot * longRot * spinQuat * center;
*/
	ofPoint p ; 
	p.x = ofMap( latitude + (*locationOffset).x , -180 , 180 , 0 , ofGetWidth() , true ) ; 
	p.y = ofMap( longitude + (*locationOffset).y , -90 , 90 , 0 , ofGetHeight() , true ) ; 


		return p ; 
}


void LocationPoint::draw ( ) 
{

	ofFill() ; 
	ofVec3f worldPoint = getGlobalPosition() ; //latRot * longRot * spinQuat * center;
		
	ofSetColor( debugColor ) ; 
	//draw it and label it
	//ofLine(ofVec3f(0,0,0), worldPoint);
	ofCircle( worldPoint , 1 ) ; 

}

void LocationPoint::drawSelected ( ) 
{

	ofFill() ; 
	ofVec3f worldPoint = getGlobalPosition() ; //latRot * longRot * spinQuat * center;
		
	ofSetColor( debugColor ) ; 
	//draw it and label it
	//ofLine(ofVec3f(0,0,0), worldPoint);
	ofCircle( worldPoint , 10 ) ; 

}