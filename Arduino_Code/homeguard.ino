#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Initialize the LCD with the I2C address 0x27, 16 columns, and 2 rows
LiquidCrystal_I2C lcd(0x27, 16, 2);

// Define LED input pins
const int ledPins[7] = {2, 3, 4, 5, 6, 7, 8};  // Digital input pins for LEDs

// Define messages to be displayed on the LCD
const char* sensorMessages[7] = {
  "Abnormal motion",      // LED 1 corresponds to "Abnormal motion detected"
  "Main gate open",       // LED 2 corresponds to "Main gate open"
  "Main door open",       // LED 3 corresponds to "Main door open"
  "High water level",     // LED 4 corresponds to "High water level"
  "Rain detected",        // LED 5 corresponds to "Rain detected"
  "High AC voltage",      // LED 6 corresponds to "High AC voltage"
  "Light sensor active"   // LED 7 corresponds to "Light sensor active"
};

void setup() {
  // Initialize serial communication for debugging (optional)
  Serial.begin(9600);

  // Initialize the LCD
  lcd.begin(16,2);
  lcd.backlight();
  lcd.setCursor(0,0);

  // Set LED pins as inputs
  for (int i = 0; i < 7; i++) {
    pinMode(ledPins[i], INPUT);
  }

  // Clear the LCD at startup
  lcd.clear();
}

void loop() {
  for (int i = 0; i < 7; i++) {
    int ledState = digitalRead(ledPins[i]);

    // If the LED is ON (indicating the sensor is triggered)
    if (ledState == HIGH) {
      // Display the corresponding message on the LCD
      lcd.clear();                 // Clear previous messages
      lcd.setCursor(0, 0);         // Set cursor to the first line
      lcd.print(sensorMessages[i]); // Print the corresponding message

      // Debug output to Serial Monitor (optional)
      Serial.println(sensorMessages[i]);

      delay(500); // Delay to ensure message visibility
    }
  }

  delay(100); // Short delay to prevent bouncing issues
}
