/**
 * @file NESControllerInterface.h
 * @brief This file contains the declarations for the NES controller interface
 * class.
 *
 * @author Harry Boyd - https://github.com/HBoyd255
 * @date 2024-05-07
 * @copyright Copyright (c) 2024
 */
#ifndef NES_CONTROLLER_INTERFACE_H
#define NES_CONTROLLER_INTERFACE_H

#include <Arduino.h>

/**
 * @brief A bitfield struct to store the values of the NES controller buttons.
 *
 * Storing this as a bitfield struct saves memory, as each boolean value would
 * take up a byte if stored individually.
 */
struct NESInput {
    bool buttonA : 1;
    bool buttonB : 1;
    bool buttonSelect : 1;
    bool buttonStart : 1;
    bool buttonUp : 1;
    bool buttonDown : 1;
    bool buttonLeft : 1;
    bool buttonRight : 1;

    /**
     * @brief Check if any button is pressed.
     *
     * @return true If any button is pressed.
     * @return false If no buttons are pressed.
     */
    bool anyButtonPressed();

    /**
     * @brief Get a string representing the state of the NESInput object.
     *
     * @return String representing the state of the NESInput object.
     */
    String statesAsString();

    /**
     * @brief Get a string representing the buttons that are pressed.
     *
     * @return String representing the buttons that are pressed.
     */
    String buttonsPressedAsString();
};

/**
 * @brief This class is used to interface with an NES controller using a 4021
 * shift register.
 */
class NESControllerInterface {
   public:
    /**
     * @brief Construct a new NESControllerInterface object.
     *
     * @param dataPin The pin connected to the data pin on the shift register.
     * @param loadPin The pin connected to the load pin on the shift register.
     * @param clockPin The pin connected to the clock pin on the shift register.
     */
    NESControllerInterface(uint8_t dataPin, uint8_t loadPin, uint8_t clockPin);

    /**
     * @brief Read the data from the NES controller as a byte. If the controller
     * is disconnected, 255 will be returned.
     *
     * @return The data from the NES controller.
     */
    uint8_t read();

    /**
     * @brief Get the NESInput object, representing the state of the NES
     * controller.
     *
     * @return NESInput The state of the NES controller's buttons.
     */
    NESInput getNESInput();

   private:
    /**
     * @brief The pin connected to the data pin on the shift register.
     */
    uint8_t _dataPin;
    /**
     * @brief The pin connected to the load pin on the shift register.
     */
    uint8_t _loadPin;
    /**
     * @brief The pin connected to the clock pin on the shift register.
     */
    uint8_t _clockPin;

    /**
     * @brief Read the raw data from the NES controller.
     *
     * @return The raw data from the NES controller.
     */
    uint8_t _readRaw();
};

#endif  // NES_CONTROLLER_INTERFACE_H
