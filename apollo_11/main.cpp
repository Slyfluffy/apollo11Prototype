/*************************************************************
 * 1. Name:
 *      Journey Curtis
 * 2. Assignment Name:
 *      Lab 01: Apollo 11
 * 3. Assignment Description:
 *      Simulate the Apollo 11 landing
 * 4. What was the hardest part? Be as specific as possible.
 *      Translating the math into code. Other than that not too bad!
 * 5. How long did it take for you to complete the assignment?
 *      3.0 hours™
 *****************************************************************/
#include <iostream>
#include <iomanip>
#include <cmath>
#include "lander.h"
#include "point.h"

using namespace std;

// Prototypes
// Get functions
float getVVelocity();
float getHVelocity();
float getAltitude();
float getInitialAngle();
float getNewAngle();

// Functions that run
void runSimulation(Lander lander, float angle);

// Computation and calculate functions
// Time
float computeLandingTime(float vVelocity, float altitude);

// Velocity
float calculateVVelocity(float velocity, float time, float angle);
float calculateHVelocity(float velocity, float time, float angle);
float calculateFinalVelocity(float vVelocity, float hVelocity);

// Thrust
float calculateVThrust(float thrust, float angle);
float calculateHThrust(float thrust, float angle);

// Position
Lander calculateXPosition(Lander l);
Lander calculateYPosition(Lander l);

// Conversion functions
float convertToRadians(float degree);

// Display functions
void displayCalculations(float time, float finalV, float finalH, float finalVelocity);
void displayNonlandingMessage();
void displayFiveSecondMessage();
void displaySecondData(int second, Lander lander, float angle);

///*********************************************
// * APOLLO 11 :: TESTPROGRAM
// * INPUTS    :: NONE
// * OUTPUTS   :: NONE
// * Tests the program with specific test cases!
// ********************************************/
//void testProgram() {
//   float v_velocity = 0.0;
//   float h_velocity = 0.0;
//   float altitude = 0.0;
//
//   for (int i = 0; i <= 3; i++) {
//      switch (i) {
//         case 0: // Test case 1
//            v_velocity = 0;
//            h_velocity = 0;
//            altitude = 10;
//            cout << "Zero Velocity:\n";
//            break;
//         case 1: // Test case 2
//            v_velocity = -9.07;
//            h_velocity = -.26;
//            altitude = 30;
//            cout << "\nSoft Landing:\n";
//            break;
//         case 2: // Test case 3
//            v_velocity = -20;
//            h_velocity = -5;
//            altitude = 50;
//            cout << "\nHard landing:\n";
//            break;
//         case 3: // Test case 4
//            v_velocity = -16.4593;
//            h_velocity = -.36;
//            altitude = 100;
//            cout << "\nArmstrong is awesome!\n";
//            break;
//      }
//      run_simulation(v_velocity, h_velocity, altitude);
//   }
//   cout << endl;
//}

/************************************************
 * APOLLO 11 :: MAIN
 * INPUTS    :: NONE
 * OUTPUTS   :: NONE
 * Main runs the program. It calls the functions
 * to get all the necessary variables, then sends
 * it to run_simulation.
 ***********************************************/
int main(int argc, const char * argv[]) {
//   test_program();
   float vVelocity = getVVelocity();
   float hVelocity = getHVelocity();
   float altitude = getAltitude();
   float angle = getInitialAngle();

   Lander lander = Lander(vVelocity, hVelocity, altitude);

   runSimulation(lander, angle);
   
   return 0;
}

/***********************************************
 * APOLLO 11 :: RUNSIMULATION
 * INPUTS    :: v_velocity, h_velocity, altitude
 * OUTPUTS   :: NONE
 * Runs the simulation.
 **********************************************/
void runSimulation(Lander lander, float angle) {
   int second = 1;
   int interval = 1;
   
   while (interval <= 2) {
      displayFiveSecondMessage();
      for (int count = 1; count < 6; count++) {
         float dx = calculateHVelocity(lander.getVelocity().getDx(), second, angle);
         float dy = calculateVVelocity(lander.getVelocity().getDy(), second, angle);
         lander.setVelocity(dx, dy);
         
         lander = calculateXPosition(lander);
         lander = calculateYPosition(lander);
         
         displaySecondData(second, lander, angle);
         second++;
      }
      interval++;
      angle = getNewAngle();
   }
}

