//
//  Main.cpp
//  
//
//  Created by Michael Saily on 18/05/17.
//
//

#include <stdio.h>
#include <time.h>

int read_camera(){
    double col = 0;
    double row = 120;
    take_picture();
    int sum, s = 0;
    double signal = 0;
    int white = 0;
    
    for(int i = 0; i < 320; i++){
        white = get_pixel(col, row, 3);
        if(white > 127){
            s = 1;
        }
        else {
            s = 0;
        }
        sum = sum + (i-160)*s;
    }
    
    signal = sum;
    return signal;
}

int main(){
    init();
    double errorPID;
    double signal = 0;
    
    int driveLeft = 100;
    int driveRight = 100;
    
    // Implementing PID
    
    float dAdjustment = 0.5;
    float iAdjustment = 0.5;
    float pAdjustment = 0.5;
    double errorTotal = 0;
    
    double differential, integral, proportional = 0;
    
    while(true){
        signal = read_camera();
        
        if(signal == 0){
            set_motor(0, driveLeft);//Left motor - depending on wiring
            set_motor(1, driveRight); // Right motor - depending on wiring
            sleep(0, 1000000);
            
            
        }
        else if (singal > 0){
            set_motor(1, driveRight);
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
