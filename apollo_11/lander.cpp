//
//  lander.cpp
//  apollo_11
//
//  Created by Journey Curtis on 1/4/22.
//

#include "lander.h"

/*********************************************
 * APOLLO 11 :: LANDER :: DEFAULT CONSTRUCTOR
 * Constructs Lander class with default values
 ********************************************/
Lander :: Lander() {
   this->weight = 15103;
   this->vPower = 45000;
   this->hPower = 450;
   this->speed = 0;
   this->xPosition = 0;

   this->angle = 0;
   this->vVelocity = 0;
   this->hVelocity = 0;
   this->yPosition = 100;
   this->vAcceleration = 2.9795;
   this->hAcceleration = .029795;
}

Lander::Lander(float angle, float vVelocity, float hVelocity; float yPosition) {
	this->weight = 15103;
	this->vPower = 45000;
	this->hPower = 450;
	this->speed = 0;
	this->xPosition = 0;

	this->vAcceleration = 2.9795;
	this->hAcceleration = .029795;

	this->angle = angle;
	this->vVelocity = vVelocity;
	this->hVelocity = hVelocity;
	this->yPosition = yPosition;
}
