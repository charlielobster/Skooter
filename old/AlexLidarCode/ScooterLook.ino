// LIDAR and Servo Control by Alexandros Achilleas Gloor, Last Updated November 4th, 2019

//DISCUSSME should we make a forwardLook where LIDAR takes one RBC measurement, 99 without and only looks forward for obstacles?

//---------------------------Globals----------------------------//

//LIDAR Globals
#include <Wire.h>
#include <LIDARLite.h>
LIDARLite eyeScooter;
int cal_cnt = 0;
int dist; // in centimeters

//Servo Pan Globals
#include <Servo.h>
Servo servoPan;  // create servo object to control a servo
int anglePan = 0;    // variable to store the servo position angle
//Servo Tilt Globals
Servo servoTilt;
int angleTilt = 0;

//Interest Point
int angleInterest = 45;


void setup() {

  //LIDAR Setup
  // Initialize serial connection to display distance readings, example gives 115200
  Serial.begin(9600);
  // Set to default config (0) and I2C to 400 kHz (true)
  eyeScooter.begin(0, true);
  // 0=default, 1=short,hispd, 2=default,hispd,loacc, 3=maxrange, 4=hisensitivity, 5=losensitivity
  //FIXME is this unecessary? --> eyeScooter.configure(0);

  //Servo Setup
  // attaches 3 to the servo object
  servoPan.attach(3);
  servoTilt.attach(5);

  lookPan();
  lookTilt(angleInterest);

}

//-------------------------LIDAR Control--------------------------//

int LIDAR() {

  // Print measurement with receiver bias correction (RBC) in cm
  Serial.println(eyeScooter.distance());
  delay(5);

  // Take 99 measurements without RBC in cm
  //for(int i = 0; i < 9; i++)
  //{
  //  Serial.println(eyeScooter.distance(false));
  //  delay(5);
  //}

  //DISCUSSME Turn off after use for safety? Implement off switch?

}

//--------------------------Servo Pan----------------------------//

int lookPan() {

  // sweeps the full 180 degree angle in 1 degree steps
  for (anglePan = 0; anglePan <= 180; anglePan++) {
    // tell servo to go to position in variable 'anglePan'
    servoPan.write(anglePan);
    LIDAR();

    //FIXME add a step to get LIDAR reading

    //FIXME add output of LIDAR reading as well as angle (could report angle from forward-facing origin or from leftmost origin)



  }

  // reset to forward-looking
  servoPan.write(90);

}

//--------------------------Servo Tilt----------------------------//

int lookTilt(int* angleInterest) {

  // scooter first pans to angleInterest
  servoPan.write(angleInterest);

  // SHOULD NEVER EXCEED 90 DEGREES IN TILT
  for (angleTilt = 0; angleTilt <= 90; angleTilt++) {
    // tell servo to go to position in variable 'angleTilt'
    servoTilt.write(angleTilt);
    LIDAR();
  }

  //reset to flat, 36 degrees, facing forward
  servoTilt.write(36);
  servoPan.write(90);

}

//---------------------------3D Scan==----------------------------//

int lookScan() {

  // scooter first pans to lower left corner
  servoPan.write(0);
  servoTilt.write(0);

  for (angleTilt = 0; angleTilt <= 90; angleTilt++) {
    for (anglePan = 0; anglePan <= 180; anglePan++) {
      servoPan.write(anglePan);
      LIDAR();
    }
    angleTilt++;
    servoTilt.write(angleTilt);
    for (anglePan = 180; anglePan >= 0; anglePan--) {
      servoPan.write(anglePan);
      LIDAR();
    }
  }

  //reset to flat, 36 degrees, facing forward
  servoTilt.write(36);
  servoPan.write(90);

}

//-----------------------------LOOP--------------------------------//

void loop() {

  //FIXME constantly check for distance in front of Scooter

  //limit determines the distance at which Scooter will stop to look around
  int limit = 500;
  if (dist <= limit) {
    //lookPan();
  }



}
