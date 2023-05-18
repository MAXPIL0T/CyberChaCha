#include <ESP32Servo.h>
#include <Adafruit_SSD1306.h>
// for faces
#include "aggressive_face.h"
#include "closed_smile.h"
#include "open_mouth.h"
#include "straight_mouth.h"

#define BAUD_RATE 650000
#define BUTTON 0
typedef void (*DanceFunction)(double speed); // function for a dance move

Servo leftShoulder; // create servo objects to control body parts
Servo rightShoulder;
Servo leftElbow;
Servo rightElbow;

Servo leftLeg;
Servo rightLeg;
Servo leftKnee;
Servo rightKnee;

Servo body;
Servo head;

Adafruit_SSD1306 lcd(128, 64); // display object

int genre = 6;
int selection = 0; // random selection int
double delayTime = 500; // milliseconds between each "beat" of the audio
unsigned long buttonTimeout = 0;
byte prevState = 1;
int on = 1;

void setup()
{
  pinMode(BUTTON, INPUT_PULLUP);

  Serial.begin(BAUD_RATE);
  leftShoulder.attach(15);
  rightShoulder.attach(13);
  rightElbow.attach(12);
  leftElbow.attach(14);
  leftLeg.attach(27);
  rightLeg.attach(23);
  leftKnee.attach(32);
  rightKnee.attach(5);
  body.attach(18);
  head.attach(19);

  resetToNormal();

  lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  lcd.clearDisplay();
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2);
  lcd.clearDisplay();
  closedSmile();
}

// Move all motors to the specified position
void resetTo(int degrees) {
  leftShoulder.write(degrees);
  rightShoulder.write(degrees);
  rightElbow.write(degrees);
  leftElbow.write(degrees);
  leftLeg.write(degrees);
  rightLeg.write(degrees);
  leftKnee.write(degrees);
  rightKnee.write(degrees);
  body.write(degrees);
  head.write(degrees);  
}

// Move all motors to a default position
void resetToNormal() {
  leftShoulder.write(20);
  rightShoulder.write(160);
  rightElbow.write(90);
  leftElbow.write(90);
  leftLeg.write(90);
  rightLeg.write(95);
  leftKnee.write(90);
  rightKnee.write(90);
  body.write(90);
  head.write(90); 
}

//----------------------Faces-----------------------
void closedSmile() {
  lcd.clearDisplay();
  lcd.drawBitmap(0, 0, bitmap_closed, 128, 64, 1);
  lcd.display();
}
void openMouth() { // and smiling
  lcd.clearDisplay();
  lcd.drawBitmap(0, 0, bitmap_open, 128, 64, 1);
  lcd.display();
}
void straightMouth() {
  lcd.clearDisplay();
  lcd.drawBitmap(0, 0, bitmap_straight, 128, 64, 1);
  lcd.display();
}
void aggressiveFace() {
  lcd.clearDisplay();
  lcd.drawBitmap(0, 0, bitmap_aggressive, 128, 64, 1);
  lcd.display();
}

//----------------------Dance Moves-----------------------
  // 1: blues
