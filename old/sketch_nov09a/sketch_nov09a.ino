#include <Sabertooth.h>

/*****************************************************
 * DIP Switches as per the wized:
 * - NiMh Battery
 * - TTL RS232
 * - Simplified Serial Mode
 * - Just one Sabertooth conected
 * - 9600 baudrate
 *
 * Pin 1 - ON
 * Pin 2 - OFF
 * Pin 3 - ON
 * Pin 4 - OFF
 * Pin 5 - ON
 * Pin 6 - ON
 ****************************************************/

// Labels for use with the Sabertooth 2x5 motor controller

// Digital pin 13 is the serial transmit pin to the 
// Sabertooth 2x5
#define SABER_TX_PIN               13

// NOT USED (but still init'd)
// Digital pin 12 is the serial receive pin from the 
// Sabertooth 2x5
#define SABER_RX_PIN               12

// Set to 9600 through Sabertooth dip switches
#define SABER_BAUDRATE             9600

// Simplified serial Limits for each motor
#define SABER_MOTOR1_FULL_FORWARD  127
#define SABER_MOTOR1_FULL_REVERSE  1

#define SABER_MOTOR2_FULL_FORWARD  255
#define SABER_MOTOR2_FULL_REVERSE  128

// Motor level to send when issuing the full stop command
#define SABER_ALL_STOP             0


SoftwareSerial SaberSerial = SoftwareSerial( SABER_RX_PIN,
                                             SABER_TX_PIN );

void initSabertooth( void )
{
  // Init software UART to communicate 
  // with the Sabertooth 2x5
  pinMode( SABER_TX_PIN, OUTPUT );

  SaberSerial.begin( SABER_BAUDRATE );     

  // 2 second time delay for the Sabertooth to init
  delay( 2000 );

  // Send full stop command
  setEngineSpeed( SABER_ALL_STOP );
}

/*****************************************************
 * setEngineSpeed
 *
 * Inputs - cSpeed_Motor1 - Input a percentage of full 
 *                          speed, from -100 to +100
 *
 *****************************************************/
void setEngineSpeed( signed char cNewMotorSpeed )
{
  unsigned char cSpeedVal_Motor1 = 0;

  unsigned char cSpeedVal_Motor2 = 0;
  
  // Check for full stop command
  if( cNewMotorSpeed == 0 )
  {
    // Send full stop command for both motors
    SaberSerial.print( 0, byte );

    return;
  }  
  
  // Calculate the speed value for motor 1
  if( cNewMotorSpeed >= 100 )
  {
    cSpeedVal_Motor1 = SABER_MOTOR1_FULL_FORWARD;

    cSpeedVal_Motor2 = SABER_MOTOR2_FULL_FORWARD;
  }
  else if( cNewMotorSpeed <= -100 )
  {
    cSpeedVal_Motor1 = SABER_MOTOR1_FULL_REVERSE;

    cSpeedVal_Motor2 = SABER_MOTOR2_FULL_REVERSE;
  }
  else
  {
    // Calc motor 1 speed (Final value ranges from 1 to 127)
    cSpeedVal_Motor1 = map( cNewMotorSpeed, 
                           -100, 
                            100, 
                            SABER_MOTOR1_FULL_REVERSE,
                            SABER_MOTOR1_FULL_FORWARD );

    // Calc motor 2 speed (Final value ranges from 128 to 255)
    cSpeedVal_Motor2 = map( cNewMotorSpeed, 
                           -100, 
                            100, 
                            SABER_MOTOR2_FULL_REVERSE, 
                            SABER_MOTOR2_FULL_FORWARD );
  }

  // Fire the values off to the Sabertooth motor controller
  SaberSerial.print( cSpeedVal_Motor1, byte );

  SaberSerial.print( cSpeedVal_Motor2, byte );
}
