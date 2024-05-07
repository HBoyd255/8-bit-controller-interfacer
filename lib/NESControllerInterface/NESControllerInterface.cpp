/**
 * @file NESControllerInterface.cpp
 * @brief Definitions for the NES controller interface class.
 *
 * @author Harry Boyd - https://github.com/HBoyd255
 * @date 2024-05-07
 * @copyright Copyright (c) 2024
 */
#include "NESControllerInterface.h"

/**
 * @brief Construct a new NESControllerInterface object.
 *
 * @param dataPin The pin connected to the data pin on the shift register.
 * @param loadPin The pin connected to the load pin on the shift register.
 * @param clockPin The pin connected to the clock pin on the shift register.
 */
NESControllerInterface::NESControllerInterface(uint8_t dataPin, uint8_t loadPin,
                                               uint8_t clockPin)
    : _dataPin(dataPin), _loadPin(loadPin), _clockPin(clockPin) {
    pinMode(dataPin, INPUT);
    pinMode(loadPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
}

/**
 * @brief Read the raw data from the NES controller.
 *
 * @return The raw data from the NES controller.
 */
uint8_t NESControllerInterface::readRaw() {
    // Create a byte for storing the received data from the shift register.
    byte shiftRegisterContents = 0;

    // Load the data into the shift register by sending a pulse to the load
    // pin.
    digitalWrite(this->_loadPin, LOW);
    delayMicroseconds(10);
    digitalWrite(this->_loadPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(this->_loadPin, LOW);

    // For of the 8 bits in a byte.
    for (int i = 0; i < 8; i++) {
        // Shift the received data up by one.
        shiftRegisterContents <<= 1;

        // Load the available bit from the shift register into the lsb of
        // the received data byte.
        shiftRegisterContents |= digitalRead(this->_dataPin);

        // Pulse the clock pin to shift the data inside the shift register.
        digitalWrite(this->_clockPin, LOW);
        delayMicroseconds(10);
        digitalWrite(this->_clockPin, HIGH);
        delayMicroseconds(10);
    }
    return shiftRegisterContents;
}