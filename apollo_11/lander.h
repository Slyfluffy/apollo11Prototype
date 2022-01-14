//
//  lander.h
//  apollo_11
//
//  Created by Journey Curtis on 1/4/22.
//

#ifndef lander_h
#define lander_h

/****************************************************
 * APOLLO 11 :: LANDER
 * Lander class. contains everything required for the
 * lander to function
 ***************************************************/
class Lander
{
private:
   float weight;
   float vPower;
   float hPower;
   float xPosition;
   float yPosition;
   float vVelocity;
   float hVelocity;
   float vAcceleration;
   float hAcceleration;
   float speed;
   float angle;
   
   
public:
   //Constructors
   Lander();
   Lander(float angle, float vVelocity, float hVelocity; float yPosition);
   
   // Getters
   float getWeight()  const { return weight;  }
   float getVPower() const { return vPower; }
   float getHPower() const { return hPower; }
   float getAngle() const { return angle; }
   float getVVelocity() const { return vVelocity; }
   float getHVelocity() const { return hVelocity; }
   float getSpeed() const { return speed; }
   float getXPosition() const { return xPosition; }
   float getYPosition() const { return yPosition; }
   float getvAcceleration() const { return vAcceleration; }
   float gethAccelreation() const { return hAcceleration; }

   // Setters
   void setAngle(float angle) { this->angle = angle; }
   void setVVelocity(float vVelocity) { this->vVelocity = vVelocity; }
   void setHVelocity(float hVelocity) { this->setHVelocity = hVelocity; }
   void setSpeed(float speed) { this->speed = speed; }
   void setXPosition(float xPosition) { this->xPosition = xPosition; }
   void setYPosition(float yPosition) { this->yPosition - yPosition; }
   void setvAcceleration(float vAcceleration) { this->vAcceleration = vAcceleration; }
   void sethAcceleration(float hAcceleration) { this->hAcceleration = hAcceleration; }
   
};

#endif /* lander_hpp */