void slowDrag(double speed) {
  closedSmile();
  leftLeg.write(90);
  leftKnee.write(90);
  rightLeg.write(95);
  rightKnee.write(90);
  head.write(90);

  rightElbow.write(50);
  leftShoulder.write(90);
  leftElbow.write(120);
  // sway from side to side slowly
  for (int i = 120; i >= 60; i--) {
    body.write(i);
    delay(2 * speed / 60);
  }
  for (int i = 60; i <= 120; i++) {
    body.write(i);
    delay(2 * speed / 60);
  }
  delay(speed);
}
void texasShuffle(double speed) {
  openMouth();
  body.write(90);
  head.write(90);
  // open legs to the right
  leftLeg.write(45);
  leftKnee.write(45);
  rightLeg.write(45);
  rightKnee.write(45);
  // arms up open to the left
  leftShoulder.write(0);
  leftElbow.write(45);
  rightShoulder.write(0);
  rightElbow.write(45);
  // delay
  delay(speed / 2);
  // close legs at middle
  leftLeg.write(90);
  leftKnee.write(90);
  rightLeg.write(95);
  rightKnee.write(90);
  // bring arms closer to center
  leftShoulder.write(20);
  leftElbow.write(50);
  rightShoulder.write(180);
  rightElbow.write(90);
  // delay
  delay(speed / 2);
  // open legs to the left
  leftLeg.write(135);
  leftKnee.write(135);
  rightLeg.write(135);
  rightKnee.write(135);
  // arms up and open to the right
  leftShoulder.write(135);
  leftElbow.write(135);
  rightShoulder.write(180);
  rightElbow.write(45);
}
void savoyWalk(double speed) {
  closedSmile();
  head.write(90);
  body.write(90);
  // one arm up, holding hand out
  rightShoulder.write(0);
  rightElbow.write(40);
  // one arm extended and curled
  leftShoulder.write(110);
  leftElbow.write(120);
  // left leg out, right leg back
  leftLeg.write(135);
  leftKnee.write(135);
  rightLeg.write(135);
  rightKnee.write(135);
  // delay
  delay(speed);
  // right leg out, left leg back
  leftLeg.write(45);
  leftKnee.write(45);
  rightLeg.write(45);
  rightKnee.write(45);
  // delay
  delay(speed);
  // left leg out, right leg back
  leftLeg.write(135);
  leftKnee.write(135);
  rightLeg.write(135);
  rightKnee.write(135);
  // much shorter delay
  delay(speed / 2);
  // right leg out, left leg back
  leftLeg.write(45);
  leftKnee.write(45);
  rightLeg.write(45);
  rightKnee.write(45);
  // left leg out, right leg back
  leftLeg.write(135);
  leftKnee.write(135);
  rightLeg.write(135);
  rightKnee.write(135);
  // much shorter delay
  delay(speed / 2);
  // right leg out, left leg back
  leftLeg.write(45);
  leftKnee.write(45);
  rightLeg.write(45);
  rightKnee.write(45);
  delay(speed);
}
  // 2: classical
void pirouette(double speed) {
  closedSmile();
  head.write(90);
  body.write(90);
  // both arms up and clasped above head
  leftShoulder.write(180);
  leftElbow.write(80);
  rightShoulder.write(0);
  rightElbow.write(90);
  // one leg straight down
  rightLeg.write(95);
  rightKnee.write(90);
  // other leg at right angle and foot touching other leg
  leftLeg.write(180);
  leftKnee.write(0);
  delay(speed);
}
void plie(double speed) {
  closedSmile();
  head.write(110);
  body.write(90);
  rightShoulder.write(50);
  rightElbow.write(90);
  leftShoulder.write(130);
  leftElbow.write(80);
  // bend both legs to make a diamond shape
  leftLeg.write(135);
  leftKnee.write(0);
  rightLeg.write(135);
  rightKnee.write(0);
  delay(speed);
}
void arabesque(double speed)
{
  closedSmile();
  //right leg up position
  leftShoulder.write(180);
  rightShoulder.write(180);
  rightElbow.write(90);
  leftElbow.write(90);
  rightLeg.write(180);
  leftLeg.write(90);
  rightKnee.write(90);
  leftKnee.write(90);
  delay(speed);
  //down position
  leftShoulder.write(20);
  rightShoulder.write(160);
  rightLeg.write(95);
  delay(speed);
  //left leg up position
  leftShoulder.write(0);
  rightShoulder.write(0);
  rightLeg.write(95);
  leftLeg.write(0);
  delay(speed);
  //down position
  leftShoulder.write(90);
  rightShoulder.write(90);
  leftLeg.write(90);
  delay(speed);
}
  // 3: country
