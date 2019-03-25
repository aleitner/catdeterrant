#include <require_cpp11.h>
#include <MFRC522.h>
#include <deprecated.h>
#include <MFRC522Extended.h>
#include <Servo.h>
#include <SPI.h>

#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);	// Create MFRC522 instance.

#define COSMO 7267
Servo myservo;

void setup() {
  Serial.begin(9600);	// Initialize serial communications with the PC
  SPI.begin();			// Init SPI bus
  mfrc522.PCD_Init();	// Init MFRC522 card

  myservo.attach(8);  // attaches the servo on pin 8 to the servo object
  delay(1000);
  myservo.write(180);

  Serial.println("Scan PICC to see UID and type...");
}

void loop() {
  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;//go to start of loop if there is no card present
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;//if ReadCardSerial returns 1, the "uid" struct contains the ID of the read card.
  }


  unsigned long uid = getID();
  if (uid != -1) {
    Serial.print("Card detected, UID: "); Serial.println(uid);
    if (uid == COSMO) {
      Serial.println("Hi Cosmo!!");
      squirt_it();
      squirt_it();
    }
  }
}

unsigned long getID() {
  unsigned long hex_num;
  hex_num =  mfrc522.uid.uidByte[0] << 24;
  hex_num += mfrc522.uid.uidByte[1] << 16;
  hex_num += mfrc522.uid.uidByte[2] <<  8;
  hex_num += mfrc522.uid.uidByte[3];
  mfrc522.PICC_HaltA(); // Stop reading
  return hex_num;
}

void squirt_it() {
  Serial.println("squirt");
  myservo.write(120 );
  Serial.println(120);
  delay(1000);                       // waits for the servo to reach the position
  myservo.write(180);
  Serial.println(180);
  delay(1000);                       // waits for the servo to reach the position
}
