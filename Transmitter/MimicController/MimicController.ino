// Feather9x_TX
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messaging client (transmitter)
// with the RH_RF95 class. RH_RF95 class does not provide for addressing or
// reliability, so you should only use RH_RF95 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example Feather9x_RX

#include <RHReliableDatagram.h>
#include <RH_RF95.h>
#include <SPI.h>
#include <Speck.h>
#include <RHEncryptedDriver.h>

//for feather m0
#define RFM95_CS 8
#define RFM95_RST 4
#define RFM95_INT 3

// Change to 434.0 or other frequency, must match RX's freq!
#define RF95_FREQ 915.0

// rf95_reliable_datagram_server.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple addressed, reliable messaging server
// with the RHReliableDatagram class, using the RH_RF95 driver to control a RF95 radio.
// It is designed to work with the other example rf95_reliable_datagram_client
// Tested with Anarduino MiniWirelessLoRa, Rocket Scream Mini Ultra Pro with the RFM95W

#define CONTROLLER_ADDRESS 1
#define ROBOT_ADDRESS 2

// Singleton instance of the radio driver
RH_RF95 raw_driver(RFM95_CS, RFM95_INT);
Speck myCipher;
unsigned char encryptkey[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
RHEncryptedDriver driver(raw_driver, myCipher);

// Class to manage message delivery and receipt, using the driver declared above
RHReliableDatagram manager(driver, CONTROLLER_ADDRESS);

// Need this on Arduino Zero with SerialUSB port (eg RocketScream Mini Ultra Pro)
//#define Serial SerialUSB

void setup()
{
    // Rocket Scream Mini Ultra Pro with the RFM95W only:
    // Ensure serial flash is not interfering with radio communication on SPI bus
    //  pinMode(4, OUTPUT);
    //  digitalWrite(4, HIGH);

    Serial.begin(115200);
    while (!Serial)
        ; // Wait for serial port to be available
    if (!manager.init())
        Serial.println("init failed");
    // Defaults after init are 434.0MHz, 13dBm, Bw = 125 kHz, Cr = 4/5, Sf = 128chips/symbol, CRC on

    if (!raw_driver.setFrequency(RF95_FREQ))
    {
        Serial.println("setFrequency failed");
        while (1)
            ;
    }

    myCipher.setKey(encryptkey, sizeof(encryptkey));

    // The default transmitter power is 13dBm, using PA_BOOST.
    // If you are using RFM95/96/97/98 modules which uses the PA_BOOST transmitter pin, then
    // you can set transmitter powers from 5 to 23 dBm:
    raw_driver.setTxPower(23, false);

    Serial.println("Finished init");
}

uint8_t data[] = "I am the first one";
// Dont put this on the stack:
uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];

void loop()
{
    uint8_t len = sizeof(buf);
    uint8_t from;

    if (manager.sendtoWait(data, sizeof(data), ROBOT_ADDRESS))
    {
        Serial.println("Controller received a message");
        // Now wait for a reply from the server
        uint8_t len = sizeof(buf);
        uint8_t from;
        if (manager.recvfromAckTimeout(buf, &len, 2000, &from))
        {
            /*Serial.print("got reply from : 0x");
            Serial.print(from, HEX);
            Serial.print(": ");
            Serial.println((char *)buf);*/
            Serial.println(String(from));
        }
        else
        {
            connect();
        }
    }
    else
        Serial.println("sendtoWait failed");
    delay(500);
}

bool connect()
{
    while (!manager.sendtoWait(data, sizeof(data), ROBOT_ADDRESS))
    {
        Serial.println("Controller not found");
    }
    return true;
}
