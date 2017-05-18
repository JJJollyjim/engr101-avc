#include<stdio.h>
#include<time.h>
#include<iostream>
#include"E101.h"
#include"camera.h"

using namespace std;

// Global Variables
char GATE_IP[15] = {'1','9','2','.','1','6','8','.','1','.','2','5','5'}; //TODO: Find correct IP for gate
int GATE_PORT = 0000; //TODO: Find correct port for gate

//Tuning
float KP = 0.7; // proportionality constant
float KD = 0.4; // derivative constant
int BASE_SPEED = 0;
int TURNINESS = 32;

int stopMotors() {
    // Sets speed of both motors to 0
    set_motor(1, 0);
    set_motor(2, 0);
    cout << "Both motors stopped (speed: 0)\n";
}

int openGate() {
    //TODO: Find out what the actual gate opening process is, e101 wiki and Arthur's notes no help

    // Listens for gate to broadcast password, then sends that password to the gate, resulting in the gate opening.

    char password[10]; // receive_from_server() returns an int according to e101.h
    char message[10] = {'g','i','v','e',' ','p','w'}; // unclear what message should be sent to get password

    connect_to_server(GATE_IP, GATE_PORT);

    // receive password from gate
    int pwInt = receive_from_server(message);
    sprintf(password,"%ld",pwInt); // convert to char[]

    // send password to gate, should open
    send_to_server(password);

    //TODO: check gate has opened with sensors(+ account for time where gate is above sensors LoS but not fully open)
    //TODO: wrap this in a for loop that waits a reasonable time for gate to open before retrying
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
    int leftSpeed;
    int rightSpeed;

    while(true) {
        error = horizontalSample(); // Value between -120 and 120
        proportional_signal = error * KP;
        derivative_signal = (error - previous_error) * KD; // (error - previous): range -240 to 240
        previous_error = error;

	if (whiteness() < 1500) {
		cout << "BLACK";
		leftSpeed = -60;
		rightSpeed = -60;
	} else {
		cout << "Raw Error: " << error << "\n";

		prop_component = proportional_signal/(120*1.0*KP);
		deriv_component = derivative_signal/(240*1.0*KD); // ? - unclear how to calculate derivative component

		PID_sum = 0-(prop_component + deriv_component);

		deltaLeft = PID_sum*TURNINESS; // 254 because of bug in library...
		deltaRight = -1*PID_sum*TURNINESS ; //... Motors can run endlessly if set to 255.

		leftSpeed = (BASE_SPEED + deltaLeft);
		rightSpeed = (BASE_SPEED + deltaRight);
	}

        if (leftSpeed > 250) {
            leftSpeed = 250;
        } else if (leftSpeed < -250) {
            leftSpeed = -250;
        }

        if (rightSpeed > 250) {
            rightSpeed = 250;
        } else if (rightSpeed < -250) {
            rightSpeed = -250;
        }

        //set_motor(1, leftSpeed);
        //set_motor(2, rightSpeed);

        cout << "Left motor speed: " << leftSpeed <<
                " Right motor speed: " << rightSpeed << "\n";


	stopMotors();
        sleep1(0,50000); // 0.1 seconds - 10FPS
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

