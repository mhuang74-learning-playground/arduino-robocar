// Define output pins to L293D HBridge

int Left_motor_reverse = 8;     // Left Motor Reverse (IN1)

int Left_motor_forward = 9;     // Left Motor Forward (IN2)

int Right_motor_forward = 10;    // Right Motor Forward (IN3)

int Right_motor_reverse = 11;    // Right Motor Reverse (IN4)

void setup()

{

  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(Left_motor_forward, OUTPUT); // PIN 8 (PWM)

  pinMode(Left_motor_reverse, OUTPUT); // PIN 9 (PWM)

  pinMode(Right_motor_forward, OUTPUT);// PIN 10 (PWM)

  pinMode(Right_motor_reverse, OUTPUT);// PIN 11 (PWM)

}

void run(int time)     // 前进

{

  // Engage right motor
  digitalWrite(Right_motor_forward, HIGH);  // Right Motor Forward
  digitalWrite(Right_motor_reverse, LOW);    
  analogWrite(Right_motor_forward, 103); // PWM 0-255. Adjust to compensate skew.
  analogWrite(Right_motor_reverse, 0);
                   

  // Engage Left Motor
  digitalWrite(Left_motor_forward, HIGH);  // Left Motor Forward
  digitalWrite(Left_motor_reverse, LOW);
  analogWrite(Left_motor_forward, 100); // PWM 0-255. Adjust to compensate skew.
  analogWrite(Left_motor_reverse, 0);

  // blink LED to indicate Motion Started!
  digitalWrite(LED_BUILTIN, HIGH);   
  delay(time * 1000); // sec
  digitalWrite(LED_BUILTIN, LOW); 

  // Stop both motors
  digitalWrite(Right_motor_forward, LOW);
  digitalWrite(Right_motor_reverse, LOW);    
  digitalWrite(Left_motor_forward, LOW); 
  digitalWrite(Left_motor_reverse, LOW);
}

void loop()

{

  delay(2 * 1000); // pause for 2 seconds

  run(1);    // sec

}
