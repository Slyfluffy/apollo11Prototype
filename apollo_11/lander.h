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
   float v_power;
   float h_power;
   
public:
   //Constructors
   Lander();
   
   float get_weight()  const { return weight;  }
   float get_v_power() const { return v_power; }
   float get_h_power() const { return h_power; }
};

#endif /* lander_hpp */
