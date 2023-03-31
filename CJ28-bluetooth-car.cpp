//Caleb J.
//2021-04-19
//FINAL PROJECT: Arduino RC Car
//Version 2.33
//-------------------------------------------------
# define TRIGGER 7   // Trigger pin is 7
# define ECHO 6      // Echo input pin is 6

char t;

void setup() {
  //Monitor for Ping Sensor Testing
  Serial.begin(9600); // Initialize UART0
  Serial.println("Ultrasonic Sensor Test");

  //Ping Sensor
  pinMode(TRIGGER, OUTPUT); // TRIGGER Pin is an Output
  pinMode(ECHO, INPUT);     // ECHO Pin is an Input  

  //Motors
  pinMode(13,OUTPUT);   //left motors forward
  pinMode(12,OUTPUT);   //left motors revers
  pinMode(11,OUTPUT);   //right motors forward
  pinMode(10,OUTPUT);   //right motors reverse
}

void loop() {
  long duration, cm; // Variables to Calculate  
  
  //Trigger the Sensor - From TinkerCAD  
  digitalWrite(TRIGGER, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGGER, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER, LOW); 

 //Ping Sensor to CM
  duration = pulseIn(ECHO, HIGH);
  cm = microsecondsToCentimeters(duration);

  //Bluetooth Control - YouTube
  
  if(Serial.available() > 0){
    t = Serial.read();
    Serial.println(t);
    }

    //Control cases as long as the sensor is far enough away from object
    if (cm >= 20){
      if(t == '1'){            //move forward(all motors rotate in forward direction)
        digitalWrite(13,HIGH);
        digitalWrite(12,LOW);
        digitalWrite(11,HIGH);
        digitalWrite(10,LOW);
        } else if(t == '2'){      //move reverse (all motors rotate in reverse direction)
          digitalWrite(13,LOW);
          digitalWrite(12,HIGH);
          digitalWrite(11,LOW);
          digitalWrite(10,HIGH);
          } else if(t == '3'){      //turn right (left side motors rotate in forward direction, right side motors doesn't rotate)
            digitalWrite(13,LOW);
            digitalWrite(12,LOW);
            digitalWrite(11,HIGH);
            digitalWrite(10,LOW);
            } else if(t == '4'){      //turn left (right side motors rotate in forward direction, left side motors doesn't rotate)
              digitalWrite(13,HIGH);
              digitalWrite(12,LOW);
              digitalWrite(11,LOW);
              digitalWrite(10,LOW);
              } else if(t == '5'){      //STOP (all motors stop)
                digitalWrite(13,LOW);
                digitalWrite(12,LOW);
                digitalWrite(11,LOW);
                digitalWrite(10,LOW);
                }
                }

                //Function if Ping Sensor is close to object
                if (cm <= 20){
                  digitalWrite(13,LOW);
                  digitalWrite(12,LOW);
                  digitalWrite(11,LOW);
                  digitalWrite(10,LOW);
                  delay(100);
                  digitalWrite(13,LOW);
                  digitalWrite(12,HIGH);
                  digitalWrite(11,LOW);
                  digitalWrite(10,HIGH);
                  delay(800);
                  digitalWrite(13,LOW);
                  digitalWrite(12,LOW);
                  digitalWrite(11,LOW);
                  digitalWrite(10,LOW);
                  }
                  delay(100);
                  }

//CM conversion from TinkerCAD
long microsecondsToCentimeters(long microseconds){
  return microseconds / 29 / 2;
}
