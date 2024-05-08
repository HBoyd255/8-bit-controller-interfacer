/**
 * @file main.cpp
 * @brief This is the top-level file for the NES to USB HID converter.
 *
 * @author Harry Boyd - https://github.com/HBoyd255
 * @date 2024-05-07
 * @copyright Copyright (c) 2024
 */

#include <Arduino.h>
#include <Keyboard.h>
#include <NESControllerInterface.h>

#include "pinDefinitions.h"

// https://www.arduino.cc/reference/en/language/functions/usb/keyboard/keyboardmodifiers/

void printByte(byte, String);
void updateKey(bool pressed, unsigned char key);

NESControllerInterface nes(DATA_PIN, LOAD_PIN, CLOCK_PIN);

void setup() {
    // Begin serial communication.
    Serial.begin(9600);

    Keyboard.begin();
}

void loop() {
    // Get the data from the NES controller, as a struct.
    NESInput input = nes.getNESInput();

    if (input.anyButtonPressed()) {
        Serial.println("Something was pressed.");
    }

    if (input.buttonA) {
        Serial.println("A");
    }
    if (input.buttonB) {
        Serial.println("B");
    }
    if (input.buttonSelect) {
        Serial.println("SELECT");
    }
    if (input.buttonStart) {
        Serial.println("START");
    }
    if (input.buttonUp) {
        Serial.println("UP");
    }
    if (input.buttonDown) {
        Serial.println("DOWN");
    }
    if (input.buttonLeft) {
        Serial.println("LEFT");
    }
    if (input.buttonRight) {
        Serial.println("RIGHT");
    }

    // This is the configuration for the game Bit Blaster XL.
    // updateKey(input.buttonA, KEY_LEFT_CTRL);
    // updateKey(input.buttonB, KEY_LEFT_ALT);
    // updateKey(input.buttonSelect, KEY_ESC);
    // updateKey(input.buttonStart, KEY_RETURN);
    // updateKey(input.buttonUp, KEY_UP_ARROW);
    // updateKey(input.buttonDown, KEY_DOWN_ARROW);
    // updateKey(input.buttonLeft, KEY_LEFT_ARROW);
    // updateKey(input.buttonRight, KEY_RIGHT_ARROW);
}

/**
 * @brief Prints a byte of data as its individual bits.
 *
 * This function takes a byte and prints it to the serial port as its
 * individual 8 bits, starting with the most significant bit on the left.
 * Any leading zeros of the data are also printed. A separator can also be
 * provided to separate the bits, but is not required.
 *
 * for example,printByte(13) would print 00001101. and printByte(13,",")
 * would print 0,0,0,0,1,1,0,1.
 *
 * This function assumes that a serial connection has been initialised.
 *
 * @param byteToPrint The unsigned 8 bits of data to print to the serial
 * port.
 * @param separator The string to be printed between each bit.
 */
void printByte(byte byteToPrint, String separator = "e") {
    // Print the 7 leading bits of the byte, followed by the optional
    // separator.
    for (byte b = 7; b != 0; b--) {
        Serial.print((byteToPrint >> b) & 1);
        Serial.print(separator);
    }
    // Print the final bit, followed by a newline character.
    Serial.println(byteToPrint & 1);
}

/**
 * @brief Updates the state of a key on the keyboard.
 *
 * @param key The key to update, as defined in the Keyboard library.
 * @param pressed Whether the key is pressed or released.
 */
void updateKey(bool pressed, unsigned char key) {
    if (pressed) {
        Keyboard.press(key);
    } else {
        Keyboard.release(key);
    }
}
