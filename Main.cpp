//
//  Main.cpp
//  
//
//  Created by Michael Saily only 18/05/17.
//
//
#include <stdio.h>
#include <time.h>
#include "E101.h"

// If the sum is equal to 999 - then its on the black 
int read_camera(){
    double row = 120;
    int sum, s = 0;
    double signal = 0;
    int numWhitePixels = 0;
    
    take_picture();
    for(int i = 0; i < 320; i++){
        s = (get_pixel(row, i, 3) > 127) ? 1:0;
        numWhitePixels = (s==1) ? numWhitePixels++:numWhitePixels;
        sum += (i-160)*s;
        if(numWhitePixels > 0){ sum/numWhitePixels; }
        else { sum = 999; }
    }
    signal = sum;
    UI.printf("Error: %d \n", signal);
    return signal;
}

int main(){
    init();
    double errorPID;
    double signal = 0;
    
    int driveLeft, driveRight = 50;
    int backSpeed = -127;
  
    // Implementing PID
    float dAdjustment = 0.5;
    float pAdjustment = 0.5;
    double errorTotal = 0;
    
    double differential, proportional = 0;
    
    while(true){
        signal = read_camera();
        
        if(signal == 0){
            set_motor(0, driveLeft);//Left motor - depending on wiring
            set_motor(1, driveRight); // Right motor - depending on wiring
            sleep(0, 1000000);
        }
        else if (signal > 0){
            set_motor(1, driveRight);
            //set_motor(0, driveLeft);
        }
        else if (singal == 999){
            driveLeft = -127;
            driveRight = -127;
            set_motor(1, backSpeed);
            set_motor(0, backSpeed);
            //set_motor(0, driveLeft);
        }
        else {
            set_motor(0, driveRight);
        }
    }
    return 0;
}


//Sum should be 0, if the white line is in the centre of the screen or picture
// A positive sum would indicate that the line is to the right hand side of the image
// A negative sum should indicate that the line is to the left hand side of the image
