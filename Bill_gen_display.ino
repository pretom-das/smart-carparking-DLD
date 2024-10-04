#include <Wire.h> // Required for I2C communication
#include <LCD_I2C.h>
LCD_I2C lcd(0x27);
#include <Servo.h>

Servo myServo; // Create a servo object
const int servoPin = 9; // Pin connected to the servo
const int bill_ir = 11; // ir responsivle for bill generaton, 
const int ex_ir = 10; // for external IR sensor
const int max = 8; // if the capacity is full
unsigned long startTime = 0; // To store start time
unsigned long elapsedTime = 0; // Elapsed time in milliseconds
float billAmount = 0.0; // Bill amount (initialized to 0)


void setup() {
  pinMode(bill_ir, INPUT); // Set pin 11 as an input
  pinMode(servoPin, OUTPUT); // Set pin 9 as an input for servo
  pinMode(ex_ir, INPUT); // Set pin 11 as an input
  pinMode(max, INPUT); // Set pin 8 as an input
  lcd.begin(); // If you are using more I2C devices using the Wire library use lcd.begin(false)
              // this stop the library(LCD_I2C) from calling Wire.begin(
  lcd.backlight();
  lcd.setCursor(4, 0);
  lcd.print("Pretom");
  myServo.attach(servoPin); // Attach the servo to the specified pin
  myServo.write(0); // Set initial position (0 degrees)
  
}

void servo(){
  int state1 = digitalRead(ex_ir); // Read the state of pin 9 for servo ir
  int state_max = digitalRead(max);
  // red is vcc, brown is gnd and orange is output 
// for servo motor
  if (state1 == HIGH && state_max == LOW) {
    // Pin 9 is high, move servo 90 degrees clockwise
    myServo.write(90);
  } else {
    // Pin 9 is low, return servo to initial position
    myServo.write(0);
  }
  delay(2000);
}

void loop() {

  servo();
  int state = digitalRead(bill_ir); // Read the state of pin 11

// for bill generation
  if (state == HIGH) {
    // Pin 11 is high, start the timer
    startTime = millis();
  } else {
    // Pin 11 is low, stop the timer
    elapsedTime = millis() - startTime;
    billAmount = 0.01667 * (elapsedTime / 1000.0); // Convert to seconds and multiply by 2

    // Display elapsed time and bill amount
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time(s): ");
    lcd.setCursor(0, 1);
    lcd.print(elapsedTime / 1000.0, 2); // Print elapsed time with 2 decimal places

    lcd.setCursor(9, 0);
    lcd.print("Bill:");
    lcd.setCursor(9, 1);

    lcd.print(billAmount, 2); // Print bill amount with 2 decimal places
    billAmount = 0.0; // Reset bill amount
  }
}


//connection
//SCL to the last D pin and SDA at the secon last D pin