int a, b;
#include <esp_now.h>
#include <WiFi.h>

//Broadcast to said reciever
/**
 * FILL IN THE XXs BELOW WITH YOUR MAC ADDRESS!
 */
uint8_t broadcastAddress[] = {0xXX, 0xXX, 0xXX, 0xXX, 0xXX, 0xXX};
/**
 * FILL IN THE XXs ABOVE WITH YOUR MAC ADDRESS!
 */


#define FORWARD_PIN 12  //FILL IN WITH YOUR BUTTON PIN
#define BACKWARD_PIN 13  //FILL IN WITH YOUR BUTTON PIN
 
typedef struct struct_message {
    int forward;
    int backwards;
} struct_message;

struct_message input_data;

esp_now_peer_info_t peerInfo;

// callback when data is sent
void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(9600);
 
  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Once ESPNow is successfully Init, we will register for Send CB to
  // get the status of Trasnmitted packet
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, broadcastAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  // Add peer        
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }

  //button input pins
  pinMode(FORWARD_PIN, INPUT_PULLUP);
  pinMode(BACKWARD_PIN, INPUT_PULLUP);

}

void loop() {
  //Read in the values of your buttons!
  a = digitalRead(FORWARD_PIN);
  b = digitalRead(BACKWARD_PIN);
  
  //ESP NOW Communication
  input_data.forward = !a;
  input_data.backwards =  !b;
  //Helpful Debugging:
  //Serial.println(!a);
  //Serial.println(!b);
  
  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(broadcastAddress, (uint8_t *) &input_data, sizeof(input_data));
  
  if (result == ESP_OK) {
    Serial.println("Sent with success");
  }
  else {
    Serial.println("Error sending the data");
  }
  
  delay(100);
}
