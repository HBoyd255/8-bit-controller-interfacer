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
     * @brief Read the raw data from the NES controller.
     *
     * @return The raw data from the NES controller.
     */
    uint8_t readRaw();

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
};

#endif  // NES_CONTROLLER_INTERFACE_H
