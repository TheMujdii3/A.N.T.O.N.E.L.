#include <Stepper.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>
#include <dht11.h>

//crearea obiectelor 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); 
Stepper help = Stepper(32,5,7,10,11);
Servo servoclapa;


//pinii pt stepper 
const int in1 = 5;
const int in2 = 7;
const int in3 = 10;
const int in4 = 11;
// gata
//pinii pt ultrasonici
const int pingPin =3;
const int plinPin = 12;
const int echoPin = 4;
const int echo2Pin = 6;
//gata
//pin reset
const int reset = 2;
//gata
//pinii pt senzorii de la statia meteo
const int Temp_HumidPin = 9;
const int metan = A0;
const int mq135 = A1;
int send_data[4];
//variabilele utilizate
long duration ,duration2;
int cm ,cm2,x;
int unghi;
int valdht,ppm_metan,ppm_135;
long val;
long procentaj;

void setup() {
  Serial.begin(9600);

  //initializarea servoului
  servoclapa.attach(9);
  servoclapa.write(175);

  //initializarea displayului
  lcd.init();
  lcd.backlight(); 

  //initializarea ultrasonicilor
  pinMode(pingPin, OUTPUT);
  pinMode(plinPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
  pinMode(echo2Pin, INPUT);
  pinMode(metan , INPUT);
  pinMode(mq135 , INPUT);

  //initializare pin reset
  digitalWrite(reset, HIGH);
  delay(200);
  pinMode(reset, OUTPUT);

  //setare viteza stepper
  help.setSpeed(15);
}

  void loop() {
  valdht = DHT11.read(Temp_HumidPin);
  
  ppm_metan=analogRead(metan);
  ppm_135=analogRead(mq135);

  send_data[1]=DHT11.humidity;
  send_data[0]=DHT11.temperature;
  send_data[2]=ppm_metan;
  send_data[3]=ppm_135;
  Serial.print("mq135:");
  Serial.println(send_data[3]);




  //citire date de la senzorul din interiorul cosului de gunoi
  digitalWrite(plinPin, LOW);
  delayMicroseconds(2);
  
  digitalWrite(plinPin, HIGH);
  delayMicroseconds(10);
  
  digitalWrite(plinPin, LOW);

  duration2 = pulseIn(echo2Pin, HIGH);

  //citire date de la senzorul din exteriorul cosului de gunoi
  digitalWrite(pingPin, LOW);

  delayMicroseconds(2);

  digitalWrite(pingPin, HIGH);

  delayMicroseconds(10);
  digitalWrite(pingPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  
  //determinare distante in functie de viteza sunetului(0.034cm/microsecunda)
  cm = duration*0.034/2;
  cm2 = duration2*0.043/2;

  //afisarea variabilei procentaj pe ecran
  lcd.setCursor(0, 0);
  lcd.print("Gunoiul e");
  lcd.setCursor(9, 0);
  x=cm2*25/10;  
  procentaj=100-(cm2*23.5/10);
  lcd.setCursor(10, 0);
  lcd.print(procentaj);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("plin");
 
  //deschiderea capacului
  if(cm<20)
  {
    servoclapa.write(100);
    help.step(20);
  }
  else 
  {
    servoclapa.write(175);
    help.step(-20);
    delay(5000);
  }
  
  //afisare variabile in serial monitor pentru debug eficient si rapid
  Serial.print("cm=");
  Serial.println(cm);
  Serial.print("unghi=");
  Serial.println(unghi);
  Serial.print("cm2=");
  Serial.println(cm2);
  Serial.print("procentaj=");
  Serial.println(procentaj);
  Serial.print("x=");
  Serial.println(x);
  delay(100);
  
  //resetarea placii cand "procentaj" iese din multimea (1,99)
  if(procentaj<1 || procentaj>99)digitalWrite(reset, LOW);

}