/************************************************
 * APOLLO 11 :: GETVVELOCITY
 * INPUTS    :: NONE
 * OUTPUTS   :: vVelocity
 * Retreives the vertical velocity from the user!
 ***********************************************/
float getVVelocity() {
   float vVelocity;
   
   cout << "What is your vertical velocity (m/s)? ";
   cin >> vVelocity;
   
   return vVelocity;
}

/**************************************************
 * APOLLO 11 :: GETHVELOCITY
 * INPUTS    :: NONE
 * OUTPUTS   :: hVelocity
 * Retreives the horizontal velocity from the user!
 *************************************************/
float getHVelocity() {
   float hVelocity;
   
   cout << "What is your horizontal velocity (m/s)? ";
   cin >> hVelocity;
   
   return hVelocity;
}

/**********************************
 * APOLLO 11 :: GETALTITUDE
 * INPUTS    :: NONE
 * OUTPUTS   :: altitude
 * Gets the altitude from the user!
 *********************************/
float getAltitude() {
   float altitude = -5;
   
   while (altitude < 0) {
      cout << "What is your altitude (m)? ";
      cin >> altitude;
   }
   
   return altitude;
}

/**********************************
 * APOLLO 11 :: GETINITIALANGLE
 * INPUTS    :: NONE
 * OUTPUTS   :: angle
 * Gets the intial angle for the LM
 *********************************/
float getInitialAngle() {
   float angle;
   
   cout << "What is the angle of the LM where 0 is up (degrees)? ";
   cin >> angle;
   
   return angle;
}

/*******************************
 * APOLLO 11 :: GETNEWANGLE
 * INPUTS    :: NONE
 * OUTPUTS   :: angle
 * Gets the new angle for the LM
 ******************************/
float getNewAngle() {
   float angle;
   
   cout << "What is the new angle of the LM where 0 is up (degrees)? ";
   cin >> angle;
   
   return angle;
}

/*************************************************
 * APOLLO 11 :: COMPUTEXAXISACCELERATION
 * INPUTS    :: NONE
 * OUTPUTS   :: acceleration
 * Computes the x-axis acceleration and returns it
 ************************************************/
float computeXAxisAcceleration(float angle) {
   Lander apollo11;
   const float a = apollo11.getVPower() / apollo11.getWeight();

   const float landerAcceleration = calculateHThrust(a, angle);
   return landerAcceleration;
}

/*************************************************
 * APOLLO 11 :: COMPUTEYAXISACCELERATION
 * INPUTS    :: NONE
 * OUTPUTS   :: acceleration
 * Computes the y-axis acceleration and returns it
 ************************************************/
float computeYAxisAcceleration(float angle) {
   Lander apollo11;
   
   // We could adjust this to change if we were working with another planet/ space object
   // Maybe through a class next time?
   const float moonAcceleration = -1.625;
   const float a = apollo11.getVPower() / apollo11.getWeight();

   const float landerAcceleration = calculateVThrust(a, angle);
   return landerAcceleration + moonAcceleration;
}

/************************************************
 * APOLLO 11 :: COMPUTELANDINGTIME
 * INPUTS    :: b (velocity), c (distance)
 * OUTPUTS   :: time
 * EQUATION  :: t = (-b + sqrt(square)) / (2 * a)
 * Computes the landing time.
 ***********************************************/
//float computeLandingTime(float b, float c) {
//   float a = computeYAxisAcceleration() / 2;
//
//   float square = (b * b) - (4 * a * c);
//   if (square >= 0)
//      return (-b + sqrt(square)) / (2 * a);
//   else
//      return -1;
//}

/**********************************************
 * APOLLO 11 :: CALCULATEVVELOCITY
 * INPUTS    :: v, t
 * OUTPUTS   :: velocity (vertical)
 * EQUATION  :: vFinal = vInitial + (a * t)
 * Calculates the vertical velocity at landing.
 *********************************************/
float calculateVVelocity(float v, float t, float angle) {
   float a = computeYAxisAcceleration(angle);
   return v + (a * t);
}

/************************************************
 * APOLLO 11 :: CALCULATEHVELOCITY
 * INPUTS    :: v, t
 * OUTPUTS   :: velocity (horizonatal)
 * EQUATION  :: vFinal = vInitial + (a * t)
 * Calculates the horizontal velocity at landing.
 ***********************************************/
float calculateHVelocity(float v, float t, float angle) {
   float a = computeXAxisAcceleration(angle);
   return v + (a * t);
}

