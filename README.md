# ESP32_BT-A2DP_Receiver

This project demonstrates how to use an ESP32-A2DP Library and M5Stack RCA Module to receive audio over Bluetooth A2DP.

RCA Module: https://docs.m5stack.com/ja/module/RCA%20Module%2013.2

## Features

- Bluetooth A2DP sink functionality
- Audio output via I2S interface

## Requirements

- M5Stack Basic
- M5Stack RCA Module
- ESP32-A2DP Library
- Arduino IDE with ESP32 board support
- M5Stack Library

## Installation

1. Install the ESP32-A2DP Library in the Arduino IDE. You can find it [here](https://github.com/pschatzmann/ESP32-A2DP.git)
2. Install the M5Stack Library in the Arduino IDE. You can find it [here](https://github.com/m5stack/M5Unified.git)
3. Connect the M5Stack RCA Module to the M5Stack Basic.
4. Open the Arduino IDE and create a new sketch.
5. Copy and paste the code from the `main.cpp` and `Application.h` files into the new sketch.
6. Upload the sketch to your M5Stack Basic.
7. Open the Serial Monitor to see the debug output.


## Usage

1. Ensure the ESP32 is properly connected to the M5Stack Basic and the RCA Module.
2. Power on the M5Stack Basic.
3. Pair your Bluetooth device "Riraosan Player"(e.g., smartphone, laptop) with the ESP32.
4. Start playing audio from your paired device.
5. The audio will be received and output through the RCA Module.
6. Adjust volume and other settings as needed using your Bluetooth device's controls.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Acknowledgments

- Thanks to [@pschatzmann](https://github.com/pschatzmann) of the ESP32-A2DP Library for making Bluetooth audio streaming possible.
- Thanks to M5Stack for providing excellent hardware modules for prototyping.


### Enjoy your Bluetooth audio streaming with ESP32-A2DP and M5Stack! ###
