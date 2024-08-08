#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 7); // CE, CSN pins
const byte address[] = "000001";
bool buttonState = 0;

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

  radio.openReadingPipe(1, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.setChannel(76); // Ensure the channel is set to the same value on the transmitter
  radio.startListening();

  Serial.println("Receiver setup done");
  radio.printDetails();
}

void loop() {
  if (radio.available()) {
    radio.read(&buttonState, sizeof(buttonState));
    Serial.print("Button state: ");
    Serial.println(buttonState);
  } else {
    Serial.println("Radio not available");
  }
  delay(1000); // Adding a small delay to avoid flooding the serial monitor
}
