#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- Servo ----------------
Servo gateServo;

// ---------------- IR Sensors ----------------
// Parking slot sensors
const int slot1 = 2;
const int slot2 = 3;
const int slot3 = 4;
const int slot4 = 5;

// Entrance sensor
const int entranceSensor = 6;

// Exit/Pass sensor after gate
const int gatePassSensor = 7;

// Servo pin
const int servoPin = 9;

// ---------------- Variables ----------------
int s1, s2, s3, s4;
int totalFilled = 0;

bool gateOpened = false;

// Timing variables
unsigned long lastLCDUpdate = 0;
unsigned long lcdInterval = 500;

// ---------------- SETUP ----------------
void setup()
{
  // Serial Monitor
  Serial.begin(9600);

  Serial.println("=================================");
  Serial.println(" SMART CAR PARKING SYSTEM ");
  Serial.println("=================================");

  // Sensor pins with pullup
  pinMode(slot1, INPUT_PULLUP);
  pinMode(slot2, INPUT_PULLUP);
  pinMode(slot3, INPUT_PULLUP);
  pinMode(slot4, INPUT_PULLUP);

  pinMode(entranceSensor, INPUT_PULLUP);
  pinMode(gatePassSensor, INPUT_PULLUP);

  // Servo setup
  gateServo.attach(servoPin);

  // Gate closed initially
  closeGate();

  // LCD setup
  lcd.init();
  lcd.backlight();

  lcd.setCursor(0, 0);
  lcd.print(" SMART PARKING");

  lcd.setCursor(0, 1);
  lcd.print("    SYSTEM");

  delay(2500);
  lcd.clear();

  Serial.println("System Ready");
}

// ---------------- LOOP ----------------
void loop()
{
  // Read parking slots
  readSlotSensors();

  // Print sensor values
  printSensorStatus();

  // Update LCD every 500ms
  if (millis() - lastLCDUpdate >= lcdInterval)
  {
    updateLCD();
    lastLCDUpdate = millis();
  }

  // Parking full condition
  if (totalFilled >= 4)
  {
    closeGate();

    Serial.println("Parking FULL");

    delay(300);
    return;
  }

  // Detect incoming vehicle
  if (digitalRead(entranceSensor) == LOW && !gateOpened)
  {
    Serial.println("---------------------------------");
    Serial.println("Vehicle Detected At Entrance");
    Serial.println("Opening Gate");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CAR DETECTED");

    lcd.setCursor(0, 1);
    lcd.print("OPENING GATE");

    openGate();

    // Wait until car passes through gate
    waitForVehicleToPass();

    // Close gate
    Serial.println("Closing Gate");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CLOSING GATE");

    closeGate();

    delay(1000);
    lcd.clear();
  }

  delay(100);
}

// ======================================================
// FUNCTION: READ SLOT SENSORS
// ======================================================
void readSlotSensors()
{
  s1 = digitalRead(slot1);
  s2 = digitalRead(slot2);
  s3 = digitalRead(slot3);
  s4 = digitalRead(slot4);

  totalFilled = 0;

  if (s1 == LOW) totalFilled++;
  if (s2 == LOW) totalFilled++;
  if (s3 == LOW) totalFilled++;
  if (s4 == LOW) totalFilled++;
}

// ======================================================
// FUNCTION: UPDATE LCD
// ======================================================
void updateLCD()
{
  lcd.setCursor(0, 0);

  lcd.print("Free Slots:");
  lcd.print(4 - totalFilled);
  lcd.print(" ");

  lcd.setCursor(0, 1);

  // Slot display
  lcd.print("1:");

  if (s1 == LOW)
    lcd.print("F ");
  else
    lcd.print("E ");

  lcd.print("2:");

  if (s2 == LOW)
    lcd.print("F ");
  else
    lcd.print("E ");

  lcd.print("3:");

  if (s3 == LOW)
    lcd.print("F ");
  else
    lcd.print("E ");

  lcd.print("4:");

  if (s4 == LOW)
    lcd.print("F");
  else
    lcd.print("E");
}

// ======================================================
// FUNCTION: SERIAL DEBUG
// ======================================================
void printSensorStatus()
{
  Serial.print("S1:");
  Serial.print(s1 == LOW ? "FULL " : "EMPTY ");

  Serial.print("S2:");
  Serial.print(s2 == LOW ? "FULL " : "EMPTY ");

  Serial.print("S3:");
  Serial.print(s3 == LOW ? "FULL " : "EMPTY ");

  Serial.print("S4:");
  Serial.print(s4 == LOW ? "FULL " : "EMPTY ");

  Serial.print(" | Filled:");
  Serial.print(totalFilled);

  Serial.print(" | Entrance:");
  Serial.print(digitalRead(entranceSensor));

  Serial.print(" | Pass:");
  Serial.println(digitalRead(gatePassSensor));
}

// ======================================================
// FUNCTION: OPEN GATE
// ======================================================
void openGate()
{
  // Change angle if needed
  gateServo.write(0);

  gateOpened = true;

  Serial.println("Gate Opened");

  delay(1000);
}

// ======================================================
// FUNCTION: CLOSE GATE
// ======================================================
void closeGate()
{
  // Change angle if needed
  gateServo.write(90);

  gateOpened = false;

  Serial.println("Gate Closed");
}

// ======================================================
// FUNCTION: WAIT FOR VEHICLE TO PASS
// ======================================================
void waitForVehicleToPass()
{
  Serial.println("Waiting For Vehicle To Pass");

  unsigned long startTime = millis();

  // Wait max 10 seconds
  while (millis() - startTime < 5000)
  {
    // Vehicle detected passing
    if (digitalRead(gatePassSensor) == LOW)
    {
      Serial.println("Vehicle Passing Gate");

      // Wait until vehicle completely crosses
      while (digitalRead(gatePassSensor) == LOW)
      {
        delay(50);
      }

      Serial.println("Vehicle Crossed");

      delay(500);
      return;
    }

    delay(50);
  }

  Serial.println("Timeout - Closing Gate");
}