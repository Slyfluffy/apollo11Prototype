//
//  point.h
//  apollo_11
//
//  Created by Journey Curtis on 1/13/22.
//

#ifndef point_h
#define point_h

class Point {
private:
   float x;
   float y;
public:
   // Constructors
   Point() { x = 0; y = 0; }
   Point(float x, float y) { this->x = x; this->y = y; }
   
   // Getters/Setters
   float getX() const { return x; }
   float getY() const { return y; }
   void setX(float x) { this->x = x; }
   void setY(float y) { this->y = y; }
};

#endif /* point_h */
