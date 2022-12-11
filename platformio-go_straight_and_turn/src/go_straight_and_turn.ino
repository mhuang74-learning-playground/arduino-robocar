// Define output pins to L293D HBridge

const int Left_motor_forward = 9;     // Left Motor Forward (IN2)
// pin 8 not working , so use 6 instead
// left motor wiring reversed, so IN1 is Reverse instead of IN2
const int Left_motor_reverse = 6;     // Left Motor Reverse (IN1)
const int Right_motor_forward = 10;    // Right Motor Forward (IN3)
const int Right_motor_reverse = 11;    // Right Motor Reverse (IN4)

// Define input pins for IR Obstacle Detector
const int Left_ir_detector = 3; // P3.4 OUT3
const int Right_ir_detector = 4; // P3.5 OUT4

// define motor driver RMS to go straight
const int Right_rms = 102;
const int Left_rms = 100;

void setup()
{

  Serial.begin(9600);  // We initialize serial connection so that we could print values from sensor.

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(Left_motor_forward, OUTPUT);
  pinMode(Left_motor_reverse, OUTPUT);
  pinMode(Right_motor_forward, OUTPUT);
  pinMode(Right_motor_reverse, OUTPUT);

  pinMode(Right_ir_detector, INPUT);
  pinMode(Left_ir_detector, INPUT);

  // rapid blink to signal START
  signal(1000, 20);

}

/*
* duration - total duration in millis
* count - total blinks within duratino
*/
void signal(int duration, int count)
{
  pinMode(LED_BUILTIN, OUTPUT);

  for (int i=0; i<count; i++)  {
    digitalWrite(LED_BUILTIN, HIGH); 
    delay(duration/count);
    digitalWrite(LED_BUILTIN, LOW); 
    delay(duration/count);
  }
}

void stop()
{
    // Stop both motors
  digitalWrite(Right_motor_forward, LOW);
  digitalWrite(Right_motor_reverse, LOW);    
  digitalWrite(Left_motor_forward, LOW); 
  digitalWrite(Left_motor_reverse, LOW);

  // 1 blinks to signal stop
  signal(10, 1);
}

/*
* duration - in msec
*/
void forward(int duration)
{
  // Engage right motor
  digitalWrite(Right_motor_forward, HIGH);  // Right Motor Forward
  analogWrite(Right_motor_forward, Right_rms); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Right_motor_reverse, LOW);    
  analogWrite(Right_motor_reverse, 0);
                   

  // Engage Left Motor
  digitalWrite(Left_motor_forward, HIGH);  // Left Motor Forward
  analogWrite(Left_motor_forward, Left_rms); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Left_motor_reverse, LOW);
  analogWrite(Left_motor_reverse, 0);

  // Blink LED while going forward
  signal(duration, duration/100);

  stop();
}

/*
* duration - in msec
*/
void reverse(int duration)
{
  // Engage right motor
  digitalWrite(Right_motor_forward, LOW);  // Right Motor Forward
  analogWrite(Right_motor_forward, 0); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Right_motor_reverse, HIGH);    
  analogWrite(Right_motor_reverse, Right_rms);
                   

  // Engage Left Motor
  digitalWrite(Left_motor_forward, LOW);  // Left Motor Forward
  analogWrite(Left_motor_forward, 0); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Left_motor_reverse, HIGH);
  analogWrite(Left_motor_reverse, Left_rms);

  // Blink LED while going forward
  signal(duration, duration/100);

  stop();
}

/*
* SPIN RIGHT - turn right in place
* duration - in msec
*/
void spinRight(int duration)
{
  // Engage right motor
  digitalWrite(Right_motor_forward, LOW);  // Right Motor Forward
  analogWrite(Right_motor_forward, 0); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Right_motor_reverse, HIGH);    
  analogWrite(Right_motor_reverse, Right_rms);
                   

  // Engage Left Motor
  digitalWrite(Left_motor_forward, HIGH);  // Left Motor Forward
  analogWrite(Left_motor_forward, Left_rms); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Left_motor_reverse, LOW);
  analogWrite(Left_motor_reverse, 0);

  // Blink LED while turning
  signal(duration, duration/125);

  stop();
}

void loop()
{

  int blocked_right = digitalRead(Right_ir_detector) == LOW;
  int blocked_left = digitalRead(Left_ir_detector) == LOW;

  // if detect blockage, stop and take reading again
  if (blocked_right || blocked_left) {
    stop();
    signal(200, 10);
    blocked_right = digitalRead(Right_ir_detector) == LOW;
    blocked_left = digitalRead(Left_ir_detector) == LOW;
  }

  if (blocked_right && blocked_left) {
    Serial.println("Both RIGHT and LEFT Blocked!");
    reverse(200);
    spinRight(400);
  } else if (blocked_right) {
    Serial.println("RIGHT Blocked!");
    reverse(200);
    spinRight(700);
  } else if (blocked_left) {
    Serial.println("LEFT Blocked!");
    reverse(200);
    spinRight(300);
  } else {
    // go forward
    forward(200);
  }

}
