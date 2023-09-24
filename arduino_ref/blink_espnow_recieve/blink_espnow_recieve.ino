//ESP-NOW test code with Blink
//Reciever code

// ESP-NOW Communication Setup
#include <esp_now.h>
#include <WiFi.h>

typedef struct struct_message {
    bool is_on;
} struct_message;

struct_message input_data;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);

  Serial.begin(115200);

  WiFi.mode(WIFI_STA);
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  //register for the reciever to get the packet information
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  
}

void OnDataRecv(const uint8_t * mac, const uint8_t *incomingData, int len) {
  memcpy(&input_data, incomingData, sizeof(input_data));
  digitalWrite(LED_BUILTIN, input_data.is_on);
}
