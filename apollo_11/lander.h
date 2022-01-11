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
   
public:
   //Constructors
   Lander();
   
   float getWeight()  const { return weight;  }
   float getVPower() const { return vPower; }
   float getHPower() const { return hPower; }
};

#endif /* lander_hpp */