/*************************************************
 * APOLLO 11 :: CALCULATEFINALVELOCITY
 * INPUTS    :: v, h
 * OUTPUTS   :: finalVelocity
 * EQUATION  :: c^2 = a^2 + b^2
 * Calculates the total final velocity at landing. 
 ************************************************/
float calculateFinalVelocity(float v, float h) { return sqrt((v * v) + (h * h)); }

/**********************************
 * APOLLO 11 :: CALCULATEVTHRUST
 * INPUTS    :: thrust, angle
 * OUTPUTS   :: hThrust
 * EQUATION  :: dy = t * cos(angle)
 * Calculates Vertical thrust
 *********************************/
float calculateVThrust(float thrust, float angle) { return thrust * cos(angle + M_PI/2); }

/**********************************
 * APOLLO 11 :: CALCULATEHTHRUST
 * INPUTS    :: thrust, angle
 * OUTPUTS   :: hThrust
 * EQUATION  :: dx = t * sin(angle)
 * Calculates horizontal thrust
 *********************************/
float calculateHThrust(float thrust, float angle) { return thrust * sin(angle + M_PI/2); }

/***********************************
 * APOLLO 11 :: CONVERTTORADIANS
 * INPUTS    :: degree
 * OUTPUTS   :: radian
 * EQUATION  :: r = 2 * PI * d / 360
 * Converts the degree to a radian
 **********************************/
float convertToRadians(float degree) { return (2 * M_PI * degree / 360); }

/***********************************
 * APOLLO 11 :: CALCULATEXPOSITION
 * INPUTS    :: lander
 * OUTPUTS   :: lander
 * Calculates the new position 
 * according to velocity
 **********************************/
Lander calculateXPosition(Lander lander) {
   float xPosition = lander.getPoint().getX();
   xPosition += lander.getVelocity().getDx();
   lander.getPoint().setX(xPosition);
   
   return lander;
}

/***********************************
 * APOLLO 11 :: CALCULATEYPOSITION
 * INPUTS    :: lander
 * OUTPUTS   :: lander
 * Calculates the new position 
 * according to velocity
 **********************************/
Lander calculateYPosition(Lander lander) {
   float yPosition = lander.getPoint().getY();
   yPosition += lander.getVelocity().getDy();
   lander.getPoint().setY(yPosition);
   
   return lander;
}

/***********************************************************************
 * APOLLO 11 :: DISPLAYCALCULATIONS
 * INPUTS    :: time, finalVVelocity, finalHVelocity, totalVelocity
 * OUTPUTS   :: NONE
 * Displays the statistics at landing
 **********************************************************************/
void displayCalculations(float time, float finalVVelocity, float finalHVelocity,
                           float totalVelocity) {
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   
   cout << "\tTime to landing:\t\t" << time << " seconds.\n"
        << "\tVertical velocity:\t" << finalVVelocity << " m/s.\n"
        << "\tHorizontal velocity:\t" << finalHVelocity << " m/s.\n"
        << "\tTotal velocity:\t\t" << totalVelocity << " m/s.\n";
}

/*****************************************
 * APOLLO 11 :: DISPLAYNONLANDINGMESSAGE
 * INPUTS    :: NONE
 * OUTPUTS   :: NONE
 * Displays a message if they won't land.
 ****************************************/
void displayNonlandingMessage() { cout << "\tYou will not land but rather fly off into space\n"; }

/**********************************************
 * APOLLO 11 :: DISPLAYNFIVESECONDMESSAGE
 * INPUTS    :: NONE
 * OUTPUTS   :: NONE
 * Displays the header for the five second data
 *********************************************/
void displayFiveSecondMessage() {
   cout << "\nFor the next 5 seconds with the main engine on, the position of the lander is:\n\n";
}

/*************************************************
 * APOLLO 11 :: DISPLAYNONLANDINGMESSAGE
 * INPUTS    :: second, x, y, dx, dy, speed, angle
 * OUTPUTS   :: NONE
 * Displays the data for one second.
 ************************************************/
void displaySecondData(int second, Lander lander, float angle) {
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);

   cout << setw(2) << second << "s - x,y: (" << lander.getPoint().getX() << ", "
        << lander.getPoint().getY() << ")m"  << " dx,dy: (" << lander.getVelocity().getDx()
        << ", " << lander.getVelocity().getDy() << ")m/s" << " speed: "
        << lander.getVelocity().getSpeed() << "m/s angle: " << angle << "deg\n";
}
