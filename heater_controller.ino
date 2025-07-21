#include <OneWire.h>
#include <DallasTemperature.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

// Pin Definitions
#define TEMP_SENSOR_PIN 4     // DS18B20 data pin
#define HEATER_PIN 5          // Heater pin
#define BUZZER_PIN 15         // Buzzer pin
#define HEATER_LED_PIN 14     // Heater LED pin

// OLED settings
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

OneWire oneWire(TEMP_SENSOR_PIN);
DallasTemperature sensors(&oneWire);
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

// Variables
float temperature = 0.0;
String currentStatus = "";

void setup() {
  Serial.begin(115200);
  sensors.begin();

  pinMode(HEATER_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(HEATER_LED_PIN, OUTPUT);

  digitalWrite(HEATER_PIN, LOW);
  digitalWrite(BUZZER_PIN, LOW);
  digitalWrite(HEATER_LED_PIN, LOW);

  // Start OLED
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.display();
}

void loop() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);

  if (temperature < 15.0) {
    digitalWrite(HEATER_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    currentStatus = "IDLE";
  } else if (temperature < 18.0) {
    digitalWrite(HEATER_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    currentStatus = "HEATING";
  } else if (temperature < 24.0) {
    digitalWrite(HEATER_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    currentStatus = "STABILIZING";
  } else if (temperature < 27.0) {
    digitalWrite(HEATER_PIN, HIGH);
    digitalWrite(BUZZER_PIN, LOW);
    currentStatus = "TARGET REACHED";
  } else {
    digitalWrite(HEATER_PIN, LOW);
    digitalWrite(BUZZER_PIN, HIGH);
    currentStatus = "OVERHEAT!";
  }

  digitalWrite(HEATER_LED_PIN, digitalRead(HEATER_PIN));

  Serial.print("Temp: ");
  Serial.print(temperature);
  Serial.print(" °C | Status: ");
  Serial.print(currentStatus);
  Serial.print(" | Heater: ");
  Serial.println(digitalRead(HEATER_PIN) ? "ON" : "OFF");

  showStatus(currentStatus.c_str());
  delay(2000);
}

void showStatus(const char* status) {
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Temp: ");
  display.print(temperature);
  display.println(" C");
  display.print("Status: ");
  display.println(status);
  display.print("Heater: ");
  display.println(digitalRead(HEATER_PIN) ? "ON" : "OFF");
  display.display();
}