#include "WiFi.h"
#include <ThingSpeak.h>               // add librery


WiFiClient  client;
unsigned long counterChannelNumber = 1539091;                // Channel ID
const char * myCounterReadAPIKey = "LZGQJC3POVQTR7XB";      // Read API Key
const int FieldNumber1 = 1;                                 // The field you wish to read
const int FieldNumber2 = 2;                                 // The field you wish to read

void setup()
{
  pinMode(27,OUTPUT);
  Serial.begin(9600);
  Serial.println();

  WiFi.begin("vivo 1935", "nandu4472");                 // write wifi name & password           

  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());
  ThingSpeak.begin(client);
}

void loop() 
{
 int A = ThingSpeak.readLongField(counterChannelNumber, FieldNumber2, myCounterReadAPIKey);
 Serial.println(A);
 digitalWrite(27,A);
}
