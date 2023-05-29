# SmartOTPDoorLock


## Proposal

Our proposed project aims to digitalize home locks. Traditional systems often require physical keys that can be lost or duplicated or one set passcode, which can be easily forgotten or stolen. Our smart lock system with OTP functionality solves this problem by allowing owners to grant access to guests through a one-time password that works only during a specific time frame, ensuring security and convenience. The system also has the option of generating a random passcode and sending it to the owner every set period of time. Additionally, the system has a feature of taking a picture if someone entered the password more than a set number of times and sending it to the owner. Our proposed solution provides a reliable and user-friendly alternative to traditional lock systems.


## External Library
* Liquid Crystal Library for I2C LED
* HAL library

##Repo

The Inc file includes all the header files needed for the project.
The Src files includes the code used to interact with the diffrent periphals and store the pasword, and the needed libraries for the HAL interface and Liquid Crystal for the LCD.

## Components
| System Components |
| :---: |
| STM32 Nucleo-32: STM32L432KC |
| USB |
| Wires |
| Keypad |
| Buzzer |
| LCD (I2C) |
| Servo Motor (SG-90) |
| Zener Diode |




## Connections
![image](https://github.com/shalan/CSCE4301-WiKi/assets/64151548/03afd632-cc64-4582-a3fa-8a4e4d2ecbde)


* LCD: Connected to I2C1
* Bluetooth module: Connected to UART2
* Alarm: Connected to PB0 GPIO output pin
* Servo Motor: Connected to TIM1_CH1 (PA8)
* Keypad: Uses PA12,PA11,PA0,PA4 as inputs and PA5,PA6,PA7,PA1 as outputs

## Setting up the eniroment.
After making the correct connections. To build the project, create a Keil uVision project containing the header files and the c code to load to the target.

## Interacting with the system
To use the system, you will need to connect to the bluetooth module, using any bluetooth application. To generate a password, send any character through the bluetooth command line, and a generated password will appear on the LCD. The password can be used only one time through the keypad, after which it will expire and a new password will need to be generated. A master password, which is "12345", is a permanent password that does not expire.
