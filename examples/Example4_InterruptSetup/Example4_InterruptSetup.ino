/******************************************************************************
Configures the button to raise an interrupt when pressed, and notifies us over
serial. Also allows us to enable/disable/reset the interrupt too!

Fischer Moseley @ SparkFun Electronics
Original Creation Date: July 29, 2019

This code is beerware; if you see me (or any other SparkFun employee) at the
local, and you've found our code helpful, please buy us a round!

Hardware Connections:
Attach the Qwiic Shield to your Arduino/Photon/ESP32 or other
Plug the button into the shield
Print it to the serial monitor at 115200 baud.

Distributed as-is; no warranty is given.
******************************************************************************/

#include <SparkFun_Qwiic_Button.h>
QwiicButton button;

void setup(){
    Serial.begin(115200);
    Wire.begin(); //Join I2C bus
    Wire.setClock(400000);
    button.begin();

    //check if button will acknowledge over I2C
    if(button.isConnected()){
        Serial.println("Device will acknowledge!");
    }

    else {
        Serial.println("Device did not acknowledge! Freezing.");
        while(1);
    }

    button.resetInterruptConfig(); //reset all the interrupt configuration stuff to defaults, so we have a clean slate to work with!
    button.enablePressedInterrupt(); //configure the interrupt to trigger when we press the button
}

void loop(){
    if(button.interruptTriggered()){
        Serial.println("Interrupt Triggered!");
    }

    else {
        Serial.println("Interrupt Not Triggered");
    }

    if(Serial.available()){
        uint8_t recieved = Serial.read();
        if(recieved == 'r' || recieved == 'R') { //if the user has send either r or R over serial, then reset the interrupt!
            Serial.println("Resetting Interrupt...");
            button.clearInterrupt();
        }
        if(recieved == 'd' || recieved == 'D') {
            Serial.println("Disabling Interrupt...");
            button.disablePressedInterrupt();
        }

        if(recieved == 'e' || recieved == 'E') {
            Serial.println("Enabling Interrupt...");
            button.enablePressedInterrupt();
        }
    }
    delay(20); //let's not hammer too hard on the I2C bus
}