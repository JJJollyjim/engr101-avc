#include<stdio.h>
#include<time.h>
#include<iostream>
using namespace std;
#include"E101.h"
#include"camera.h"

int drive() {

    // proportionality constant
    float kp = 0.5;

    int proportional_signal;

    while(true) {
        proportional_signal = horizontalSample() * kp;
        
        int baseSpeed = 10;
        
        double left = baseSpeed + (proportional_signal/(30600*kp))*254;
        double right = baseSpeed + (-1*(proportional_signal/(30600*kp)))*254;
        
        if (left > 254) {
			left = 254;
			}
		if (right > 254) {
			right = 254;
			}

        set_motor(1, left );
        set_motor(2, right);

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

		cout << "Current Error is " << horizontalSample() <<".\n";
		cout << "Current Left Speed is " << left <<".\n";
		cout << "Current Right Speed is " << right <<".\n";
        sleep1(0, 100000); // 0.1 seconds
    }
    return 0;
}


int main() {
    init();
    
    
    //while(true) {
		//printf("Current Error: %d", horizontalSample());
		//cout << "Current Error is " << horizontalSample() <<".\n";		
	//	display_picture(0,1000);		
	//	}

    drive();

    return 0;
}

