#include<stdio.h>
#include<time.h>
#include<iostream>
#include"E101.h"

using namespace std;

int horizontalSample() {
    // returns an int in the range -120 to 120
    int pixels[32];
    double sum = 0;

    take_picture();

    for (int i = 1; i < 32; i++) {
        int w = get_pixel(120,i*10,3);

        // Filters noise by simplifying pixels as either black or white, depending on th white value of the pixel
        if (w > 127) {
            pixels[i-1] = 255;
        } else {
            pixels[i-1] = 0;
        }
    }

    // using odd amount so scaling factor is even. Dropped pixel is on the very right and not very useful
    for (int i = 0; i < 31; i++) {
        double s = i - 15;

        if(pixels[i] == 255) {
            sum += s;
        }

    }

    return (int) sum;
}

int whiteness() {
	int whiteness = 0;
	for (int i = 1; i < 32; i++) {
		int w = get_pixel(120,i*10,3);
		whiteness += w;
	}
	
	cout << "White" << whiteness << endl;

	return whiteness;
}
