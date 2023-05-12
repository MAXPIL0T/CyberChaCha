#include <ESP32Servo.h>
#define BAUD_RATE 115200
typedef void (*DanceFunction)(double tempo);

Servo leftShoulder; // create servo object to control a servo
Servo rightShoulder;
Servo rightElbow;
Servo leftElbow;

int genre;
int selection;
double tempo;

void setup()
{
  Serial.begin(BAUD_RATE);
  leftShoulder.attach(13); // attaches the servo on pin 23
  rightShoulder.attach(15);
  rightElbow.attach(12);
  leftElbow.attach(14);
}

//----------------------Dance Moves-----------------------
  // 1: blues
  // 2: classical
void arabesque(double speed)
{
  leftShoulder.write(180);
  rightShoulder.write(180);
  rightElbow.write(90);
  delay(speed);
  leftShoulder.write(90);
  rightShoulder.write(120);
  delay(speed);
}
  // 3: country
  // 4: disco
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
  // 5: hiphop
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
  // 6: jazz
  // 7: metal
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
  // 8: pop
  // 9: reggae
  // 10: rock
//----------------------END Dance Moves-----------------------

// all the dances
DanceFunction bluesDances[] = {}; // 1
DanceFunction classicalDances[] = {arabesque}; // 2
DanceFunction countryDances[] = {}; // 3
DanceFunction discoDances[] = {robot}; // 4
DanceFunction hiphopDances[] = {runningMan}; // 5
DanceFunction jazzDances[] = {}; // 6
DanceFunction metalDances[] = {pumpArms}; // 7
DanceFunction popDances[] = {}; // 8
DanceFunction reggaeDances[] = {}; // 9
DanceFunction rockDances[] = {pumpArms}; // 10

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
    delayTime = 1.0 / (int(Serial.read()) * (1 / 60000.0)); // milliseconds per beat
    switch (genre)
    {
    case 1: // blues
      bluesDances[selection](delayTime);
      break;
    case 2: // classical
      classicalDances[selection](delayTime);
      break;
    case 3: // country
      countryDances[selection](delayTime);
      break;
    case 4: // disco
      discoDances[selection](delayTime);
      break;
    case 5: // hiphop
      hiphopDances[selection](delayTime);
      break;
    case 6: // jazz
      jazzDances[selection](delayTime);
      break;
    case 7: // metal
      metalDances[selection](delayTime);
      break;
    case 8: // pop
      popDances[selection](delayTime);
      break;
    case 9: // reggae
      reggaeDances[selection](delayTime);
      break;
    default: // rock
      rockDances[selection](delayTime);
      break;
    }
  }
}