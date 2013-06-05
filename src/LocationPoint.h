#pragma once

#include "ofMain.h"

class LocationPoint
{
	public : 
		LocationPoint ( ) { }
		~LocationPoint ( ) { } 

		void setup ( int _id , float _latitude , float _longitude , ofColor color , ofPoint * locationOffset ) ;
		void update ( ) ; 
		void draw ( ) ;
		void drawSelected ( ) ;

		ofPoint getGlobalPosition() ; 

		int id ; 
		float latitude ; 
		float longitude ; 
		ofColor debugColor ; 
		float * sphereRadius ; 
		ofPoint *locationOffset ; 

};