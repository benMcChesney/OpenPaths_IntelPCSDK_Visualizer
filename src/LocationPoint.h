#pragma once

#include "ofMain.h"

class LocationPoint
{
	public : 
		LocationPoint ( ) { }
		~LocationPoint ( ) { } 

		void setup ( int _id , float _latitude , float _longitude ) ;
		void update ( ) ; 
		void draw ( float rotationAmount ) ; 

		int id ; 
		float latitude ; 
		float longitude ; 

};