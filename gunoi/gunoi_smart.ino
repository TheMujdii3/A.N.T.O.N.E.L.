#include <LiquidCrystal_I2C.h>
#include <Servo.h>


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); // Adjust to (0x27,20,4) for 20x4 LCD

char rezultat;
const int pingPin = 10;
const int plinPin = 12;
const int echoPin = 7;
const int echo2Pin = 6;
const int reset = 2;
long duration ,duration2;
int cm ,cm2;

Servo servoclapa;  // create servo object to control a servo            
long val;
long procentaj;
void setup() {
  Serial.begin(9600);
  servoclapa.attach(9);
  lcd.init();
  lcd.backlight(); 
  pinMode(pingPin, OUTPUT);
  pinMode(plinPin, OUTPUT); // Sets the trigPin as an Output
  pinMode(echoPin, INPUT); // Sets the echoPin as an Input 
  pinMode(echo2Pin, INPUT);
  //digitalWrite(reset, HIGH);
  delay(200);
  //pinMode(reset, OUTPUT);
  //Serial.flush();
}

  void loop() {
  // establish variables for duration of the ping, and the distance result
  // in inches and centimeters:
  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  //lcd.print("da");
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  /*pinMode(pingPin, OUTPUT);
  
  pinMode(plinPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  digitalWrite(plinPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  digitalWrite(plinPin, LOW);
  */
  //digitalWrite(plinPin, LOW);
  //digitalWrite(pingPin, LOW);
  digitalWrite(plinPin, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(plinPin, HIGH);
 // digitalWrite(pingPin, HIGH);

  delayMicroseconds(10);
  
  digitalWrite(plinPin, LOW);
  //digitalWrite(pingPin, LOW);

  // Reads the echoPin, returns the sound wave travel time in microseconds
  duration = pulseIn(echo2Pin, HIGH);
 // duration2 = pulseIn(echo2Pin, HIGH);
  cm = duration*0.034/2;
  //cm=cm*3/10;
 
  //Serial.println(duration);
  //Serial.println(cm);
  //Serial.println(cm2);
  //Serial.println(duration);
  servoclapa.write(90);
  lcd.setCursor(0, 0);
  lcd.print("Gunoiu e");
  lcd.setCursor(9, 0);
  //lcd.print(cm);
  // The same pin is used to read the signal from the PING))): a HIGH pulse
  // whose duration is the time (in microseconds) from the sending of the ping
  // to the reception of its echo off of an object.
  // pinMode(plinPin, INPUT);
  //duration2 = pulseIn(echoPin,HIGH);
  // convert the time into a distance

  
  procentaj=100-(cm*31/10);
  Serial.print("cm=");
  Serial.println(cm);
  Serial.print("procentaj=");
  Serial.println(procentaj);
  //if(procentaj>100 || procentaj<1)digitalWrite(reset, LOW);
  lcd.print(procentaj);
 //  Serial.println(cm);
  
  if(cm<10){
    servoclapa.write(0);
  }
  else servoclapa.write(180);


  
  //rezultat=("rezultatu e"+procentaj);
  
  //val=map(val,0 ,cm ,0,180);

  delay(100);
}



