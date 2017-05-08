#include <stdio.h>
#include <time.h>
#include "E101.h"
#include "camera.h"

int drive() {

    // proportionality constant
    float kp =; //TODO: find a reasonable value for this

    int proportional_signal;

    while(true) {
        proportional_signal = horizontalSample() * kp;

        set_motor(1, (proportional_signal/(15*1*kp))*254);
        set_motor(2, (-1*proportional_signal/(15*1*kp))*254);

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

        sleep1(0, 100000); // 0.1 seconds
    }
    return 0;
}


int main() {
    init();

    drive();

    return 0;
}

