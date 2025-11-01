# Garden Analyzer & Botanist (GAB)

This project includes a robot which uses a variety of sensors & motors to measure and provide data from your garden plants, as well as a user interface for communicating and controlling the robot.
-
developed by:
 - Jeff Bayhon
 - Lance Dador
 - Giuliano de Guzman
 - Gabriel Hipolito
---

## Languages Used:

- **Arduino** (for Nano microcontroller)
- **C#** (for .exe application)

---

## Features

- Utilizes a 2WD movement mechanism & a 4-DOF Servo Arm
- Wireless communication via Serial over Bluetooth
- Sensors for measuring battery voltage, soil moisture, air humidity, & air temperature
- Includes a GUI for accesibility & ease of usage

---

## Requirements

Before you start, make sure you have the following:
- **Visual Studio 2019 / 2022** (for Visual Basic programming)
- **.NET 6 or .NET 8 SDK**
- **Arduino IDE** (for Arduino programming)

---

## How to Run

 - Before running the application, you must first connect your device to your robot via Bluetooth
 - After connecting via Bluetooth, check for your device's Serial port for Bluetooth (either via device manager or Arduino)
 - Run the application, & connect to your robot using your device's active serial port
 - After establishing a serial connection, you can either click the buttons on the screen or use the following keybinds:
   - `W`, `A`, `S`, `D` for motor movement
   - `Z` to decrease motor speed & `C` to increase motor speed
   - `V` to check battery voltage, `B` to check soil moisture, `N` to check air humidity, & `M` to check air temperature
   - `T` & `Y` for servo 1 rotation
   - `G` & `H` for servo 2 rotation
   - `U` & `I` for servo 3 rotation
   - `J` & `K` for servo 4 rotation

---

### Cloning the Repository
Open **Visual Studio** and do this:
1. Click **Clone a repository**
2. In **Repository location**, paste:
   ```bash
   https://github.com/YOUR_USERNAME/rc_controller.git