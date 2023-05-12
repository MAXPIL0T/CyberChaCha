#include <ESP32Servo.h>

Servo leftShoulder; // create servo object to control a servo
Servo rightShoulder;
Servo rightElbow;
Servo leftElbow;
#define BAUD_RATE 115200

typedef void (*DanceFunction)(double tempo);

void setup()
{
  Serial.begin(BAUD_RATE);
  leftShoulder.attach(13); // attaches the servo on pin 23
  rightShoulder.attach(15);
  rightElbow.attach(12);
  leftElbow.attach(14);
}

int genre;
int selection;
double tempo;

//----------------------Dance Moves-----------------------

void runningMan(double speed)
{
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

void pumpArms(double speed)
{
  leftShoulder.write(0);
  rightShoulder.write(180);
  rightElbow.write(180);
  delay(speed);
  leftShoulder.write(60);
  rightShoulder.write(130);
  delay(speed);
}

void arabesque(double speed)
{
  Serial.println("in arabesque");
  // leftShoulder.write(180);
  // rightShoulder.write(180);
  // rightElbow.write(90);
  // delay(speed);
  // leftShoulder.write(90);
  // rightShoulder.write(120);
  // delay(speed);
}

void testFunc1(double speed)
{
  Serial.println("in testFunc1");
}

void testFunc2(double speed)
{
  Serial.println("in testFunc2");
}

void robot(double speed)
{
  rightShoulder.write(50);
  leftShoulder.write(90);
  for (int x = 3; x >= 0; x--)
  {
    rightElbow.write(180);
    delay(300);
    rightElbow.write(90);
    delay(300);
  }
  delay(speed);
  rightShoulder.write(120);
  leftShoulder.write(140);
  for (int x = 3; x >= 0; x--)
  {
    leftElbow.write(0);
    delay(200);
    leftElbow.write(90);
    delay(200);
  }
  delay(speed);
}

// all the dances
DanceFunction bluesDances[] = {};
DanceFunction classicalDances[] = {arabesque, testFunc1, testFunc2};
DanceFunction countryDances[] = {};
DanceFunction discoDances[] = {robot};
DanceFunction hiphopDances[] = {runningMan};
DanceFunction jazzDances[] = {};
DanceFunction metalDances[] = {pumpArms};
DanceFunction popDances[] = {};
DanceFunction reggaeDances[] = {};
DanceFunction rockDances[] = {pumpArms};

void loop()
{
  // test motors
  //  leftShoulder.write(0);
  //  delay (500);
  //  leftShoulder.write(180);
  //  delay(500);
  //  arabesque(500);
  //  delay(1000);

  if (Serial.available())
  {
    selection = random(0, 3);
    genre = int(Serial.read());
    tempo = int(Serial.read());
    switch (genre)
    {
    case 1: // blues
      bluesDances[selection](tempo);
      break;
    case 2: // classical
      classicalDances[selection](tempo);
      break;
    case 3: // country
      countryDances[selection](tempo);
      break;
    case 4: // disco
      discoDances[selection](tempo);
      break;
    case 5: // hiphop
      hiphopDances[selection](tempo);
      break;
    case 6: // jazz
      jazzDances[selection](tempo);
      break;
    case 7: // metal
      metalDances[selection](tempo);
      break;
    case 8: // pop
      popDances[selection](tempo);
      break;
    case 9: // reggae
      reggaeDances[selection](tempo);
      break;
    default: // rock
      rockDances[selection](tempo);
      break;
    }
  }
}