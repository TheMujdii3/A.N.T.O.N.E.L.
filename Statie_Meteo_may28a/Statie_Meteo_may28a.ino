#include "arduino_secrets.h"
/*
  Sketch generated by the Arduino IoT Cloud Thing "Untitled"
  https://create.arduino.cc/cloud/things/efbed191-f553-49a7-a7c7-fc34dca2681e

  Arduino IoT Cloud Variables description

  The following variables are automatically generated and updated when changes are made to the Thing

  float ppm_aer;
  float ppm_metan;
  float temp;
  float umiditate;
  bool ok;

  Variables which are marked as READ/WRITE in the Cloud Thing will also have functions
  which are called when their values are changed from the Dashboard.
  These functions are generated with the Thing and added at the end of this sketch.
*/

#include "thingProperties.h"


int v[4],i;

void setup() {
  // Initialize serial and wait for port to open:
  Serial.begin(9600);
  // This delay gives the chance to wait for a Serial Monitor without blocking if none is found
  delay(1500);
  Serial.swap();

  // Defined in thingProperties.h
  initProperties();

  // Connect to Arduino IoT Cloud
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  /*
     The following function allows you to obtain more information
     related to the state of network and IoT Cloud connection and errors
     the higher number the more granular information you’ll get.
     The default is 0 (only errors).
     Maximum is 4
  */
  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();
  // Your code here
   if (Serial.available() > 0) {
                for(i=0;i<4;i++)v[i] = Serial.read();
    }
    /*
    v[0]=temp
    v[1]=umiditate
    v[2]=metan
    v[3]=135
    */
    if(v[2]<400 && v[3]<150)ok=true;
    else ok=false;
    
    

}


/*
  Since Temp is READ_WRITE variable, onTempChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onTempChange()  {
  // Add your code here to act upon Temp change
}

/*
  Since Umiditate is READ_WRITE variable, onUmiditateChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onUmiditateChange()  {
  // Add your code here to act upon Umiditate change
}

/*
  Since Presiune is READ_WRITE variable, onPresiuneChange() is
  executed every time a new value is received from IoT Cloud.
*/


/*
  Since PpmAer is READ_WRITE variable, onPpmAerChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPpmAerChange()  {
  // Add your code here to act upon PpmAer change
}

/*
  Since PpmMetan is READ_WRITE variable, onPpmMetanChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onPpmMetanChange()  {
  // Add your code here to act upon PpmMetan change
}


/*
  Since Ok is READ_WRITE variable, onOkChange() is
  executed every time a new value is received from IoT Cloud.
*/
void onOkChange()  {
  // Add your code here to act upon Ok change
}