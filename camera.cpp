#include<stdio.h>
#include<time.h>
#include<iostream>
#include"E101.h"

using namespace std;

#define LINE_THRESHOLD 128
#define BLACK_THRESHOLD 128

#define LOW_LINE 120
#define HIGH_LINE 40

unsigned char dataFromLastTime[320];

double horizontalSample() {
    double sum = 0;

    take_picture();

    for (int i = 0; i < 320; i++) {
        int w = get_pixel(LOW_LINE,i,3);

        // Filters noise by simplifying pixels as either black or white, depending on th white value of the pixel
        if ((w > dataFromLastTime[i] ? w : dataFromLastTime[i]) > LINE_THRESHOLD) {
            sum += (i - 160);
            set_pixel(LOW_LINE,i,255,0,0);
        }
        
        dataFromLastTime[i] = w;
    }

    return sum / 100;
}

unsigned char high_dataFromLastTime[320];

double horizontalSampleHigh() {
    double sum = 0;

    for (int i = 0; i < 320; i++) {
        int w = get_pixel(HIGH_LINE,i,3);

        // Filters noise by simplifying pixels as either black or white, depending on th white value of the pixel
        if ((w > high_dataFromLastTime[i] ? w : high_dataFromLastTime[i]) > LINE_THRESHOLD) {
            sum += (i - 160);
            set_pixel(HIGH_LINE,i,255,0,0);
        }
        
        high_dataFromLastTime[i] = w;
    }

    return sum / 100;
}
unsigned char whiteness_dataFromLastTime[320 * 20];
int whiteness() {
    int whiteness = 0;
    for (int y = 110; y < 130; y++) {
        for (int i = 1; i < 320; i++) {
            int w = get_pixel(y,i,3);
            if ((w > whiteness_dataFromLastTime[i + 320*(y-110)] ? w : whiteness_dataFromLastTime[i + 320*(y-110)]) > BLACK_THRESHOLD) {
                whiteness++;
            }
            whiteness_dataFromLastTime[i + 320*(y-110)] = w;
        }
    }

    //update_screen();

    return whiteness;
}
