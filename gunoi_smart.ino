#include <LiquidCrystal_I2C.h>
#include <Servo.h>


LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); 

char rezultat;
const int pingPin =3;
const int plinPin = 12;
const int echoPin = 4;
const int echo2Pin = 6;
const int reset = 2;
long duration ,duration2;
int cm ,cm2;

Servo servoclapa;           
long val;
long procentaj;

void setup() {
  Serial.begin(9600);
  
  servoclapa.attach(9);
  servoclapa.write(90);
  
  lcd.init();
  lcd.backlight(); 
  
  pinMode(pingPin, OUTPUT);
  pinMode(plinPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(echo2Pin, INPUT);
  
  digitalWrite(reset, HIGH);
  delay(200);
  pinMode(reset, OUTPUT);

}

  void loop() {
  while(procentaj<100 || procentaj>0){

  
  digitalWrite(plinPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(plinPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(plinPin, LOW);

  duration2 = pulseIn(echo2Pin, HIGH);


  digitalWrite(pingPin, LOW);

  delayMicroseconds(2);

  digitalWrite(pingPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  cm = duration*0.034/2;
  cm2 = duration2*0.043/2;

  lcd.setCursor(0, 0);
  lcd.print("Gunoiu e");
  lcd.setCursor(9, 0);
  
  procentaj=100-(cm2*30.2/10);
  Serial.print("cm=");
  Serial.println(cm);
  /*QSerial.print("procentaj=");
  Serial.println(procentaj);*/
  lcd.print(procentaj);
  lcd.print("%");
 
  
  if(cm<10 && procentaj<95){
    servoclapa.write(0);

    delay(5000);
  }
  else servoclapa.write(180);

  delay(100);
  if(cm2>33 || cm<20)digitalWrite(reset, LOW);
  }

}