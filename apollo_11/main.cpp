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
#include <cmath>
#include "lander.h"

using namespace std;

//prototypes
float get_v_velocity();
float get_h_velocity();
float get_altitude();

void run_simulation(float v_velocity, float h_velocity, float altitude);
float compute_landing_time(float v_velocity, float altitude);

float calculate_v_velocity(float velocity, float time);
float calculate_h_velocity(float velocity, float time);
float calculate_final_velocity(float v_velocity, float h_velocity);

void display_calculations(float time, float final_v, float final_h, float final_velocity);
void display_nonlanding_message();

/*
 * APOLLO 11 :: TEST_PROGRAM
 * INPUTS    :: NONE
 * OUTPUTS   :: NONE
 * Tests the program with specific test cases!
 */
void test_program() {
   float v_velocity = 0.0;
   float h_velocity = 0.0;
   float altitude = 0.0;
   
   for (int i = 0; i <= 3; i++) {
      switch (i) {
         case 0: // Test case 1
            v_velocity = 0;
            h_velocity = 0;
            altitude = 10;
            cout << "Zero Velocity:\n";
            break;
         case 1: // Test case 2
            v_velocity = -9.07;
            h_velocity = -.26;
            altitude = 30;
            cout << "\nSoft Landing:\n";
            break;
         case 2: // Test case 3
            v_velocity = -20;
            h_velocity = -5;
            altitude = 50;
            cout << "\nHard landing:\n";
            break;
         case 3: // Test case 4
            v_velocity = -16.4593;
            h_velocity = -.36;
            altitude = 100;
            cout << "\nArmstrong is awesome!\n";
            break;
      }
      run_simulation(v_velocity, h_velocity, altitude);
   }
   cout << endl;
}

/*
 * APOLLO 11 :: MAIN
 * INPUTS    :: NONE
 * OUTPUTS   :: NONE
 * Runs the program itself.
 */
int main(int argc, const char * argv[]) {
   test_program();
   float v_velocity = get_v_velocity();
   float h_velocity = get_h_velocity();
   float altitude = get_altitude();

   run_simulation(v_velocity, h_velocity, altitude);
   
   return 0;
}

/*
 * APOLLO 11 :: RUN_SIMULATION
 * INPUTS    :: v_velocity, h_velocity, altitude
 * OUTPUTS   :: NONE
 * Runs the simulation.
 */
void run_simulation(float v_velocity, float h_velocity, float altitude) {
   float landing_time = compute_landing_time(v_velocity, altitude);

   if (landing_time == -1)
      display_nonlanding_message();
   else {
      float final_v_velocity = calculate_v_velocity(v_velocity, landing_time);
      float final_h_velocity = calculate_h_velocity(h_velocity, landing_time);
      float final_velocity = calculate_final_velocity(final_v_velocity, final_h_velocity);

      display_calculations(landing_time, final_v_velocity, final_h_velocity, final_velocity);
   }
}

/*
 * APOLLO 11 :: GET_V_VELOCITY
 * INPUTS    :: NONE
 * OUTPUTS   :: v_velocity
 * Retreives the vertical velocity from the user!
 */
float get_v_velocity() {
   float v_velocity;
   
   cout << "What is your vertical velocity (m/s)? ";
   cin >> v_velocity;
   
   return v_velocity;
}

/*
 * APOLLO 11 :: GET_H_VELOCITY
 * INPUTS    :: NONE
 * OUTPUTS   :: h_velocity
 * Retreives the horizontal velocity from the user!
 */
float get_h_velocity() {
   float h_velocity;
   
   cout << "What is your horizontal velocity (m/s)? ";
   cin >> h_velocity;
   
   return h_velocity;
}

/*
 * APOLLO 11 :: GET_ALTITUDE
 * INPUTS    :: NONE
 * OUTPUTS   :: altitude
 * Gets the altitude from the user!
 */
float get_altitude() {
   float altitude;
   
   cout << "What is your altitude (m)? ";
   cin >> altitude;
   
   return altitude;
}

/*
 * APOLLO 11 :: COMPUTE_X_AXIS_ACCELERATION
 * INPUTS    :: NONE
 * OUTPUTS   :: acceleration
 * Sends the x_axis acceleration
 */
float compute_x_axis_acceleration() {
   Lander apollo_11;

   const float lander_acceleration = (apollo_11.get_h_power() / apollo_11.get_weight());
   return lander_acceleration;
}

/*
 * APOLLO 11 :: COMPUTE_y_AXIS_ACCELERATION
 * INPUTS    :: NONE
 * OUTPUTS   :: acceleration
 * Sends the y_axis acceleration.
 */
float compute_y_axis_acceleration() {
   Lander apollo_11;
   
   // We could adjust this to change if we were working with another planet/ space object
   // Maybe through a class next time?
   const float moon_acceleration = -1.625;

   const float lander_acceleration = (apollo_11.get_v_power() / apollo_11.get_weight());
   return lander_acceleration + moon_acceleration;
}

/*
 * APOLLO 11 :: COMPUTE_LANDING_TIME
 * INPUTS    :: b (velocity), c (distance)
 * OUTPUTS   :: time
 * Computes the landing time.
 */
float compute_landing_time(float b, float c) {
   float a = compute_y_axis_acceleration() / 2;
   
   float square = pow(b, 2) - (4 * a * c);
   if (square >= 0)
      return (-b + sqrt(square)) / (2 * a);
   else
      return -1;
}

/*
 * APOLLO 11 :: CALCULATE_V_VELOCITY
 * INPUTS    :: v, t
 * OUTPUTS   :: velocity (vertical)
 * Calculates the vertical velocity at landing.
 */
float calculate_v_velocity(float v, float t) {
   float a = compute_y_axis_acceleration();
   return v + (a * t);
}

/*
 * APOLLO 11 :: CALCULATE_H_VELOCITY
 * INPUTS    :: v, t
 * OUTPUTS   :: velocity (horizonatal)
 * Calculates the horizontal velocity at landing.
 */
float calculate_h_velocity(float v, float t) {
   float a = compute_x_axis_acceleration();
   return v + (a * t);
}

/*
 * APOLLO 11 :: CALCULATE_FINAL_VELOCITY
 * INPUTS    :: v, h
 * OUTPUTS   :: final_velocity
 * Calculates the total final velocity at landing. Uses pythagorean theorem.
 */
float calculate_final_velocity(float v, float h) { return sqrt(pow(v, 2) + pow(h, 2)); }

/*
 * APOLLO 11 :: DISPLAY_CALCULATIONS
 * INPUTS    :: time, final_v_velocity, final_h_velocity, total_velocity
 * OUTPUTS   :: NONE
 * Displays the statistics at landing
 */
void display_calculations(float time, float final_v_velocity, float final_h_velocity,
                           float total_velocity) {
   cout.setf(ios::fixed);
   cout.setf(ios::showpoint);
   cout.precision(2);
   
   cout << "\tTime to landing:\t\t" << time << " seconds.\n";
   cout << "\tVertical velocity:\t" << final_v_velocity << " m/s.\n";
   cout << "\tHorizontal velocity:\t" << final_h_velocity << " m/s.\n";
   cout << "\tTotal velocity:\t\t" << total_velocity << " m/s.\n";
}

/*
 * APOLLO 11 :: DISPLAY_NONLANDING_MESSAGE
 * INPUTS    :: NONE
 * OUTPUTS   :: NONE
 * Displays a message if they won't land.
 */
void display_nonlanding_message() { cout << "\tYou will not land but rather fly off into space\n"; }
