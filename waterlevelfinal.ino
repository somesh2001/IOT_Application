
#define POWER_PIN  17 // ESP32 pin GIOP17 connected to sensor's VCC pin
#define SIGNAL_PIN A6// ESP32 pin GIOP36 (ADC0) connected to sensor's signal pin
#define SIGNAL_PIN2 A4 // ESP32 pin GIOP36 (ADC3) connected to sensor's signal pin

#define THRESHOLD 100
int value = 0; // variable to store the sensor value
int value2 = 0; // variable to store the sensor value

void setup() {
  // put your setup code here, to run once:
   Serial.begin(9600);
  pinMode(POWER_PIN, OUTPUT);   // configure pin as an OUTPUT
  digitalWrite(POWER_PIN, LOW); // turn the sensor OFF

}

void loop() {
   digitalWrite(POWER_PIN, HIGH);  // turn the sensor ON

  delay(100);                      // wait 10 milliseconds
  value = analogRead(SIGNAL_PIN); // read the analog value from sensor
  value2 = analogRead(SIGNAL_PIN2); // read the analog value from sensor
  digitalWrite(POWER_PIN, LOW);   // turn the sensor OFF
  Serial.print("\n");
  delay(1000);
//  **********************Conditioning water level******************************
  if (value > THRESHOLD) {
    Serial.print("Sensor 1");
    Serial.print("The water is detected ");
    Serial.print("Water level is Medium ");

  } 
 if(value < THRESHOLD) {
   
    Serial.print("Sensor 1");
    Serial.print(" Water level is Low ");
  }
    Serial.print("Sensor 1 value: ");
  Serial.println(value);

    if (value2 > THRESHOLD) {
   // digitalWrite(RELAY_PIN, LOW); // turn on pump 5 seconds
    Serial.print("Sensor 2");
    Serial.print(" The water is detected ");
    Serial.print(" Water level is High ");

  } 
  if(value2 < THRESHOLD) {
  //  digitalWrite(RELAY_PIN, HIGH); // turn on pump 5 seconds
    Serial.print("Sensor 2");
    Serial.print(" Water level is Low ");
  }
  Serial.print("\n");
  Serial.print("Sensor 2 value: ");
  Serial.println(value2);
  delay(100);  
  int finals = value+value2;

}
