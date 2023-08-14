#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

const int RELAY_PIN = 4;
const int ACCESS_DELAY = 3000; // Keep lock unlocked for 3 seconds

void setup() {
  // Set up the fingerprint sensor
  finger.begin(57600);
  delay(5);
  
  // Verify the password
  if (!finger.verifyPassword()) {
    while (1) { delay(1); }
  }

  // Set up the relay module
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, HIGH); // Switch off relay initially

  // Set up the serial monitor
  Serial.begin(9600);
  
  // Print the Excel labels
  Serial.println("CLEARDATA");//clear excel sheet
  Serial.println("LABEL,Time,ID,Name");
}

void loop() {
  // Get the fingerprint ID
  int fingerprintId = getFingerprintId();
  
  // If a fingerprint is detected
  if (fingerprintId != -1) {
    // Get the user's name and ID
    String userName = "";
    int userId = 0;
    
    if (fingerprintId == 1) {
      userName = "Supriya";
      userId = 1;
    } else if (fingerprintId == 2) {
      userName = "Lathasri";
      userId = 2;
    }
    else if (fingerprintId == 3) {
      userName = "Akanksha";
      userId = 3;
    }
    else if (fingerprintId == 4) {
      userName = "Jeevitha"; 
      userId = 4;
    }
    else if (fingerprintId == 6) {
      userName = "Yellesh";
      userId = 6;
    }
    
    
    // Get the current time
    unsigned long currentTime = millis();

    // Unlock the relay module
    digitalWrite(RELAY_PIN, LOW);
    Serial.print("DATA,TIME,");
    Serial.print(userId);
    Serial.print(",");
    Serial.println(userName);
    
    delay(ACCESS_DELAY);
    
    // Lock the relay module
    digitalWrite(RELAY_PIN, HIGH);
    
    // Log attendance on the serial monitor with Excel labels
    
  }  
  
  // Add some delay before the next scan
  delay(50);
}

// Returns -1 if no fingerprint is detected, otherwise returns the fingerprint ID
int getFingerprintId() {
  int result = finger.getImage();
  if (result != FINGERPRINT_OK)  return -1;

  result = finger.image2Tz();
  if (result != FINGERPRINT_OK)  return -1;

  result = finger.fingerFastSearch();
  if (result != FINGERPRINT_OK)  return -1;

  // Found a match!
  return finger.fingerID;
}
