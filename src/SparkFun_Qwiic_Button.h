/******************************************************************************
SparkFun_Qwiic_Button.h
SparkFun Qwiic Button/Switch Library Header File
Fischer Moseley @ SparkFun Electronics
Original Creation Date: July 24, 2019
https://github.com/sparkfunX/

This file prototypes the QwiicButton class, implemented in SparkFun_Qwiic_Button.cpp.

Development environment specifics:
	IDE: Arduino 1.8.9
	Hardware Platform: Arduino Uno/SparkFun Redboard
	Qwiic Button Breakout Version: 1.0.0
    Qwiic Switch Breakout Version: 1.0.0

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Distributed as-is; no warranty is given.
******************************************************************************/

#ifndef __SparkFun_Qwiic_Button_H__
#define __SparkFun_Qwiic_Button_H__

#include <Wire.h>
#include <Arduino.h>
#include "registers.h"

#define DEV_ADDR 0x5F //default device address of the QwiicButton
#define DEV_ID_BTN 0x5D //device ID of the Qwiic Button
#define DEV_ID_SW 0x5E //device ID of the Qwiic Switch

class QwiicButton {
    private:
    TwoWire *_i2cPort;                                                //Generic connection to user's chosen I2C port
    uint8_t _deviceAddress;                                           //I2C address of the button/switch

    public:
    //Device status
    bool begin(uint8_t address = DEV_ADDR, TwoWire &wirePort = Wire); //Sets device I2C address to a user-specified address, over whatever port the user specifies. 
    bool isConnected();                                               //Returns true if the button/switch will acknowledge over I2C, and false otherwise
    uint8_t deviceID();                                               //Return the 8-bit device ID of the attached device.
    bool checkDeviceID();                                             //Returns true if the device ID matches that of either the button or the switch
    uint8_t getDeviceType();                                          //Returns 1 if a button is attached, 2 if a switch is attached. Returns 0 if there is no device attached.
    uint16_t getFirmwareVersion();                                    //Returns the firmware version of the attached device as a 16-bit integer. The leftmost (high) byte is the major revision number, and the rightmost (low) byte is the minor revision number.

    //Button status
    bool isPressed();                                                 //Returns 1 if the button/switch is pressed, and 0 otherwise
    bool hasBeenClicked();                                            //Returns 1 if the button/switch is clicked, and 0 otherwise

    //LED configuration
    bool LEDconfig(uint8_t brightness, uint8_t granularity,
        uint16_t cycleTime, uint16_t offTime);                        //Configures the LED with the given max brightness, granularity (1 is fine for most applications), cycle time, and off time. 
    bool LEDoff();                                                    //Turns the onboard LED off
    bool LEDon(uint8_t brightness = 255);                             //Turns the onboard LED on with specified brightness. Set brightness to an integer between 0 and 255, where 0 is off and 255 is max brightness.

    //Internal I2C Abstraction
    uint8_t readSingleRegister(Qwiic_Button_Register reg);                           //Reads a single 8-bit register.
    uint16_t readDoubleRegister(Qwiic_Button_Register reg);                          //Reads a 16-bit register (little endian).
    bool writeSingleRegister(Qwiic_Button_Register reg, uint8_t data);               //Attempts to write data into a single 8-bit register. Does not check to make sure it was written successfully. Returns 0 if there wasn't an error on I2C transmission, and 1 otherwise.
    bool writeDoubleRegister(Qwiic_Button_Register reg, uint16_t data);              //Attempts to write data into a double (two 8-bit) registers. Does not check to make sure it was written successfully. Returns 0 if there wasn't an error on I2C transmission, and 1 otherwise.
};
#endif