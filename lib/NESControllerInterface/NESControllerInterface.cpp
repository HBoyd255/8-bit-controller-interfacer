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
    pinMode(dataPin, INPUT_PULLUP);
    pinMode(loadPin, OUTPUT);
    pinMode(clockPin, OUTPUT);
}
/**
 * @brief Read the data from the NES controller as a byte. If the up and
 * down buttons are pressed at the same time, or the left and right buttons
 * are pressed at the same time, the function will return 255, to indicate
 * that the controller is disconnected.
 *
 * @return The data from the NES controller.
 */
uint8_t NESControllerInterface::read() {
    uint8_t rawData = this->_readRaw();

    bool up_pressed = (!(rawData & 8));
    bool down_pressed = (!(rawData & 4));
    bool left_pressed = (!(rawData & 2));
    bool right_pressed = (!(rawData & 1));

    if (up_pressed && down_pressed) {
        return 255;
    } else if (left_pressed && right_pressed) {
        return 255;
    }

    return rawData;
}

/**
 * @brief Read the raw data from the NES controller.
 *
 * @return The raw data from the NES controller.
 */
uint8_t NESControllerInterface::_readRaw() {
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