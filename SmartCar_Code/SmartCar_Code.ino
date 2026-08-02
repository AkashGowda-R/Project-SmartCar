#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

// ---------------- LCD ----------------
LiquidCrystal_I2C lcd(0x27, 16, 2);

// ---------------- Servo ----------------
Servo gateServo;

// ---------------- IR Sensors ----------------
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
  Serial.begin(9600);

  Serial.println("=================================");
  Serial.println(" SMART CAR PARKING SYSTEM ");
  Serial.println("=================================");

  // Sensor pins
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

  // ---------------- PROJECT DISPLAY ----------------
  lcd.setCursor(0, 0);
  lcd.print("  SMART CAR"); 
  
  lcd.setCursor(0, 1);
  lcd.print("PARKING SYSTEM");

  delay(2500);

  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("  PROJECT DONE");

  lcd.setCursor(0, 1);
  lcd.print("      BY");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("    AKASH R");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DHANANJAYA K M");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("DHARANI DHARAN R");

  delay(2000);
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("    WELCOME");

  delay(2000);
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

  // ---------------- PARKING FULL ----------------
  if (totalFilled >= 4)
  {
    closeGate();

    Serial.println("   PARKING FULL");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("  PARKING FULL");

    lcd.setCursor(0, 1);
    lcd.print("    NO SPACE");

    delay(5000);
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

    // ---------------- 2 SECOND DELAY ----------------
    delay(500);

    // Close gate
    Serial.println("Closing Gate");

    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("CLOSING GATE");

    closeGate();

    delay(500);
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
  gateServo.write(0);

  gateOpened = true;

  Serial.println("Gate Opened");

  delay(500);
}

// ======================================================
// FUNCTION: CLOSE GATE
// ======================================================
void closeGate()
{
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

  // Wait max 5 seconds
  while (millis() - startTime < 5000)
  {
    if (digitalRead(gatePassSensor) == LOW)
    {
      Serial.println("Vehicle Passing Gate");

      while (digitalRead(gatePassSensor) == LOW)
      {
        delay(50);
      }

      Serial.println("Vehicle Crossed");

      return;
    }

    delay(50);
  }

  Serial.println("Timeout - Closing Gate");
}