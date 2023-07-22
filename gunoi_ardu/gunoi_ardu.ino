#include <DHT11.h>

#include <Servo.h>
#include <LiquidCrystal_I2C.h>


//crearea obiectelor 
LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,16,2); 
Servo servoclapa;



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
DHT11 dht11(10);
const int metan = A0;
const int mq135 = A1;
int send_data[4];
//variabilele utilizate
long duration ,duration2;
int cm ,cm2,x;
int unghi;
int i=1;
int umiditate,ppm_metan,ppm_135;
long val;
long procentaj;





void setup() {
  Serial.begin(9600);

  //initializarea servoului
  servoclapa.attach(9);
  //servoclapa.write(100);

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


  Serial.println("START");
  //setare viteza stepper
}

  void loop() {
  
  ppm_metan=analogRead(metan);
  ppm_135=analogRead(mq135);
  if(i%2==0){
    send_data[0]=dht11.readTemperature();
    i=i+1;
  }
  else{
    send_data[1]=dht11.readHumidity();
    i=i+1;
  }
  send_data[2]=ppm_metan;
  send_data[3]=ppm_135;
  

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
  if(cm2<=39)procentaj=100-(cm2*25.5/10);
  lcd.setCursor(10, 0);
  lcd.print(procentaj);
  lcd.print("%");
  lcd.setCursor(0, 1);
  lcd.print("plin");
  delay(2000);
  lcd.clear();
  
  lcd.setCursor(0,0);
  lcd.print("Temp e ");
  lcd.setCursor(8,0);
  lcd.print(send_data[0]);
  lcd.setCursor(0,1);
  lcd.print("Humid e");
  lcd.setCursor(8,1);
  lcd.print(send_data[1]);
  delay(2000);
  lcd.clear();
  
  //deschiderea capacului
  if(cm<20)
  {
    servoclapa.write(93);
  }
  else 
  {
    servoclapa.write(181);
    delay(1000);
  }
  
  //afisare variabile in serial monitor pentru debug eficient si rapid
  /*
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
  Serial.print("dht:");
  Serial.print(send_data[0]);
  Serial.print(" ");
  Serial.print("+");
  Serial.print(" ");
  Serial.println(send_data[1]);
  Serial.print("mq135:");
  Serial.println(send_data[3]);
  Serial.print("mq4:");
  Serial.println(send_data[2]);
  Serial.print("i=");
  Serial.println(i);
  */

  //daca se detecteaza metan clapa sta deschisa
  if(send_data[2]>800)servoclapa.write(90);
  
  //variabila i o ia de la inceput
  if(i == 100)i=1;

  //se pune in vector si procentul pentru a fi transmis in cloud
  send_data[4]=procentaj;

  //se trimite vectorul in nodemcu
  for(int j=0;j<=4;j++){
    Serial.write(send_data[j]);
  }
  
  
  
  //resetarea placii cand "procentaj" iese din multimea (1,99)
  //if(procentaj<1 || procentaj>100)digitalWrite(reset, LOW);
  /*if(procentaj>95){
    servoclapa.write(180);
    delay(500);
    servoclapa.write(90);
  }*/
}