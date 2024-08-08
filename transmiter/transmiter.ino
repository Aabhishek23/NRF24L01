#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 7); // CE, CSN pins
const byte address[] = "000001";
bool buttonCheck = 1;

void setup() {
  Serial.begin(9600);
  while (!Serial) { delay(100); }

  delay(5000);

  SPI.setSCK(18);
  SPI.setMOSI(19);
  SPI.setMISO(16);

  Serial.println("Initializing radio...");
  if (!radio.begin()) {
    Serial.println("Radio hardware is not responding!");
    while (1);
  }
  
  radio.openWritingPipe(address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(76); // Ensure the channel is set to the same value on the receiver
  radio.stopListening();

  Serial.println("Transmitter setup done");
  radio.printDetails();
  
  pinMode(4, INPUT);
}

void loop() {
  buttonCheck = digitalRead(4);
  radio.write(&buttonCheck, sizeof(buttonCheck));

  Serial.print("Sent: ");
  Serial.println(buttonCheck);
  delay(1000);
}
