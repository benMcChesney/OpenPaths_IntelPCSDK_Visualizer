#include "LocationPoint.h"

void LocationPoint::setup ( int _id , float _latitude , float _longitude , ofColor _color ) 
{
	id = _id ; 
	latitude = _latitude ;  
	longitude = _longitude ; 
	debugColor = _color; 
}
		
void LocationPoint::update ( ) 
{

}

ofVec3f LocationPoint::getGlobalPosition() 
{
		ofQuaternion latRot, longRot, spinQuat;
		latRot.makeRotate( latitude, 1, 0, 0);
		longRot.makeRotate( longitude, 0, 1, 0);
		//spinQuat.makeRotate( rotationAmount , 0, 1, 0);
		
		//our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
		ofVec3f center = ofVec3f(0,0,300);
		//multiplying a quat with another quat combines their rotations into one quat
		//multiplying a quat to a vector applies the quat's rotation to that vector
		//so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
		ofVec3f worldPoint = latRot * longRot * spinQuat * center;

		return worldPoint ; 
}


void LocationPoint::draw ( ) 
{
	/*
	//three rotations
		//two to represent the latitude and lontitude of the city
		//a third so that it spins along with the spinning sphere 
		ofQuaternion latRot, longRot, spinQuat;
		latRot.makeRotate( latitude, 1, 0, 0);
		longRot.makeRotate( longitude, 0, 1, 0);
		spinQuat.makeRotate( rotationAmount , 0, 1, 0);
		
		//our starting point is 0,0, on the surface of our sphere, this is where the meridian and equator meet
		ofVec3f center = ofVec3f(0,0,300);
		//multiplying a quat with another quat combines their rotations into one quat
		//multiplying a quat to a vector applies the quat's rotation to that vector
		//so to to generate our point on the sphere, multiply all of our quaternions together then multiple the centery by the combined rotation
		*/
	ofFill() ; 
		ofVec3f worldPoint = getGlobalPosition() ; //latRot * longRot * spinQuat * center;
		
		ofSetColor( debugColor ) ; 
		//draw it and label it
		ofLine(ofVec3f(0,0,0), worldPoint);
		ofCircle( worldPoint , 4 ) ; 

		//set the bitmap text mode billboard so the points show up correctly in 3d
		ofDrawBitmapString( "city : " + ofToString( id ) , worldPoint );
}