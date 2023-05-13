#include <ESP32Servo.h>
#define BAUD_RATE 115200
typedef void (*DanceFunction)(double speed);

Servo leftShoulder; // create servo object to control a servo
Servo rightShoulder;
Servo rightElbow;
Servo leftElbow;
Servo leftLeg;
Servo rightLeg;
Servo leftKnee;
Servo rightKnee;
Servo body;
Servo head;

int genre = 1;
int selection = 0;
double delayTime = 500;

// left upper arm add to move forward

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
void slowDrag(double speed) {
  // hold arms out
  // sway from side to side slowly
}
void texasShuffle(double speed) {
  // open legs to the right
  // arms up open to the left
  // delay
  // close legs at middle
  // bring arms closer to center
  // delay
  // open legs to the left
  // arms up and open to the right
}
void savoyWalk(double speed) {
  // one arm up, holding hand out
  // one arm extended and curled
  // left leg out, right leg back
  // delay
  // right leg out, left leg back
  // delay
  // left leg out, right leg back
  // much shorter delay
  // right leg out, left leg back
  // left leg out, right leg back
  // much shorter delay
  // right leg out, left leg back
}
  // 2: classical
void pirouette(double speed) {
  // both arms up and clasped above head
  // one leg straight down
  // other leg at right angle and foot touching other leg
}
void plie(double speed) {
  // bend both legs to make a diamond shape
}
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
void watermelonCrawl(double speed) {
  // left leg out a bit
  // left leg fully kick out
  // bring left leg back in
  // right leg out a bit
  // right leg fully kick out
  // bring right leg back in
  // "clap" hands
}
void cowboyShuffle(double speed) {
  // clap
  // sway left then right
  // clap
  // sway right then left
}
void tushPush(double speed) {
  // move arms to put hands on hips
  // sway side to side in a groovy country way
}
  // 4: disco
void ymca(double speed){
  // both arms out at 45 degrees outstretched and two legs straight down
  // keep legs straight, but move arms to make an "M" shape above head
  // move one arm down (but still curled) to make "C" shape
  // keep legs straight, but move arms to make an "M" shape above head
}
void discoFinger(double speed) {
  // move one arm up and down, delay for funkyness
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
  // 5: hiphop
void wave(double speed) {
  // start out with both arms extended straight out
  // make left arm an L shape
  // make left arm an upside down L shape
  // make left arm straight and right arm upside down L shape
  // make right arm straight
  // make right arm L shape
}
void popChest(double speed) {
  //move shoulders slightly back and forth rapidly
}
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
void jazzKick(double speed) {
  // arms sticking straight out to the audience
  // right leg up at 90 degrees
  // left leg up at 90 degrees
}
  // 7: metal
void bobHead(double speed) {

}
void pumpLegs(double speed) {
  // same as pumpArms but with legs
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
  // 8: pop
void dab(double speed) {
  // lean to side
  // move head to look to side at one arm
  // move arm up and bend at elbow
}
void bodyRoll(double speed) {
  // sway sensually side to side at a medium tempo
}
void floss(double speed) {
  // arms are straight, left arm is back and right arm is forward, alternate between these
}
  // 9: reggae
void flairy(double speed) {
  // fling all arms and legs backwards
  // fling all arms and legs forwards
}
void lebehLebeh(double speed) {
  // sway body to one side
  // on that side, raise arm and raise leg
  // sway body to another side and do the same thing
}
void gennaBounce(double speed) {
  // arms up and legs down
  // arms go down, left leg up
  // back to initial position
  // arms go down, right leg up
}
  // 10: rock
      // everything's the same as for metal
//----------------------END Dance Moves-----------------------

// all the dances
DanceFunction bluesDances[] = {slowDrag, texasShuffle, savoyWalk}; // 1
DanceFunction classicalDances[] = {pirouette, plie, abaresque}; // 2
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
  // test motors
  //  leftShoulder.write(0);
  //  delay (500);
  //  leftShoulder.write(180);
  //  delay(500);
  //  arabesque(500);
  //  delay(1000);

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