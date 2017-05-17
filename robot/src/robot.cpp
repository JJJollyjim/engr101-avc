#include<stdio.h>
#include<time.h>
#include<iostream>
#include"E101.h"
#include"camera.h"

using namespace std;

// Global Variables
string GATE_IP = "0.0.0.0"; //TODO: Find correct IP for gate
int GATE_PORT = 0000; //TODO: Find correct port for gate

//Tuning
float KP = 0.5; // proportionality constant
float KD = 0.5; // derivative constant
int BASE_SPEED = 50;

int stopMotors() {
    // Sets speed of both motors to 0
    set_motor(1, 0);
    set_motor(2, 0);
    cout << "Both motors stopped (speed: 0)\n";
}

int openGate() {
    //TODO: Find out what the actual gate opening process is, e101 wiki and Arthur's notes no help

    // Listens for gate to broadcast password, then sends that password to the gate, resulting in the gate opening.

    int password; // receive_from_server() returns an int according to e101.h

    connect_to_server(GATE_IP, GATE_PORT);

    // receive password from gate
    password = recieve_from_server("give password pls"); // unclear what message should be sent to get password

    // send password to gate, should open
    send_to_server(password);

    //TODO: check gate has opened with sensors(+ account for time where gate is above sensors LoS but not fully open)
    //TODO: wrap this in a for loop tha waits a reasonable time for gate to open before retrying
//    if (sensors no longer detect gate) {
//        wait x seconds (for gate to fully open)
//        return 1; // return that the gate has successfully opened
//    } else {
//        openGate(); // Try again
//    }
    return 0;
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
        derivative_signal = (error - previous_error) * KD; // (error - previous): range -240 to 240
        previous_error = error;

        prop_component = proportional_signal/(120*1.0*KP);
        deriv_component = derivative_signal/(240*1.0*KD); // ? - unclear how to calculate derivative component

        PID_sum = prop_component + deriv_component;

        deltaLeft = PID_sum*254; // 254 because of bug in library...
        deltaRight = -1*PID_sum*254 ; //... Motors can run endlessly if set to 255.

        set_motor(1, (BASE_SPEED + deltaLeft));
        set_motor(2, (BASE_SPEED + deltaRight));

        // sleep1(0,100000); // 0.1 seconds - 10FPS
    }
    return 0;
}

int main() {
    init();

    drive();

    //TODO: Implement a way to break out of drive loop and safely stop motors - Wait for an input in terminal?
    // if (program end condition) {
    //    stopMotors();
    //    stop(); // function from e101 lib - can't find what it does in lecture slides, Arthur's notes or e101 wiki
    //    return 0;
    // }

    return 0;
}

