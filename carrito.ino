#include <NewPing.h>

#define SONAR_NUM     2 // Number or sensors.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
#define PING_INTERVAL 33 // Milliseconds between sensor pings (29ms is about the min to avoid cross-sensor echo).
#define TRIGGER_PIN1  31  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN1     30  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define TRIGGER_PIN2  49  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN2     48  // Arduino pin tied to echo pin on the ultrasonic sensor.

// wired connections
#define HG7881_A_IA 8 // D10 --> Motor A Input A --> MOTOR A +
#define HG7881_A_IB 9 // D11 --> Motor A Input B --> MOTOR A -
#define HG7881_B_IA 10 // D10 --> Motor B Input A --> MOTOR B +
#define HG7881_B_IB 11 // D11 --> Motor B Input B --> MOTOR B -
 
// functional connections
#define MOTOR_A_PWM HG7881_A_IA // Motor B PWM Speed
#define MOTOR_A_DIR HG7881_A_IB // Motor B Direction
#define MOTOR_B_PWM HG7881_B_IA // Motor B PWM Speed
#define MOTOR_B_DIR HG7881_B_IB // Motor B Direction
 
// the actual values for "fast" and "slow" depend on the motor
#define PWM_SLOW 50  // arbitrary slow speed PWM duty cycle
#define PWM_FAST 200 // arbitrary fast speed PWM duty cycle
#define DIR_DELAY 1000 // brief delay for abrupt motor changes

unsigned long pingTimer[SONAR_NUM]; // Holds the times when the next ping should happen for each sensor.
unsigned int cm[SONAR_NUM];         // Where the ping distances are stored.
uint8_t currentSensor = 0;          // Keeps track of which sensor is active.

NewPing sonar[SONAR_NUM] = {     
  NewPing(31, 30, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping.
  NewPing(49, 48, MAX_DISTANCE)
};



void setup() {
  Serial.begin( 9600 );
  pinMode( MOTOR_A_DIR, OUTPUT );
  pinMode( MOTOR_B_DIR, OUTPUT );
  pinMode( MOTOR_A_PWM, OUTPUT );
  pinMode( MOTOR_B_PWM, OUTPUT );
  digitalWrite( MOTOR_A_DIR, HIGH );
  digitalWrite( MOTOR_B_DIR, HIGH );
  digitalWrite( MOTOR_A_PWM, 255-PWM_FAST );
  digitalWrite( MOTOR_B_PWM, 255-PWM_FAST );
  pingTimer[0] = millis() + 75;           // First ping starts at 75ms, gives time for the Arduino to chill before starting.
  for (uint8_t i = 1; i < SONAR_NUM; i++) // Set the starting time for each sensor.
    pingTimer[i] = pingTimer[i - 1] + PING_INTERVAL;
}

void loop() {
  boolean isValidInput;
  // put your main code here, to run repeatedly:
Serial.println( "Fast forward..." );
        // always stop motors briefly before abrupt changes
        digitalWrite( MOTOR_A_DIR, LOW );
        digitalWrite( MOTOR_A_PWM, LOW );
        digitalWrite( MOTOR_B_DIR, LOW );
        digitalWrite( MOTOR_B_PWM, LOW );
        delay( DIR_DELAY );
        // set the motor speed and direction
        digitalWrite( MOTOR_A_DIR, HIGH );
        digitalWrite( MOTOR_B_DIR, HIGH ); // direction = forward
        analogWrite( MOTOR_A_PWM, 255-PWM_FAST );
        analogWrite( MOTOR_B_PWM, 255-PWM_FAST ); // PWM speed = fast
        //isValidInput = true;
        
}
