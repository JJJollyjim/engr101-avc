#include<stdio.h>
#include<time.h>
#include<E101.h>

int horizontalSample() {
    // returns an int in the range -30600 to 30600
    int pixels[32];
    double sum;

    take_picture();

    for (int i = 1; i < 32; i++) {
        int w = get_pixel(120,i*10,3);

        if (w > 127) {
            pixels[i-1] = 255;
        } else {
            pixels[i-1] = 0;
        }
    }

    // using odd amount so scaling factor is even. Dropped pixel is on the very right and not very useful
    for (int i = 0; i < 31; i++) {
        double s = i - 15;

        sum = sum + pixels[i] * s;
    }

    return (int) sum;
}