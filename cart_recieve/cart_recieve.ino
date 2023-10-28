//Simple forward-backwards cart

// ESP-NOW Communication Setup
#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
    int forward;
    int backwards;
} struct_message;

struct_message input_data;

#define EA 3  // Enable Pin for motor 1
#define EB 12  // Enable Pin for motor 2
 
#define A1 5  // Control pin 1 for motor 1
#define A2 7  // Control pin 2 for motor 1
#define B1 9  // Control pin 1 for motor 2
#define B2 11  // Control pin 2 for motor 2
 
void setup() {
    pinMode(LED_BUILTIN, OUTPUT);

    //setup serial monitor
    Serial.begin(9600);

    //setup motor controller pins
    pinMode(EA, OUTPUT);
    pinMode(EB, OUTPUT);
    pinMode(A1, OUTPUT);
    pinMode(A2, OUTPUT);
    pinMode(B1, OUTPUT);
    pinMode(B2, OUTPUT);
    //Turn on motor controller
    digitalWrite(EA, HIGH);
    digitalWrite(EB, HIGH); 

    //Setup communication
    WiFi.mode(WIFI_STA);
    if (esp_now_init() != ESP_OK) {
      Serial.println("Error initializing ESP-NOW");
      return;
    }
    
    //register for the reciever to get the packet information
    esp_now_register_recv_cb(OnDataRecv);
}
 
void loop(){
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&input_data, incomingData, sizeof(input_data));
  
  if (input_data.forward) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(A1, HIGH);
    digitalWrite(A2, LOW);
    digitalWrite(B1, HIGH);
    digitalWrite(B2, LOW);
  } else if (input_data.backwards) {
    digitalWrite(LED_BUILTIN, HIGH);
    digitalWrite(A1, LOW);
    digitalWrite(A2, HIGH);
    digitalWrite(B1, LOW);
    digitalWrite(B2, HIGH);
  } else {
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(A1, LOW);
    digitalWrite(A2, LOW);
    digitalWrite(B1, LOW);
    digitalWrite(B2, LOW);
  }
 
}
