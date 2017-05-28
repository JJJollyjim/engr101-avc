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

#define MIN_PIXELS 20
#define MAX_PIXELS 40

int identifyPaths() {
    /* When called identifies if there are paths to the north, east and west.
     * returns a string containing "NEW" if junction has all paths, "E" if only eastern path etc.
     * if a empty string is returned, then this method shouldn't have been called in the first place eg. in curves quad2
     */
    int paths = 0;
    double northPixels;
    double eastPixels;
    double westPixels;

    take_picture();

    //North
    for (int i = 0; i < 320; i++) {
        int w = get_pixel(0,i,3);

        // Filters noise by simplifying pixels as either black or white, depending on th white value of the pixel
        if (w > BLACK_THRESHOLD) {
            northPixels += 1;
        }
    }
    //East
    for (int i = 0; i < 240; i++) {
        int w = get_pixel(i,0,3);

        // Filters noise by simplifying pixels as either black or white, depending on th white value of the pixel
        if (w > BLACK_THRESHOLD) {
            eastPixels += 1;
        }
    }

    //West
    for (int i = 1; i < 240; i++) {
        int w = get_pixel(i,319,3);

        // Filters noise by simplifying pixels as either black or white, depending on th white value of the pixel
        if (w > BLACK_THRESHOLD) {
            westPixels += 1;
        }
    }

//    if (northPixels >= ) {
//        paths += "N";
//    }
//
//    if (eastPixels >= 160/sampleInterval * accuracy) {
//        paths += "E";
//    }
//
//    if (westPixels >= 160/sampleInterval * accuracy) {
//        paths += "W";
//    }


    cout << endl << "LEFT: " << westPixels << ", TOP: " << northPixels << ", RIGHT: " << eastPixels << endl;
    return paths;
}
