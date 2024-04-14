#define BLYNK_PRINT Serial                                                  //These defines are used for the BLYNK APP
#define BLYNK_TEMPLATE_ID "user1"
#define BLYNK_TEMPLATE_NAME "user1@server.wyns.it"

#include <WiFi.h>                                                           //These includes are necessary for all used libraries
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <DHT.h>

#define DHTTYPE DHT11  // Type DHT-sensor                                   //this line is used to declare which type of DHT we are using

char auth[] = "FhyFOzCjztiBuopmhh4WLCXDOkfoQZu9";                           //this is the authentication token you get on the Blynk App, in the Project Settings (nut icon)


char ssid[] = "**********";                                                  //these are you wifi name and password, fill your own wifi and pass in
char pass[] = "**********";

const int DHTPIN = 22;                                                      //these lines define what pin you use for your DHT and setup the DHT
DHT dht(DHTPIN, DHTTYPE);

const int TRANSISTOR_PIN[3] = { 2, 4, 5 };                                  //these lines are used for defining which pins the transistor and contactsensors use
const int DOOR_SENSOR_PIN[3] = { 18, 19, 21 };

int doorState[3];                                                           //doorstate is a int used for simplification of the code, if you have more or less gates you have to change this. This well display if the gate is open or closed
 

int buttonState = 0;                                                        // Variable to store the button state

void setup() {

  dht.begin();
  Serial.begin(9600);                                                      //the serial is used to troubleshoot problems
  initializePins();                                                        //This function initialises all the pins

  delay(10);
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, pass);                                                  // This is a check to ensure your wifi is working
  int wifi_ctr = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("WiFi connected");

  Blynk.begin(auth, ssid, pass, "server.wyns.it", 8081);                  //this connects to the Blynk app
}

void loop() {
  Blynk.run();                                                             //this line is used for the blynk app to communicate
  UpdateSensors();                                                         //this function read and updates the position of the gates
  UpdateDHT11();                                                           //this fucntion read and updates the DHT sensor
}





void initializePins() {
  for (int i = 0; i < 3; i++) {
    pinMode(TRANSISTOR_PIN[i], OUTPUT);
    pinMode(DOOR_SENSOR_PIN[i], INPUT_PULLUP);
  }
}

void UpdateSensors() {
  for (int i = 0; i < 3; i++) {
    doorState[i] = digitalRead(DOOR_SENSOR_PIN[i]);  // read state
    if (doorState[i] == HIGH) {
//      Serial.println("The door is open");
    
      Blynk.virtualWrite(i+8, 1023);
    } else {
//      Serial.println("The door is closed");
      Blynk.virtualWrite(i+8, 0);
    }
  }
}


void UpdateDHT11() {
  float temperature = dht.readTemperature();  // Read temperature in Celsius
  float humidity = dht.readHumidity();        // Read humidity
  Blynk.virtualWrite(V30, temperature);
  Blynk.virtualWrite(V31, humidity);
}