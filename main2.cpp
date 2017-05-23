#include <stdio.h>
#include <time.h>
#include "E101.h"

int main(){
  boolean checkRed = false;
  
  openGate();
  int previousError = getError();
  while(!atRed(checkRed)){
    int error = getError();
    getScale(error, previousError);
    previousError = error;
  }
        
  for(int i=0; i<100; i++){
   printf("Reached first red patch \n"); 
  }
  return 0;
}

//Done method
void openGate(){
  connect_to_server("130.195.6.196", 1024);
  send_to_server("Please0");
  char response[24];
  recieve_from_server(reponse);
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
  int error = 0;
  int bitValue = 0;
  int threshold = 127;
  int numWhitePixels = 0;
  
  take_picture();
  for(int i=-160; i<160; i++){
      if(get_pixel(120, i, 3) > threshold){
          bitValue = 1;
      }else {
          bitValue = 0;
      }
      
      if(numWhitePixels = (bitValue==1)){
        numWhitePixels++;
      }
      else {
          numWhitePixels;                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
      }
      
    error+=(i*bitValue);
  }
  if(numWhitePixels>0) {
      error=error/numWhitePixels;
  }
  else {
      error = INT_MAX;
  }
  
  printf("ERROR: %d", error);
  return error;
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
  move(error, scale);
}

//Working
void move(int error, int scale){
  int speedLeft = 75;
  int speedRight = 75;
  if(scale < 0) scale*= -1;
  if(scale > 254) scale = 254;
  
  if(error == INT_MAX){
    printf("GOING BACKWARDS");
    speedLeft = -254;
    speedRight = -254
  }else if(error == 0){
    printf("GOING FORWARDS");
    speedLeft = 55;
    speedRight = 55;
  }else if(error < 0){
    printf("GOING RIGHT");
    speedLeft+=scale;
    speedLeft-=scale;
  }else if(error > 0){
    printf("GOING LEFT");
    speedLeft+=scale;
    speedLeft-=scale;
  }
  set_motor(1, speedLeft);
  set_motor(2, speedRight);
  Sleep1(0, 5000);
  stop(1);
  stop(2);
}


boolean atRed(boolean checkRed){
  int error = 0;
  int bitValue = 0;
  int threshold = 127;
  int numRedPixels = 0;
  
  take_picture();
  for(int i=-160; i<160; i++){
      if((get_pixel(120, i, 0) > threshold){
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
