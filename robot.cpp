#include <stdio.h>
#include <time.h>
#include <iostream>
#include "E101.h"
#include "camera.h"

using namespace std;

// Global Variables
char GATE_IP[15] = {'1','3','0','.','1','9','5','.','6','.','1','9','6'};
int GATE_PORT = 1024;

//Tuning
double KP = 0.5; // proportionality constant
double KD = 0; // derivative constant
double KDelta = 0; // high-low constant
int BASE_SPEED = 35;
int TURNINESS = 1;
int BLACK_THRESH = 3;

int ACTUALLY_SET_MOTORS = 1;

int stopMotors() {
    // Sets speed of both motors to 0
    set_motor(1, 0);
    set_motor(2, 0);
    cout << "Both motors stopped (speed: 0)\n";
}

int openGate() {

    // Listens for gate to broadcast password, then sends that password to the gate, resulting in the gate opening.

    char password[24]; // receive_from_server() returns an int according to e101.h
    char message[14] = {0x1B, '[', '4', '5', 'm', 'P','l','e','a','s','e'}; 
    //char message[6] = {'P','l','e','a','s','e'}; 

    connect_to_server(GATE_IP, GATE_PORT);

    send_to_server(message);

    // receive password from gate
    int pwInt = receive_from_server(password);
    printf("%s %ld\n",password,pwInt); // convert to char[]

    // send password to gate, should open for 4 seconds
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
    double previous_error = 0;
    int deltaLeft;
    int deltaRight;
    int leftSpeed;
    int rightSpeed;

    while(true) {
        double error = horizontalSample();
        double errorHigh = horizontalSampleHigh();

        double prop_signal = error * KP;
        double deriv_signal = (error - previous_error) * KD; // (error - previous): range -240 to 240
        double deltap_signal = (errorHigh - error) * KDelta;
        previous_error = error;

        int whitenessval = whiteness();

        cout << whitenessval << ", ";

        if (whitenessval < BLACK_THRESH) {
            cout << "B ";
            leftSpeed = -45;
            rightSpeed = -45;
        } else {
            cout << "W ";

            double PID_sum = 0-(prop_signal + deriv_signal + deltap_signal);

            deltaLeft = PID_sum;
            deltaRight = -1*PID_sum ;

            cout << "P " << prop_signal << ", Delta " << deltap_signal;

            if (deltaLeft < 0)
                deltaLeft *= 2;
            if (deltaRight < 0)
                deltaRight *= 2;

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

        if (ACTUALLY_SET_MOTORS) {
            set_motor(1, -rightSpeed);
            set_motor(2, -leftSpeed);
        }

        //cout << " " << leftSpeed <<
        //":" << rightSpeed << ", " << whitenessval;

        cout << endl;

        sleep1(0,5000); // 0.1 seconds - 10FPS
    }
    return 0;
}

int main() {
    init();
    open_screen_stream();

    //openGate();
    drive();

    sleep1(1,0);

    stopMotors();

    //TODO: Implement a way to break out of drive loop and safely stop motors - Wait for an input in terminal?
    // if (program end condition) {
    //    stopMotors();
    //    stop(); // function from e101 lib - can't find what it does in lecture slides, Arthur's notes or e101 wiki
    //    return 0;
    // }

    return 0;
}

