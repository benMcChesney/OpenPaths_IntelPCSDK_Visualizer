#pragma once

#include "ofMain.h"

class LocationPoint
{
	public : 
		LocationPoint ( ) { }
		~LocationPoint ( ) { } 

		void setup ( int _id , float _latitude , float _longitude , ofColor color ) ;
		void update ( ) ; 
		void draw ( ) ; 

		ofVec3f getGlobalPosition() ; 

		int id ; 
		float latitude ; 
		float longitude ; 
		ofColor debugColor ; 

};