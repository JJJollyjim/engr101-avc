#include<stdio.h>
#include<time.h>
#include<iostream>
#include"E101.h"
#include"camera.h"

using namespace std;

// Global Variables
String GATE_IP = null;
String GATE_PORT = null;

//Tuning
float KP = 0.5; // proportionality constant
int BASE_SPEED = 50;

int openGate() {
    // Listens for gate to broadcast password, then sends that password to the gate, resulting in the gate opening.

}

int drive() {

    int proportional_signal;
    int deltaLeft;
    int deltaRight;

    while(true) {
        proportional_signal = horizontalSample() * KP;

        deltaLeft = proportional_signal/(120*1*KP)*254; // 254 because of bug in library...
        deltaRight = -1*proportional_signal/(120*1*KP)*254 ; //... Motors can run endlessly if set to 255.

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
        // sleep1(0,200000); // 0.2 seconds
    }
    return 0;
}


int main() {
    init();
    
    
    while(true) {
		printf("Current Error: %d", horizontalSample());		
		display_picture(3,0);		
		}

    //drive();

    return 0;
}

