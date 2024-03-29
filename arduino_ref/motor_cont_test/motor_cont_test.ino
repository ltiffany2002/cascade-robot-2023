#define E1 12  // Enable Pin for motor 1
#define E2 11  // Enable Pin for motor 2
 
#define I1 9  // Control pin 1 for motor 1
#define I2 7  // Control pin 2 for motor 1
#define I3 5  // Control pin 1 for motor 2
#define I4 3  // Control pin 2 for motor 2
 
void setup() {
 
    pinMode(E1, OUTPUT);
    pinMode(E2, OUTPUT);
 
    pinMode(I1, OUTPUT);
    pinMode(I2, OUTPUT);
    pinMode(I3, OUTPUT);
    pinMode(I4, OUTPUT);
}
 
void loop() {
 
    digitalWrite(E1, HIGH); // Run in half speed
    digitalWrite(E2, HIGH); // Run in full speed
 
    digitalWrite(I1, HIGH);
    digitalWrite(I2, LOW);
    digitalWrite(I3, HIGH);
    digitalWrite(I4, LOW);
 
    delay(10000);
 
    // change direction
 
    digitalWrite(I1, LOW);
    digitalWrite(I2, HIGH);
    digitalWrite(I3, LOW);
    digitalWrite(I4, HIGH);
 
    delay(10000);
}
