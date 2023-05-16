/*
  Rui Santos
  Complete project details at our blog.
    - ESP32: https://RandomNerdTutorials.com/esp32-firebase-realtime-database/
    - ESP8266: https://RandomNerdTutorials.com/esp8266-nodemcu-firebase-realtime-database/
  Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files.
  The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.
  Based in the RTDB Basic Example by Firebase-ESP-Client library by mobizt
  https://github.com/mobizt/Firebase-ESP-Client/blob/main/examples/RTDB/Basic/Basic.ino
*/

#include <String.h>
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#endif
#include <Firebase_ESP_Client.h>

//Provide the token generation process info.
#include "addons/TokenHelper.h"
//Provide the RTDB payload printing info and other helper functions.
#include "addons/RTDBHelper.h"

// Insert your network credentials
#define WIFI_SSID "Farag"
#define WIFI_PASSWORD "88888888"

// Insert Firebase project API Key
#define API_KEY "AIzaSyB7xzN9xLaINlMB6f-A48vMTdAVshjyGN0"

// Insert RTDB URLefine the RTDB URL */
#define DATABASE_URL "https://smart-otp-lock-system-default-rtdb.firebaseio.com/" 

// Insert RX/TX for UART2
#define RXp2 16
#define TXp2 17

//Define Firebase Data object
FirebaseData fbdo;

FirebaseAuth auth;
FirebaseConfig config;

unsigned long sendDataPrevMillis = 0;
int count = 0;
bool signupOK = false;

String path;
String read_data;
String passwordReceived = "00000";
String passwords[5];
bool fetched = false;
int i = 0;

void setup(){
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXp2, TXp2);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(300);
  }
  Serial.println();
  Serial.print("Connected with IP: ");
  Serial.println(WiFi.localIP());
  Serial.println();

  /* Assign the api key (required) */
  config.api_key = API_KEY;

  /* Assign the RTDB URL (required) */
  config.database_url = DATABASE_URL;

  /* Sign up */
  if (Firebase.signUp(&config, &auth, "", "")){
    Serial.println("ok");
    signupOK = true;
  }
  else{
    Serial.printf("%s\n", config.signer.signupError.message.c_str());
  }

  /* Assign the callback function for the long running token generation task */
  config.token_status_callback = tokenStatusCallback; //see addons/TokenHelper.h
  
  Firebase.begin(&config, &auth);
  Firebase.reconnectWiFi(true);
}

void sendBit(bool bitValue) {
  // Convert the bit value to a byte
  uint8_t byteToSend = bitValue ? 0xFF : 0x00;

  // Send the byte
  Serial2.write(byteToSend);
}

void fetchPasswords(){
  i = 0;
  if (Firebase.ready() && signupOK && (millis() - sendDataPrevMillis > 8000 || sendDataPrevMillis == 0))
  {
    sendDataPrevMillis = millis();
    if (Firebase.RTDB.getString(&fbdo, "/passwords"))
    {
        // path = "/passwords/" + fbdo.stringData() + "/password";
        // if (Firebase.RTDB.getString(&fbdo, path))
        // {
        read_data = fbdo.stringData();
        Serial.print("Data received: ");
        Serial.println(read_data); //print the data received from the Firebase database
        // }
    }
    else
    {
      Serial.println(fbdo.errorReason()); //print he error (if any)
    }
    int dataIndex = read_data.indexOf('{');  // Find the starting index of the data object

    while (dataIndex != -1) {
      int passwordIndex = read_data.indexOf("\"password\":\"", dataIndex);  // Find the starting index of the password value
      if (passwordIndex == -1) {
        break;  // No more password values found
      }

      int passwordEndIndex = read_data.indexOf("\"", passwordIndex + 12);  // Find the ending index of the password value
      String password = read_data.substring(passwordIndex + 12, passwordEndIndex);  // Extract the password value
      Serial.println("Password: " + password);
      passwords[i] = password;
      i++;
      dataIndex = read_data.indexOf('{', passwordEndIndex);  // Find the starting index of the next data object
    }
  }
  fetched = true;
}

void loop(){
  if (!fetched)
    fetchPasswords();

  Serial.println("Password Received: ");
    passwordReceived = Serial2.readString();
  
  for (int j = 0; j < 5; j++)
  {
    if (passwordReceived == passwords[j])
    {
      if (passwordReceived != NULL)
        {
          Serial.print("-------sending 1 ----------");
          Serial.print(passwordReceived);
          Serial.print(passwords[j]);
          sendBit(1);
          delay(2000);
          sendBit(0);
          passwordReceived = "00000";
        }
    }
    else
    {
      Serial.println("-------sending 0 ----------");
      sendBit(0);
    }
  }
  fetched = false;
}