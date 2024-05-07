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
    // Read the data from the shift register.
    byte data = nes.read();

    // Print the received data to the serial port.
    // printByte(data, ",");

    // Break the byte into its individual bits.
    // The values are inverted because the buttons are pulled low when pressed.
    bool button_a = !(data & 128);
    bool button_b = !(data & 64);
    bool button_select = !(data & 32);
    bool button_start = !(data & 16);
    bool button_up = !(data & 8);
    bool button_down = !(data & 4);
    bool button_left = !(data & 2);
    bool button_right = !(data & 1);

    // if (button_a) {
    //     Serial.println("A");
    // }
    // if (button_b) {
    //     Serial.println("B");
    // }
    // if (button_select) {
    //     Serial.println("SELECT");
    // }
    // if (button_start) {
    //     Serial.println("START");
    // }
    // if (button_up) {
    //     Serial.println("UP");
    // }
    // if (button_down) {
    //     Serial.println("DOWN");
    // }
    // if (button_left) {
    //     Serial.println("LEFT");
    // }
    // if (button_right) {
    //     Serial.println("RIGHT");
    // }

    // This is the configuration for the game Bit Blaster XL
    updateKey(button_a, KEY_LEFT_CTRL);
    updateKey(button_b, KEY_LEFT_ALT);
    updateKey(button_select, KEY_ESC);
    updateKey(button_start, KEY_RETURN);
    updateKey(button_up, KEY_UP_ARROW);
    updateKey(button_down, KEY_DOWN_ARROW);
    updateKey(button_left, KEY_LEFT_ARROW);
    updateKey(button_right, KEY_RIGHT_ARROW);
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