void watermelonCrawl(double speed) {
  openMouth();
  body.write(90);
  rightShoulder.write(20);
  rightElbow.write(100);
  leftShoulder.write(100);
  leftElbow.write(90);
  // left leg out a bit
  head.write(70);
  rightLeg.write(95);
  rightKnee.write(90);
  leftLeg.write(100);
  leftKnee.write(90);
  // left leg fully kick out
  delay(500);
  leftLeg.write(135);
  delay(500);
  // bring left leg back in
  leftLeg.write(90);
  delay(speed);
  // right leg out a bit
  head.write(130);
  rightLeg.write(80);
  rightKnee.write(90);
  leftLeg.write(90);
  leftKnee.write(90);
  // right leg fully kick out
  delay(500);
  rightLeg.write(45);
  delay(500);
  // bring right leg back in
  rightLeg.write(95);
  delay(speed);
  // "clap" hands
  leftShoulder.write(110);
  rightShoulder.write(10);
  delay(speed);
}
void cowboyShuffle(double speed) {
  openMouth();
  head.write(90);
  leftLeg.write(90);
  leftKnee.write(90);
  rightLeg.write(95);
  rightKnee.write(90);
  // clap
  rightShoulder.write(20);
  rightElbow.write(100);
  leftShoulder.write(100);
  leftElbow.write(90);
  delay(500);
  leftShoulder.write(110);
  rightShoulder.write(10);
  // sway left then right
  for (int i = 90; i <= 120; i++) {
    body.write(i);
    delay(speed / 120);
  }
  for (int i = 120; i >= 60; i--) {
    body.write(i);
    delay(speed / 120);
  }
  for (int i = 60; i <= 90; i++) {
    body.write(i);
    delay(speed / 120);
  }
  delay(500);
  // clap
  leftShoulder.write(110);
  rightShoulder.write(10);
  delay(speed);
  // sway right then left
  for (int i = 90; i >= 60; i--) {
    body.write(i);
    delay(speed / 120);
  }
  for (int i = 60; i <= 120; i++) {
    body.write(i);
    delay(speed / 120);
  }
  for (int i = 120; i >= 90; i--) {
    body.write(i);
    delay(speed / 120);
  }
  delay(speed);
}
void tushPush(double speed) {
  openMouth();
  leftLeg.write(90);
  leftKnee.write(90);
  rightLeg.write(95);
  rightKnee.write(90);
  head.write(90);
  // move arms to put hands on hips
  leftShoulder.write(0);
  leftElbow.write(150);
  rightShoulder.write(180);
  rightElbow.write(40);
  delay(500);
  // sway side to side in a groovy country way
  for (int i = 45; i <= 135; i++) {
    body.write(i);
    delay(speed / 90);
  }
  delay(speed);
}
  // 4: disco
