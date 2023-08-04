/*A basic 4 channel transmitter using the nRF24L01 module.*/
/* Like, share and subscribe, ELECTRONOOBS */
/* http://www.youtube/c/electronoobs */

/* First we include the libraries. Download it from 
   my webpage if you donw have the NRF24 library */
 
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

/*Create a unique pipe out. The receiver has to 
  wear the same unique code*/
  
const uint64_t pipeOut = 0xE8E8F0F0E1LL; //IMPORTANT: The same as in the receiver

RF24 radio(9, 10); // select  CSN  pin

struct MyData {
  byte throttle;
  byte yaw;
  byte pitch;
  byte roll;
  byte AUX1;
  byte AUX2;
  
};

MyData data;

void resetData() 
{
  //This are the start values of each channal
  // Throttle is 0 in order to stop the motors
  //127 is the middle value of the 10ADC.
    
  data.throttle = 0;
  data.yaw = 127;
  data.pitch = 127;
  data.roll = 127;
  data.AUX1 = 0;
  data.AUX2 = 0;

}


void setup()
{
  //Start everything up
  radio.begin();
  radio.setAutoAck(false);
  radio.setDataRate(RF24_250KBPS);
  radio.openWritingPipe(pipeOut);
  //pinMode(7, INPUT );
  //pinMode(5, INPUT);
}


void loop()
{
  // The calibration numbers used here should be measured 
  // for your joysticks till they send the correct values.                                     //Ammar Changes here
  data.throttle = map( analogRead(A0), 900, 100, 0, 255 );                    //I changed the joystick Callibration values of all the data 
  data.yaw      = map( analogRead(A1),  900, 100, 0, 255 );                  // to make is more optimised for my analog joysticks
  data.pitch    = map( analogRead(A2), 900, 100, 0, 255 );
  data.roll     = map( analogRead(A3), 900, 100, 0, 255 );
  data.AUX1 = digitalRead(7);
  data.AUX2 = digitalRead(5);

  radio.write(&data, sizeof(MyData));
}
