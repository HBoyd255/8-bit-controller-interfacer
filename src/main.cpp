

#include <Arduino.h>

#include "pinDefinitions.h"

byte read8BitShiftReg();
void printByte(byte, String);

void setup() {
    // Begin serial communication.
    Serial.begin(9600);

    // Define pin modes.
    pinMode(DATA_PIN, INPUT);
    pinMode(LOAD_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
}

void loop() {
    byte data = read8BitShiftReg();

    printByte(data, ",");
}

/**
 * @brief Reads the data from the a 8-bit shift register.
 *
 * @return (byte) The data from the a 8-bit shift register.
 */
byte read8BitShiftReg() {
    // Create a byte for storing the received data from the shift register.
    byte shiftRegisterContents = 0;

    // Load the data into the shift register by sending a pulse to the load pin.
    digitalWrite(LOAD_PIN, LOW);
    delayMicroseconds(10);
    digitalWrite(LOAD_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(LOAD_PIN, LOW);

    // For of the 8 bits in a byte.
    for (int i = 0; i < 8; i++) {
        // Shift the received data up by one.
        shiftRegisterContents <<= 1;

        // Load the available bit from the shift register into the lsb of the
        // received data byte.
        shiftRegisterContents |= digitalRead(DATA_PIN);

        // Pulse the clock pin to shift the data inside the shift register.
        digitalWrite(CLOCK_PIN, LOW);
        delayMicroseconds(10);
        digitalWrite(CLOCK_PIN, HIGH);
        delayMicroseconds(10);
    }
    return shiftRegisterContents;
}

/**
 * @brief Prints a byte of data as its individual bits.
 *
 * This function takes a byte and prints it to the serial port as its
 * individual 8 bits, starting with the most significant bit on the left. Any
 * leading zeros of the data are also printed. A separator can also be provided
 * to separate the bits, but is not required.
 *
 * for example,printByte(13) would print 00001101. and printByte(13,",") would
 * print 0,0,0,0,1,1,0,1.
 *
 * This function assumes that a serial connection has been initialised.
 *
 * @param byteToPrint The unsigned 8 bits of data to print to the serial port.
 * @param separator The string to be printed between each bit.
 */
void printByte(byte byteToPrint, String separator = "e") {
    // Print the 7 leading bits of the byte, followed by the optional separator.
    for (byte b = 7; b != 0; b--) {
        Serial.print((byteToPrint >> b) & 1);
        Serial.print(separator);
    }
    // Print the final bit, followed by a newline character.
    Serial.println(byteToPrint & 1);
}
