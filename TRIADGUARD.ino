#include <DHT.h>
#include "HX711.h"

#define DHTPIN 7 
#define DHTTYPE DHT22
#define RELAY_PIN 8      
#define LOAD_CELL_DOUT 2 
#define LOAD_CELL_SCK 3

#define HEATER_ON  LOW   
#define HEATER_OFF HIGH  

DHT dht(DHTPIN, DHTTYPE);
HX711 scale;

float calibration_factor = -7050; 
float reduction_goal = 0.25;      
float initialFruitWeight = 0;
float targetWeight = 0;
float currentTargetTemp = 55.0;   
bool DRYING_MODE = false;

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HEATER_OFF); 
  
  dht.begin();
  scale.begin(LOAD_CELL_DOUT, LOAD_CELL_SCK);
  scale.set_scale(calibration_factor);
  
  delay(1000);
  scale.tare(); 
  
  // These prints are for the Monitor - they won't break the Plotter
  Serial.println("\n--- TRIADGUARD S7: GRAPHICAL INTERFACE READY ---");
  Serial.println("Go to Tools > Serial Plotter for GUI");
}

void loop() {
  float currentTemp = dht.readTemperature();
  float currentFruitWeight = scale.get_units(5); 

  if (Serial.available()) {
    char cmd = Serial.read();
    if (cmd == 's' || cmd == 'S') {
      DRYING_MODE = !DRYING_MODE;
      if (DRYING_MODE) {
        initialFruitWeight = currentFruitWeight; 
        targetWeight = initialFruitWeight * reduction_goal;
      } else {
        digitalWrite(RELAY_PIN, HEATER_OFF);
      }
    }
  }

  if (DRYING_MODE) {
    if (currentFruitWeight <= targetWeight && currentFruitWeight > 0.5) { 
      DRYING_MODE = false;
      digitalWrite(RELAY_PIN, HEATER_OFF);
    } 
    else {
      float progress = currentFruitWeight / initialFruitWeight;
      if (progress > 0.75) currentTargetTemp = 60.0;
      else if (progress > 0.40) currentTargetTemp = 50.0;
      else currentTargetTemp = 40.0;

      float buffer = 1.5; 
      if (isnan(currentTemp)) {
        digitalWrite(RELAY_PIN, HEATER_OFF); 
      } else if (currentTemp < (currentTargetTemp - buffer)) {
        digitalWrite(RELAY_PIN, HEATER_ON); 
      } else if (currentTemp > (currentTargetTemp + buffer)) {
        digitalWrite(RELAY_PIN, HEATER_OFF); 
      }
    }
  }

  // --- THE GRAPHICAL GUI OUTPUT ---
  updateDisplay(currentTemp, currentFruitWeight);
  delay(1000); // 1 second updates for smoother graphing
}

void updateDisplay(float t, float w) {
  // FORMATTING FOR SERIAL PLOTTER GUI
  // This creates color-coded live traces
  
  Serial.print("Current_Temp:");
  Serial.print(t); 
  Serial.print(",");
  
  Serial.print("Target_Setpoint:");
  Serial.print(currentTargetTemp); 
  Serial.print(",");
  
  Serial.print("Fruit_Mass_g:");
  Serial.println(w); 
}