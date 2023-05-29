# SmartOTPDoorLock


See wiki page for the detailed description of the project.

How to build: 
In order to build our project, you need to download the header files under the Inc directory, and the c files under the Src directory, and load them on the microcontroller. For the hardware part, you should do the following:
* LCD: Connected to I2C1
* Bluetooth module: Connected to UART2
* Alarm: Connected to PB0 GPIO output pin
* Servo Motor: Connected to TIM1_CH1 (PA8)
* Keypad: Uses PA12,PA11,PA0,PA4 as inputs and PA5,PA6,PA7,PA1 as outputs
You can see the circuit in the wiki page. 

## Setting up the environment.
After making the correct connections. To build the project, create a Keil uVision project containing the header files and the c code to load to the target.

## Interacting with the system
To use the system, you will need to connect to the bluetooth module, using any bluetooth application. To generate a password, send any character through the bluetooth command line, and a generated password will appear on the LCD. The password can be used only one time through the keypad, after which it will expire and a new password will need to be generated. A master password, which is "12345", is a permanent password that does not expire.

How to use:
Use this project in homes to automate the security system.


## External Library
* Liquid Crystal Library for I2C LED
* HAL library

## Repo

The Inc file includes all the header files needed for the project.
The Src files includes the code used to interact with the diffrent periphals and store the pasword, and the needed libraries for the HAL interface and Liquid Crystal for the LCD.




