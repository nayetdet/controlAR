# ControlAR

An ESP32-based infrared controller that toggles an air conditioner’s power state with a push button. It uses the [IRremoteESP8266](https://github.com/crankyoldgit/IRremoteESP8266) library to transmit infrared commands.

## Hardware

- ESP32 development board
- Infrared transmitter module
- 3 push buttons
- 6 LEDs
- 6 × 270Ω resistors
- Jumper wires

## Wiring

| Component | ESP32 |
|---|---|
| IR transmitter VCC | 3V3 |
| IR transmitter GND | GND |
| IR transmitter DATA | GPIO 4 |
| Power button | GPIO 5 and GND |
| Temperature up button | GPIO 21 and GND |
| Temperature down button | GPIO 22 and GND |
| Power LED (via 270Ω) | GPIO 25 and GND |

The buttons use the ESP32’s internal pull-up resistors, so no external resistors are required.

### Temperature LEDs

The set temperature is shown in binary on 5 LEDs. Wire each one as GPIO → 270Ω resistor → LED anode, LED cathode → GND.

| LED (bit value) | ESP32 |
| --- | --- |
| 16 | GPIO 23 |
| 8 | GPIO 19 |
| 4 | GPIO 18 |
| 2 | GPIO 17 |
| 1 | GPIO 16 |

For example, 24°C = 16 + 8 lights the first two LEDs (`11000`).

## Setup

1. Install [PlatformIO](https://platformio.org/).
2. Connect the ESP32 to your computer.
3. Build and upload the project:

   ```bash
   make run
   ```

## Usage

Press the button once to turn the air conditioner on. Press it again to turn it off. Each press sends one infrared command.

Use the temperature buttons to raise or lower the temperature by 1°C (between 16°C and 30°C). If the air conditioner is off, the new temperature is stored and applied the next time it is turned on.

The default command is configured for cooling at 24°C with automatic fan speed.
