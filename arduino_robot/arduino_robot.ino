#include <ESP32Servo.h>
//#define leftShoulder 15
Servo leftShoulder;  // create servo object to control a servo
Servo rightShoulder;
Servo rightElbow;
Servo leftElbow;
#define BAUD_RATE 650000

void setup() {
  Serial.begin(BAUD_RATE);
  leftShoulder.attach(13);  // attaches the servo on pin 23
  rightShoulder.attach(15);
  rightElbow.attach(12);
  leftElbow.attach(14);

//delay(3000);

}

int genre;
int selection; 
int tempo;

void loop() {
  //test motors 
    // leftShoulder.write(0);
    // delay (500);
    // leftShoulder.write(180);
    // delay(500);
    arabesque(500);
    delay(1000);

// if(Serial.available()){
//     Serial.println("the serial is available!");
//     genre = int(Serial.read()); //note whether sending genre or tempo first
//     tempo = int(Serial.read());
//     Serial.println("genre = ");
//     Serial.println(genre);
//     Serial.println("tempo = ");
//     Serial.println(tempo);
// if (genre == 2){
//   arabesque(tempo);
// }
}

//for actual selection
  // if(Serial.available()){
  //   selection = random(0,3)
  //   genre = Serial.read(); //note whether sending genre or tempo first
  //   tempo = Serial.read();
  //   if (genre == 1){ //genre one selections
  //     if (selection == 0){
        
  //     }
  //     if (selection == 1){
        
  //     }
  //     if (selection == 2){
        
  //     }
  //   }
  //   if (genre == 4){ //genre four selections
  //     if (selection == 0){
        
  //     }
  //     if (selection == 1){
        
  //     }
  //     if (selection == 2){
  //       robot(tempo);
  //     }
  //   }
  //   if (genre == 5){ //genre five selections
  //     if (selection == 0){
        
  //     }
  //     if (selection == 1){
        
  //     }
  //     if (selection == 2){
  //       runningMan(tempo);
  //     }
  //   }
  //   if (genre == 7){ //genre 7 selections
  //     if (selection == 0){
  //     }
  //     if (selection == 1){
  //        pumpArms(tempo);
  //     }
  //     if (selection == 2){

  //     }
  //   }
  // }

void runningMan(int speed){
    leftShoulder.write(60);
    rightShoulder.write(150); 
    rightElbow.write(90);    
    delay(speed);
    leftShoulder.write(120);
    rightShoulder.write(90);   
    rightElbow.write(160); 
    delay(speed);
    // leftShoulder.write(60);
    // rightShoulder.write(90); 
    // rightElbow.write(150);
    // delay(speed);

}


void pumpArms(int speed){
    leftShoulder.write(0);
    rightShoulder.write(180); 
    rightElbow.write(180);    
    delay(speed);
    leftShoulder.write(60);
    rightShoulder.write(130);    
    delay(speed);
}

void arabesque(int speed){
    leftShoulder.write(180);
    rightShoulder.write(180); 
    rightElbow.write(90);    
    delay(speed);
    leftShoulder.write(90);
    rightShoulder.write(120);    
    delay(speed);
}

void robot(int speed){
    rightShoulder.write(50); 
    leftShoulder.write(90); 
    for (int x = 3; x>=0;x--){
      rightElbow.write(180); 
      delay(300);
      rightElbow.write(90); 
      delay(300);
    }  
    delay(speed);
    rightShoulder.write(120); 
    leftShoulder.write(140); 
    for (int x = 3; x>=0;x--){
      leftElbow.write(0); 
      delay(200);
      leftElbow.write(90); 
      delay(200);
    }      
    delay(speed);

}
