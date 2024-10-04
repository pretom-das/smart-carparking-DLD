const int pin11 = 11; // Pin 11
unsigned long startTime = 0; // To store start time
unsigned long elapsedTime = 0; // Elapsed time in milliseconds
float billAmount = 0.0; // Bill amount (initialized to 0)

void setup() {
  pinMode(pin11, INPUT); // Set pin 11 as an input
  Serial.begin(9600); // Initialize serial communication
}

void loop() {
  int state = digitalRead(pin11); // Read the state of pin 11

  if (state == LOW) {
    // Pin 11 is high, start the timer
    startTime = millis();
  } else {
    // Pin 11 is low, stop the timer
    elapsedTime = millis() - startTime;
    billAmount = 1.66 * (elapsedTime / 60000.0); // Convert to mins and multiply by 
    Serial.print("Elapsed time (s): ");
    Serial.println(elapsedTime / 1000.0);
    Serial.print("Bill amount: ৳");
    Serial.println(billAmount, 2); // Print with 2 decimal places
    billAmount = 0.0; // Reset bill amount
  }
}
