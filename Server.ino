
/*
  ModbusTCP for W5x00 Ethernet library
  Basic Server code example

  (c)2020 Alexander Emelianov (a.m.emelianov@gmail.com)
  https://github.com/emelianov/modbus-esp8266

  This code is licensed under the BSD New License. See LICENSE.txt for more info.
*/

#include <SPI.h>
#include <Ethernet.h>       // Ethernet library v2 is required
#include <ModbusEthernet.h>

// Enter a MAC address and IP address for your controller below.
byte mac[] = {
  0xdc, 0x4f, 0x22, 0x6d, 0x86, 0x0b
};
IPAddress ip(192, 168, 0, 114); // The IP address will be dependent on your local network:
ModbusEthernet mb;              // Declare ModbusTCP instance

void setup() {
  Serial.begin(115200);  
  delay(2000);   // Open serial communications and wait for port to open
  #if defined(AVR_LEONARDO)
  while (!Serial) {}        // wait for serial port to connect. Needed for Leonardo only
  #endif
  Ethernet.init(4);        // SS pin
  Ethernet.begin(mac, ip);  // start the Ethernet connection
  delay(1000);              // give the Ethernet shield a second to initialize
  mb.server();              // Act as Modbus TCP server
  mb.addReg(HREG(100));     // Add Holding register #100
}

void loop() {
  mb.Hreg(100, 1234); // Example: Setting register 100 to 1234
  mb.task();                // Server Modbus TCP queries
  delay(50);
}