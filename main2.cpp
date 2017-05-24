#include <stdio.h>
#include <time.h>
#include "E101.h"

void move(int error, int scale); 
//Done method
void openGate(){
  connect_to_server("130.195.6.196", 1024);
  send_to_server("Please0");
  char response[24];
  receive_from_server(response);
  char passWord[24];
  for(int i=0; i<6; i++){
    passWord[i] = response[i]; 
  }
  passWord[7] = 0;
  send_to_server(passWord);
  
  for(int i=0; i<100; i++){
      printf("Gate should be opening \n");
  }
}

//Done method
int getError(){

take_picture(); 
int sum = 0; 
int i, w, s; 
for(i = 0; i < 320; i++){
	w = get_pixel(120, i, 3); 
	
	if(w > 127){
		s = 1; 
	} else {
		s = 0; 
	}
	
	
	
	sum = sum + (i-160) * s;
	return sum; 
	
}

/**
  int error = 0;
  int bitValue = 0;
  int threshold = 127;
  int numWhitePixels = 0;
  
  take_picture();
  for(int i=0; i<320; i++){
	  printf("%d", i); 
	  int pixel = get_pixel(120, i, 3); 
      if(pixel > threshold){
          bitValue = 1;
      }else {
          bitValue = 0;
      }
      
      if(bitValue==1){
        numWhitePixels += (i-160*bitValue);
      }
      else {
          numWhitePixels = numWhitePixels;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
      }
      
    error+=(i*bitValue);
  }
  if(numWhitePixels>0) {
      error=error/numWhitePixels;
  }
  else {
      error = 999;
  }
  
  printf("ERROR: %d", error);
  return error;
  */
}

//Done method
void getScale(int error, int previousError){
  //Proportional
  double kp = 0.5;
  double proportionalSignal = error*kp;
  //Derivative
  double kd = 0.5;
  double derivativeSignal = (error - previousError)*kd;
  
  double scale = proportionalSignal + derivativeSignal;
  //printf("RUNNING"); 
  move(error, scale);
}

//Working
void move(int error, int scale){
  int speedLeft = 55;
  int speedRight = 55;
  if(scale < 0) scale*= -1;
  if(scale > 254) scale = 254;
  
  if(error == 999){
    //printf("GOING BACKWARDS");
    speedLeft = -254;
    speedRight = -254;
  }else if(error == 0){
    //printf("GOING FORWARDS");
    speedLeft = 55;
    speedRight = 55;
  }else if(error < 0){
    //printf("GOING RIGHT");
    speedLeft+=scale;
    speedRight-=scale;
  }else if(error > 0){
    //printf("GOING LEFT");
    speedRight+=scale;
    speedLeft-=scale;
  }
  set_motor(1, speedLeft);
  set_motor(2, speedRight);
  //sleep1(0, 5000);
  //stop(1);
  //stop(2);
}


bool atRed(bool checkRed){
  int error = 0;
  int bitValue = 0;
  int threshold = 127;
  int numRedPixels = 0;
  
  take_picture();
  
  for(int i=0; i<320; i++){
		int pixel = get_pixel(120, i, 0); 
      if(pixel > threshold){
          bitValue = 1;
      }
         else {
             bitValue = 0;
         }
      if(bitValue == 1){
          numRedPixels++;
      }else {
          numRedPixels = numRedPixels;
      }
      
    error+=(i*bitValue);
  }
  if(numRedPixels > 150) checkRed = true;
  
  return checkRed;
}

int main(){
	init(); 
  //bool checkRed = false;
  
  //openGate();
  int previousError = getError();
  while(true){
    int error = getError();
    printf("Value: %d \n", error); 
    getScale(error, previousError);
    previousError = error;
 
  }
        
 // for(int i=0; i<100; i++){
  // printf("Reached first red patch \n"); 
 // }
 stop(1); 
 stop(2); 
 return 0;
}

