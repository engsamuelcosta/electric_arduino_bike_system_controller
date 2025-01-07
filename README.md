# electric_arduino_bike_system_controller
Arduino-based Bicycle System Controller featuring distance measurement, voltage monitoring, and multiple modes (motor, generator, regenerative brake). Includes EEPROM for persistent wheel radius settings, LCD for real-time data, and debounce logic for reliable button inputs. Ideal for smart bicycle prototyping
Vehicle Speed and Distance Tracker with Arduino
This project is a vehicle speed and distance tracker based on an Arduino microcontroller. It calculates the speed (in km/h), the number of rotations (RPM), and the total distance traveled (in km) using a Hall-effect sensor and a bicycle wheel's rotation.

Features:
Speed Calculation: Calculates the speed of the vehicle using the rotation of the wheel.
Distance Tracking: Tracks the total distance traveled based on wheel rotations.
RPM Measurement: Measures the RPM (Revolutions Per Minute) of the wheel.
LCD Display: Displays the speed, RPM, and distance on an I2C 16x2 LCD.
Relay Control: Controls relays for switching between motor and generator modes based on accelerator and brake input.
Brake and Accelerator Input: Monitors the brake and accelerator to switch between active motor mode and standby mode.
Components:
Arduino Board (e.g., Arduino Uno)
I2C LCD (16x2)
Hall-effect Sensor
Relays (for switching modes)
Accelerator (analog input)
Brake (digital input)
Wiring and Connectors
Libraries Used:
LiquidCrystal_I2C: For controlling the I2C LCD display.
Wire: For I2C communication.
EEPROM: For storing configuration data (if applicable).
SPI: For SPI communication (if used in future expansions).
Connections:
Hall-effect sensor: Connected to digital pin 2.
LCD: Connected via I2C (pins SDA, SCL).
Accelerator: Connected to analog pin A1.
Brake: Connected to digital pin 6.
Relay pins: Connected to pins 3, 4, and 5 for controlling the motor and generator states.
How It Works:
Speed Calculation: The number of wheel rotations is counted using the Hall-effect sensor. The time between rotations is used to calculate the vehicle's speed.
Distance Tracking: Based on the number of rotations, the total distance is computed.
Relay Control: The system switches between active motor mode and generator mode based on the accelerator and brake inputs.
LCD Display: The speed, RPM, and distance are continuously displayed on the LCD.
Usage:
The system continuously monitors the vehicle's speed and distance and displays the data on the LCD.
The accelerometer and brake inputs are used to switch the system between motor and generator modes.
The data is also available via serial communication for debugging or external monitoring.
Notes:
The system uses a pre-defined wheel circumference (2.0734 meters) for speed and distance calculations.
The relays help manage different operating modes, including motor and generator states.
