# ControlAR

An ESP32-based infrared controller that toggles an air conditioner’s power state with a push button. It uses the [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266) library to transmit infrared commands.

## Hardware

- ESP32 development board
- Infrared transmitter module
- Push button
- Jumper wires

## Wiring

| Component | ESP32 |
|---|---|
| IR transmitter VCC | 3V3 |
| IR transmitter GND | GND |
| IR transmitter DATA | GPIO 4 |
| Push button | GPIO 5 and GND |

The button uses the ESP32’s internal pull-up resistor, so no external resistor is required.

## Setup

1. Install [PlatformIO](https://platformio.org/).
2. Connect the ESP32 to your computer.
3. Build and upload the project:

   ```bash
   make run
   ```

## Usage

Press the button once to turn the air conditioner on. Press it again to turn it off. Each press sends one infrared command.

The default command is configured for cooling at 24°C with automatic fan speed.
