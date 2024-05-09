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
        Serial.println(input.buttonsPressedAsString());
    }

    // This is the configuration for the game Bit Blaster XL.
    updateKey(input.buttonA, KEY_LEFT_CTRL);
    updateKey(input.buttonB, KEY_LEFT_ALT);
    updateKey(input.buttonSelect, KEY_ESC);
    updateKey(input.buttonStart, KEY_RETURN);
    updateKey(input.buttonUp, KEY_UP_ARROW);
    updateKey(input.buttonDown, KEY_DOWN_ARROW);
    updateKey(input.buttonLeft, KEY_LEFT_ARROW);
    updateKey(input.buttonRight, KEY_RIGHT_ARROW);
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
