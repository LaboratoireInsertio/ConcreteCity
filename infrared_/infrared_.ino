
#include <Button.h>
#include <Servo.h>


#define DC       0
#define SERVO    1
#define SOLENOID 2

Servo servoA;
Servo servoB;

Button switch_servo = Button(5, BUTTON_PULLUP_INTERNAL);
Button switch_solenoide = Button(9, BUTTON_PULLUP_INTERNAL);

int actuator = DC;

int sensorPin = A5;

int data = 0;


void setup() {
  // put your setup code here, to run once:
 
  Serial.begin (9600);
  
   //Switch D5

  if (switch_servo.isPressed()) {
    actuator = SERVO;

    servoA.attach(A5);
    servoB.attach(A4);

    //Switch D9
  } else if (switch_solenoide.isPressed()) {
    actuator = SOLENOID;

    //Motor 1 direction - OUT1 & OUT2
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    //Motor 1 Speed
    pinMode(10, OUTPUT);

    //Motor 2 direction - OUT3 & OUT4
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    //Motor 2 Speed
    pinMode(11, OUTPUT);

  } else {
    actuator = DC;

    //Motor 1 direction - OUT1 & OUT2
    pinMode(7, OUTPUT);
    pinMode(8, OUTPUT);
    //Motor 1 Speed
    pinMode(10, OUTPUT);

    //Motor 2 direction - OUT3 & OUT4
    pinMode(12, OUTPUT);
    pinMode(13, OUTPUT);
    //Motor 2 Speed
    pinMode(11, OUTPUT);

  }

}


/////////////////////////////


void loop() {
  // put your main code here, to run repeatedly:
  
    data = analogRead(sensorPin);
  // turn the ledPin on
   Serial.println(data);
   
  delay(100);
  
  
  // Actuator Servo
      if (actuator == SERVO ) {
        data = map(data, 0, 1023, 0, 180);

        servoA.write(data);
        servoB.write(data);

        // Actuator Solenoide - Switch D9
      } else if (actuator == SOLENOID) {

        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);

        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);

        digitalWrite(10, HIGH);
        digitalWrite(11, HIGH);
        delay (map(data, 0, 1023, 1, 25));
        digitalWrite(10, LOW);
        digitalWrite(11, LOW);



      } else if (actuator == DC) {
        data = map(data, 0, 1023, 0, 255);


#ifdef BIDIRECTIONNAL_DC

        // TWO DIRECTIONAL DC MOTOR - OPTIONAL

        if (data < 128) {
          digitalWrite(7, LOW);
          digitalWrite(8, HIGH);

          analogWrite(10, 255 - map(data, 0, 127, 0, 255));

          digitalWrite(12, LOW);
          digitalWrite(13, HIGH);

          analogWrite(11, 255 - map(data, 0, 127, 0, 255));

        } else {
          digitalWrite(7, HIGH);
          digitalWrite(8, LOW);

          analogWrite(10, map(data, 128, 255, 0, 255));

          digitalWrite(12, HIGH);
          digitalWrite(13, LOW);

          analogWrite(11, map(data, 128, 255, 0, 255));
        }


#else

        // ONE DIRECTION DC MOTOR

        digitalWrite(7, HIGH);
        digitalWrite(8, LOW);

        analogWrite(10, data);

        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);

        analogWrite(11, data);
#endif
      }

  

}
