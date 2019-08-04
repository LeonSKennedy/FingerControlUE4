#include "EEPROM.h"
#include <WiFi.h>
#include "AsyncUDP.h"

#define EEPROMUtils
#define SettingsUtils
#define SerialPortHelper
#define WiFiHelper
#define UDPClient
#define ProtocolHelper
#define DataUtils

const int thumbPin = 34; //SVP
const int indexPin = 33; //SVN
const int middlePin = 35;
const int ringPin = 39;
const int pinkyPin = 36;

void setup() 
{
    Serial.begin(115200);
    EEPROM.begin(500);

    InitSettings();
    InitWiFi();
    UDPConnect();

    pinMode(thumbPin, INPUT);        
    pinMode(indexPin, INPUT);
    pinMode(middlePin, INPUT);
    pinMode(ringPin, INPUT);
    pinMode(pinkyPin, INPUT);
}

void loop() 
{

    String sensorName = ReadStringEEPROM(2);
    int thumb = analogRead(thumbPin);
    int index = analogRead(indexPin);
    int middle = analogRead(middlePin);
    int ring = analogRead(ringPin);
    int pinky = analogRead(pinkyPin);
    String fingerDataJSONString = GetFingerDataJSONString(sensorName, thumb, index, middle, ring, pinky);
    UDPSendData(fingerDataJSONString);

    SerialPortReceive();
}
