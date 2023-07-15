// Code generated by Arduino IoT Cloud, DO NOT EDIT.

#include <ArduinoIoTCloud.h>
#include <Arduino_ConnectionHandler.h>

const char DEVICE_LOGIN_NAME[]  = "f6ff9954-f825-4e02-a54e-2fbd6d46fdc9";

const char SSID[]               = SECRET_SSID;    // Network SSID (name)
const char PASS[]               = SECRET_OPTIONAL_PASS;    // Network password (use for WPA, or use as key for WEP)
const char DEVICE_KEY[]  = SECRET_DEVICE_KEY;    // Secret device password

void onPpmAerChange();
void onPpmMetanChange();
void onProcentGunoiChange();
void onTempChange();
void onUmiditateChange();
void onOkChange();

float ppm_aer;
float ppm_metan;
float procent_gunoi;
float temp;
float umiditate;
bool ok;

void initProperties(){

  ArduinoCloud.setBoardId(DEVICE_LOGIN_NAME);
  ArduinoCloud.setSecretDeviceKey(DEVICE_KEY);
  ArduinoCloud.addProperty(ppm_aer, READWRITE, 1 * SECONDS, onPpmAerChange);
  ArduinoCloud.addProperty(ppm_metan, READWRITE, 1 * SECONDS, onPpmMetanChange);
  ArduinoCloud.addProperty(procent_gunoi, READWRITE, 1 * SECONDS, onProcentGunoiChange);
  ArduinoCloud.addProperty(temp, READWRITE, 1 * SECONDS, onTempChange);
  ArduinoCloud.addProperty(umiditate, READWRITE, 1 * SECONDS, onUmiditateChange);
  ArduinoCloud.addProperty(ok, READWRITE, 1 * SECONDS, onOkChange);

}

WiFiConnectionHandler ArduinoIoTPreferredConnection(SSID, PASS);