void ymca(double speed){
  // both arms out at 45 degrees outstretched and two legs straight down
  // keep legs straight, but move arms to make an "M" shape above head
  // move one arm down (but still curled) to make "C" shape
  // keep legs straight, but move arms to make an "M" shape above head
  rightShoulder.write(160);
  rightElbow.write(90);
  leftShoulder.write(30);
  leftElbow.write(90);
  leftLeg.write(90);
  rightLeg.write(95);
  delay(speed);

}
void discoFinger(double speed) {
  closedSmile();
  // move one arm up and down, delay for funkyness
  rightShoulder.write(160);
  rightElbow.write(0);
  delay(speed);
  rightShoulder.write(90);
  delay(speed);
  rightShoulder.write(160);
  delay(speed);
}
void robot(double speed)
{
  straightMouth();
  rightShoulder.write(30);
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
void wave(double speed) {
  closedSmile();  
  // start out with both arms extended straight out
  // make left arm an L shape
  // make left arm an upside down L shape
  // make left arm straight and right arm upside down L shape
  // make right arm straight
  // make right arm L shape
  leftShoulder.write(180);
  leftElbow.write(90);
  delay(speed);
  leftShoulder.write(90);
  leftElbow.write(180);
  delay(speed);
  rightShoulder.write(90);
  rightElbow.write(0);
  delay(speed);
  rightShoulder.write(0);
  rightElbow.write(90);
  leftShoulder.write(0);
  leftElbow.write(90);  
  delay(speed);
  rightShoulder.write(90);
  rightElbow.write(0);
  delay(speed);
}
void popChest(double speed) {
  aggressiveFace();
  //move shoulders slightly back and forth rapidly
  leftShoulder.write(150);
  rightShoulder.write(30);
  delay(speed);
  leftShoulder.write(90);
  rightShoulder.write(90);
  delay(speed);
}
void runningMan(double speed)
{
  aggressiveFace();
  leftLeg.write(90);
  rightLeg.write(95);
  leftKnee.write(90);
  rightKnee.write(90);
  leftShoulder.write(150);
  rightShoulder.write(30);
  rightElbow.write(90);
  leftElbow.write(90);
  delay(speed);
  leftShoulder.write(0);
  rightShoulder.write(180);
  rightElbow.write(0);
  leftElbow.write(180);
  leftLeg.write(160);
  leftKnee.write(20);
  delay(speed);
  // leftShoulder.write(60);
  // rightShoulder.write(90);
  // rightElbow.write(150);
  // delay(speed);
}
  // 6: jazz
void jazzKick(double speed) {
  closedSmile();
  leftLeg.write(90);
  rightLeg.write(95);
  leftShoulder.write(90);
  rightShoulder.write(90);
  leftElbow.write(90);
  rightElbow.write(90);
  delay(speed);
  leftLeg.write(180);
  delay(speed);
  leftLeg.write(90);
  rightLeg.write(0);
  delay(speed);
}
  // 7: metal
void bobHead(double speed) {
  openMouth();
  head.write(0);
  delay(speed);
  head.write(180);
  delay(speed);
}
void pumpLegs(double speed) {
  openMouth();
  leftLeg.write(20);
  rightLeg.write(160);
  rightKnee.write(160);
  leftKnee.write(20);
  delay(speed);
  leftLeg.write(60);
  rightLeg.write(130);
  delay(speed);
}
void pumpArms(double speed)
{
  openMouth();
  leftShoulder.write(90);
  rightShoulder.write(90);
  rightElbow.write(0);
  leftElbow.write(180);
  delay(speed);
  leftShoulder.write(180);
  rightShoulder.write(0);
  rightElbow.write(90);
  leftElbow.write(90);
  delay(speed);
}
  // 8: pop
void dab(double speed) {
  aggressiveFace();
  body.write(110);
  head.write(50);
  leftShoulder.write(180);
  leftElbow.write(180);
  delay(speed * 2);
}
void bodyRoll(double speed) {
  openMouth();
  int initialPos = 90;
  int upper_bounds = 120;
  int lower_bounds = 60;
  int step = 5;
  int time_per_step = speed * 2 / 5;
  while (initialPos < 120) {
    initialPos += step;
    body.write(initialPos);
    delay(time_per_step);
  }
  while(initialPos > 60) {
    initialPos -= step;
    body.write(initialPos);
    delay(time_per_step);
  }
  while(initialPos < 90) {
    initialPos += step;
    body.write(initialPos);
    delay(time_per_step);
  }
}
void floss(double speed) {
  openMouth();  
  // arms are straight, left arm is back and right arm is forward, alternate between these
  leftShoulder.write(150);
  rightShoulder.write(30);
  head.write(30);
  delay(300);
  leftShoulder.write(30);
  rightShoulder.write(150);
  head.write(150);
}
  // 9: reggae
void flairy(double speed) {
  openMouth();
  // fling all arms and legs backwards
  // fling all arms and legs forwards
  leftShoulder.write(180);
  rightShoulder.write(0);
  rightElbow.write(0);
  rightElbow.write(180);
  leftLeg.write(0);
  rightLeg.write(180);
  delay(speed);
  leftShoulder.write(0);
  rightShoulder.write(180);
  leftLeg.write(180);
  rightLeg.write(0);
  rightElbow.write(180);
  rightElbow.write(0);
}
void lebehLebeh(double speed) {
  openMouth();
  body.write(120);
  rightShoulder.write(180);
  leftShoulder.write(0);
  delay(speed);
  body.write(60);
  rightShoulder.write(0);
  leftShoulder.write(180);
}
void gennaBounce(double speed) {
  aggressiveFace();
  leftShoulder.write(180);
  rightShoulder.write(0);
  delay(300);
  leftShoulder.write(40);
  rightShoulder.write(140);
  delay(300);
  leftLeg.write(180);
  leftLeg.write(90);
  delay(300);
  rightLeg.write(0);
  delay(0);
}
  // 10: rock
      // everything's the same as for metal
//----------------------END Dance Moves-----------------------

// all the dances
DanceFunction bluesDances[] = {slowDrag, texasShuffle, savoyWalk}; // 1
DanceFunction classicalDances[] = {pirouette, plie, arabesque}; // 2
DanceFunction countryDances[] = {watermelonCrawl, cowboyShuffle, tushPush}; // 3
DanceFunction discoDances[] = {ymca, discoFinger, robot}; // 4
DanceFunction hiphopDances[] = {wave, popChest, runningMan}; // 5
DanceFunction jazzDances[] = {jazzKick, jazzKick, jazzKick}; // 6
DanceFunction metalDances[] = {bobHead, pumpLegs, pumpArms}; // 7
DanceFunction popDances[] = {dab, bodyRoll, floss}; // 8
DanceFunction reggaeDances[] = {flairy, lebehLebeh, gennaBounce}; // 9
DanceFunction rockDances[] = {bobHead, pumpLegs, pumpArms}; // 10

void loop()
{
  if (millis() > buttonTimeout) {
    byte curState = digitalRead(BUTTON);
    if (curState == 0 && prevState == 1) {
          on = !on;
    }
    prevState = curState;
    buttonTimeout = millis() + 50;
  }
  if (on) {
    resetToNormal();
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
    if (Serial.available())
    {
      selection = random(0, 3);
      genre = int(Serial.read());
      delayTime = 1.0 / (int(Serial.read()) * (1 / 60000.0)); // milliseconds per beat
    }
  }
}