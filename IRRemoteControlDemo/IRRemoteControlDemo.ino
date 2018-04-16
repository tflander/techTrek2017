/*
   IRsend: IRRemoteControlDemo - demonstrates receiving/sending IR codes.
   Created by Cristiano Borges - STI - Fatesg
   August, 2017
*/

#include "IRRemoteControl.h"

IRRecv irRecv;
IRSend irSend;

const int IR_RECV_PIN = 2;

const int MAX_IR_BUFFER_LENGTH = 200;
unsigned int irBuffer[MAX_IR_BUFFER_LENGTH];
int currentIrBufferLength = 0;

const int FREQ_KHZ = 40;

void setup() {
  Serial.begin(9600);
  pinMode(LED_BUILTIN, OUTPUT);
  irRecv.start(IR_RECV_PIN, irBuffer, MAX_IR_BUFFER_LENGTH, currentIrBufferLength);
}

void showIrBuffer() {
  Serial.println();
  Serial.print(F("Codelen: "));
  Serial.print(currentIrBufferLength);
  Serial.print(F("; Code: "));
  Serial.println();

  for (int i = 0; i < currentIrBufferLength; i++) {
    if (i > 0) {
      Serial.print(F(", "));
    }
    Serial.print(irBuffer[i]);
  }

  Serial.println();
}

void showIrBufferCodeForFireplaceRemote() {
  Serial.println();
  if (currentIrBufferLength != 99) {
    Serial.print("Expected buffer length 99, found ");
    Serial.print(currentIrBufferLength);
    Serial.println();
    return;
  }

  if ( irBuffer[0] < 9100 || 9300 < irBuffer[0]) {
    Serial.print("Expected first buffer byte to be 9100-9300, found ");
    Serial.print(irBuffer[0]);
    Serial.println();
    return;
  }

  if ( irBuffer[1] < 4700 || 4800 < irBuffer[1]) {
    Serial.print("Expected second buffer byte to be 4700-4800, found ");
    Serial.print(irBuffer[1]);
    Serial.println();
    return;
  }

  int count = 0;
  int previousBufferValue = -1;
  for (int i = 2; i < currentIrBufferLength; ++i) {

    if (1600 < irBuffer[i] && irBuffer[i] < 2000) {
      ++count;
    } else if (irBuffer[i] < 800) {
      if (previousBufferValue < 800) {
        // output count and reset
        if (count > 0) {
          Serial.print(count);
        }
        count = 0;
      } else {
        // skip one low value
      }
    } else {
      // invalid read
      Serial.print("Found unexpected value in irBuffer ");
      Serial.print(irBuffer[i]);
      Serial.println();
      return;
    }

    previousBufferValue = irBuffer[i];


  } // end for loop

  Serial.println();
}

void loop() {
  Serial.println(F("Press the remote control button now - only once"));
  delay(5000);

  if (currentIrBufferLength > 0) {
    irRecv.stop(IR_RECV_PIN);

    digitalWrite(LED_BUILTIN, HIGH);

    //    showIrBuffer();
    showIrBufferCodeForFireplaceRemote();

    digitalWrite(LED_BUILTIN, LOW);

    irRecv.start(IR_RECV_PIN, irBuffer, MAX_IR_BUFFER_LENGTH, currentIrBufferLength);
  }
}
