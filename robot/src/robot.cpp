#include<stdio.h>
#include<time.h>
#include<iostream>
#include"E101.h"
#include"camera.h"

using namespace std;

// Global Variables
String GATE_IP = 0;
String GATE_PORT = 0;

//Tuning
float KP = 0.5; // proportionality constant
float KD = 0.5; // derivative constant
int BASE_SPEED = 50;

int openGate() {
    // Listens for gate to broadcast password, then sends that password to the gate, resulting in the gate opening.

}

int drive() {

    int error;
    int previous_error = 0;
    int proportional_signal;
    float prop_component;
    int derivative_signal;
    float deriv_component;
    float PID_sum;
    int deltaLeft;
    int deltaRight;

    while(true) {
        error = horizontalSample(); // Value between -120 and 120
        proportional_signal = error * KP;
        derivative_signal = (error - previous_error) * KD; // error - previous: range -240 to 240
        previous_error = error;

        prop_component = proportional_signal/(120*1.0*KP);
        deriv_component = derivative_signal/(240*1.0*KD); //?

        PID_sum = prop_component + deriv_component;

        deltaLeft = PID_sum*254; // 254 because of bug in library...
        deltaRight = -1*PID_sum*254 ; //... Motors can run endlessly if set to 255.

        set_motor(1, (BASE_SPEED + deltaLeft));
        set_motor(2, (BASE_SPEED + deltaRight));

        /*
        if (proportional_signal == 0) {
            set_motor(1, 80);
            set_motor(2, 80);
        } else if (proportional_signal > 0) {
            set_motor(1, );
            set_motor(2, );
        } else if (proportional_signal < 0) {
            set_motor(1, );
            set_motor(2, )
        }
        **/

        //TODO: sleep1 seems to cause compilation errors (undefined reference) when called within a while loop
        // atleast when compiling on a RPi 3, our robot may be different
        sleep1(0,100000); // 0.1 seconds - 10FPS
    }
    return 0;
}

int main() {
    init();

    drive();

    //TODO: Implement a way to break out of drive loop and safely stop motors - Wait for an input in terminal?

    // Found within e101 lib - unclear how it works, e101 wiki and Arthur's notes were no help.
    // stop();

    return 0;
}

