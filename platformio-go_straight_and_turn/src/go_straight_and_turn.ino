// Define output pins to L293D HBridge

int Left_motor_forward = 9;     // Left Motor Forward (IN2)

// pin 8 not working , so use 6 instead
// left motor wiring reversed, so IN1 is Reverse
int Left_motor_reverse = 6;     // Left Motor Reverse (IN1)

int Right_motor_forward = 10;    // Right Motor Forward (IN3)

int Right_motor_reverse = 11;    // Right Motor Reverse (IN4)

void setup()
{

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(Left_motor_forward, OUTPUT);

  pinMode(Left_motor_reverse, OUTPUT);

  pinMode(Right_motor_forward, OUTPUT);

  pinMode(Right_motor_reverse, OUTPUT);

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

  // 2 rapid blinks to signal stop
  signal(100, 2);
}

/*
* duration - in msec
*/
void forward(int duration)
{
  // Engage right motor
  digitalWrite(Right_motor_forward, HIGH);  // Right Motor Forward
  analogWrite(Right_motor_forward, 105); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Right_motor_reverse, LOW);    
  analogWrite(Right_motor_reverse, 0);
                   

  // Engage Left Motor
  digitalWrite(Left_motor_forward, HIGH);  // Left Motor Forward
  analogWrite(Left_motor_forward, 100); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Left_motor_reverse, LOW);
  analogWrite(Left_motor_reverse, 0);

  // Blink LED while going forward
  signal(duration, duration/200);

  stop();
}

/*
* Turn RIGHT in place
* duration - in msec
*/
void turnRight(int duration)
{
  // Engage right motor
  digitalWrite(Right_motor_forward, LOW);  // Right Motor Forward
  analogWrite(Right_motor_forward, 0); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Right_motor_reverse, HIGH);    
  analogWrite(Right_motor_reverse, 105);
                   

  // Engage Left Motor
  digitalWrite(Left_motor_forward, HIGH);  // Left Motor Forward
  analogWrite(Left_motor_forward, 100); // PWM 0-255. Adjust to compensate skew.
  digitalWrite(Left_motor_reverse, LOW);
  analogWrite(Left_motor_reverse, 0);

  // Blink LED while turning
  signal(duration, duration/300);

  stop();
}

void loop()
{

  delay(100);
  
  // rapid blink to signal start
  signal(300, 10);
  
  delay(100);

  // go forward
  forward(1000);

  turnRight(300);

}
