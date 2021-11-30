#include <Servo.h>
Servo servo1;
int trigPin = 8;
int echoPin = 10;

int sen2Value = 0;
long distance;
long duration;
const int pResistor = A0; // Photoresistor at Arduino analog pin A0
const int ledPin=9;       // Led pin at Arduino pin 9
int value;// Store value from photoresistor (0-1023)

void setup() 
{
  Serial.begin(9600);
servo1.attach(7); 
 pinMode(trigPin, OUTPUT);
 pinMode(echoPin, INPUT);// put your setup code here, to run once:
  pinMode(ledPin, OUTPUT);  // Set lepPin - 9 pin as an output
 pinMode(pResistor, INPUT);// Set pResistor - A0 pin as an input (optional)
 pinMode(4, OUTPUT);   //Red LED
  pinMode(3, OUTPUT);   //Green LED
  pinMode(5, INPUT);//PIR
  pinMode(11, OUTPUT);    //signal to npn as switch
}
 
void loop() {
  sen2Value = digitalRead(5);
  if (sen2Value == 0) 
    {
      digitalWrite(11, LOW); //npn as switch OFF
      digitalWrite(4, HIGH); // Red LED ON,indicating no motion
      digitalWrite(3, LOW); //Green LED OFF, since no Motion detected
      Serial.print("     || NO Motion Detected    " );
    }
 
  if (sen2Value == 1) 
    {
      digitalWrite(11, HIGH);//npn as switch ON
      delay(100);
      digitalWrite(4, LOW); // RED LED OFF 
      digitalWrite(3, HIGH);//GREEN LED ON , indicating motion detected
      Serial.print("      || Motion Detected!      " );
    }
  ultra();
  servo1.write(0);//servo pin 7
  if(distance <= 10){
  servo1.write(90);
  }
  value = analogRead(pResistor);
  
  //You can change value "25"
  if (value > 25){
    digitalWrite(ledPin, LOW);  //Turn led off
    Serial.print("Bulb OFF = ");
    Serial.print(value);
  }
  else{
    digitalWrite(ledPin, HIGH);
    Serial.print("Bulb ON = ");
    Serial.print(value);//Turn led on
  }

   
}
 
void ultra(){
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  Serial.println(distance);
  delay(100);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration*0.034/2;
  }
