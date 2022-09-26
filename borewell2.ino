#include "WiFi.h"
#include "PubSubClient.h" // Connect and publish to the MQTT broker
                    // The field you wish to read
//*******************current/*******************
const int sensorIn = A0;
int mVperAmp =185; // use 100 for 20A Module and 66 for 30A Module and 185 for 5A Module

double Voltage = 0;
double VRMS = 0;
double vp = 0;
double AmpsRMS = 0;

//***********curret*************************
const char ssid[]="AVANTI";
const char wifi_password[]="Avantika@";
// MQTT
const char* mqtt_server = "10.33.0.62";  // IP of the MQTT broker
const char* borewell2 = "home/motor/waterborewell2";
const char* power_topic2 = "home/borewell/power2";
const char* mqtt_username = "somesh"; // MQTT username
const char* mqtt_password = "nandu4472"; // MQTT password
const char* clientID = "client_livingroom"; // MQTT client ID

// Initialise the WiFi and MQTT Client objects
WiFiClient wifiClient;
// 1883 is the listener port for the Broker
PubSubClient client(mqtt_server, 1883, wifiClient); 

//**********************wifi_Connection******************************
// Custom function to connet to the MQTT broker via WiFi
void connect_MQTT(){
//  Serial.print("Connecting to ");
//  Serial.println(ssid);
//
//  // Connect to the WiFi
//  WiFi.begin(ssid, wifi_password);
//
//  // Wait until the connection has been confirmed before continuing
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(500);
//    Serial.print(".");
//  }
//
//  // Debugging - Output the IP Address of the ESP8266
//  Serial.println("WiFi connected");
//  Serial.print("IP address: ");
//  Serial.println(WiFi.localIP());

  // Connect to MQTT Broker
  // client.connect returns a boolean value to let us know if the connection was successful.
  // If the connection is failing, make sure you are using the correct MQTT Username and Password (Setup Earlier in the Instructable)
  if (client.connect(clientID, mqtt_username, mqtt_password)) {
    Serial.println("Connected to MQTT Broker!");
  }
  else {
    Serial.println("Connection to MQTT Broker failed...");
  }
}




#define POWER_PIN  17 // ESP32 pin GIOP17 connected to sensor's VCC pin
#define SIGNAL_PIN A6 // ESP32 pin GIOP36 (ADC0) connected to sensor's signal pin
const int RELAY_PIN = A7; // ESP32 pin GIOP27, which connects to the IN pin of relay
void setup() {
  Serial.begin(9600);
 pinMode(POWER_PIN, OUTPUT);   // configure pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);
  //*******************wifi*****************************
  Serial.print("Connecting to ");
  Serial.println(ssid);

  // Connect to the WiFi
  WiFi.begin(ssid, wifi_password);

  // Wait until the connection has been confirmed before continuing
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Debugging - Output the IP Address of the ESP8266
  Serial.println("WiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
 
  //********************wifi over*******************
}

#define THRESHOLD 100
int value = 0; // variable to store the sensor value


void loop() 
{
 connect_MQTT();

  //--------------------Water LEVEL  CALCULATION----------------------------------
  digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON
  delay(1000);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF
  Serial.print("\n");
  delay(1000);
  digitalWrite(RELAY_PIN, HIGH); // turn on pump 5 seconds
  delay(1000);
  digitalWrite(RELAY_PIN, LOW); // turn on pump 5 seconds

  //**********************Conditioning water level******************************
  if (value > THRESHOLD) {
    digitalWrite(RELAY_PIN, LOW); // turn on pump 5 seconds
    Serial.print("Sensor 1");
    Serial.print("The water is detected ");
    Serial.print("Water level is Medium ");

  } 
 if(value < THRESHOLD) {
    digitalWrite(RELAY_PIN, HIGH); // turn on pump 5 seconds
    Serial.print("Sensor 1");
    Serial.print(" Water level is Low ");
  }
    Serial.print("Sensor 1 value: ");
  Serial.println(value);
  Serial.print("\n");

    //**********************water level data to pi******************************
  if (client.publish(borewell2, String(value).c_str())) {
    Serial.println("water level sent!");
  }
  // Again, client.publish will return a boolean value depending on whether it succeded or not.
  // If the message failed to send, we will try again, as the connection may have broken.
  else {
    Serial.println("water level failed to send. Reconnecting to MQTT Broker and trying again");
    client.connect(clientID, mqtt_username, mqtt_password);
    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
    client.publish(borewell2, String(value).c_str());
  }

  client.disconnect();  // disconnect from the MQTT broker
  delay(100);

  int power2 = 4*2;
//    if (client.publish(power_topic2, String(power2).c_str())) {
//    Serial.println("water level sent!");
//  }
//  // Again, client.publish will return a boolean value depending on whether it succeded or not.
//  // If the message failed to send, we will try again, as the connection may have broken.
//  else {
//    Serial.println("water level failed to send. Reconnecting to MQTT Broker and trying again");
//    client.connect(clientID, mqtt_username, mqtt_password);
//    delay(10); // This delay ensures that client.publish doesn't clash with the client.connect call
//    client.publish(power_topic2, String(power2).c_str());
//  }
//
//  client.disconnect();  // disconnect from the MQTT broker
//  delay(100);
  
   Voltage = getVPP();
 vp = Voltage/2.0;
 VRMS = vp*0.707;
 AmpsRMS =((VRMS * 1000)/mVperAmp)-15.50;
 Serial.print(AmpsRMS);
 Serial.println(" Amps RMS");
};

float getVPP()
{
  float result;
  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  
   uint32_t start_time = millis();
   while((millis()-start_time) < 1000) //sample for 1 Sec
   {
       readValue = analogRead(sensorIn);
       // see if you have a new maxValue
       if (readValue > maxValue) 
       {
           /*record the maximum sensor value*/
           maxValue = readValue;
       }
       if (readValue < minValue) 
       {
           /*record the minimum sensor value*/
           minValue = readValue;
       }
   }
   
   // Subtract min from max
   result = ((maxValue - minValue) * 5.0)/1024.0;
      
   return result;
 }
