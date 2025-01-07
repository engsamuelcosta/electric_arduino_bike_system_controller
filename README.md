# Electric Arduino Bicycle System Controller

This project is an Arduino-based bicycle system controller that features speed and distance measurement, voltage monitoring, multiple operation modes (motor, generator, regenerative brake), and more. It uses an Arduino microcontroller to calculate vehicle speed, track distance, monitor rotational speed (RPM), and switch between different modes based on sensor inputs. The system includes a real-time LCD display, an EEPROM for persistent settings, and debounced button logic for reliable user inputs.

### Features:
- **Speed Calculation**: Calculates vehicle speed in km/h using wheel rotations detected by a Hall-effect sensor.
- **Distance Tracking**: Tracks the total distance traveled by measuring wheel rotations.
- **RPM Measurement**: Measures wheel rotations per minute (RPM).
- **Multiple Operation Modes**:
  - **Motor Mode**: For standard vehicle operation.
  - **Generator Mode**: When using the wheel's motion to generate electricity.
  - **Regenerative Braking**: Recaptures energy during braking and charges the battery.
- **LCD Display**: A 16x2 I2C LCD screen shows real-time data, including speed, RPM, and distance.
- **EEPROM Settings**: Stores wheel radius and other configuration data persistently.
- **Relay Control**: Controls relays to switch between motor and generator modes based on the brake and accelerator inputs.
- **Accelerator and Brake Monitoring**: Monitors accelerator and brake states to switch between active motor mode and standby mode.
- **Debounced Button Logic**: Ensures reliable button inputs for mode switching and configuration.

### Components:
- **Arduino Board** (e.g., Arduino Uno, Nano, or compatible)
- **I2C LCD (16x2)** for displaying real-time data
- **Hall-effect Sensor** for detecting wheel rotations
- **Relays** for switching between motor and generator modes
- **Accelerator** (analog input) for controlling the motor mode
- **Brake** (digital input) for activating regenerative braking
- **Wiring and Connectors** for assembling the system

### Libraries Used:
- **LiquidCrystal_I2C**: For controlling the I2C LCD display.
- **Wire**: For I2C communication with the LCD.
- **EEPROM**: For storing configuration data like wheel radius settings.
- **SPI**: For future expansions (if applicable).

### Wiring Guide:
1. **Hall-effect Sensor**:
   - Connect the Hall-effect sensor to **digital pin 2** on the Arduino.
   
2. **LCD**:
   - Connect the I2C LCD to the **SDA and SCL pins** on the Arduino (A4 and A5 for Uno).

3. **Accelerator**:
   - Connect the accelerator to **analog pin A1**.

4. **Brake**:
   - Connect the brake to **digital pin 6**.

5. **Relay Control**:
   - Connect the relay control pins to **pins 3, 4, and 5** to control motor and generator states.

### How It Works:
1. **Wheel Rotation Detection**: 
   - The system uses the Hall-effect sensor to detect each wheel rotation. The time between rotations is used to calculate speed, while the total number of rotations is tracked for distance.

2. **Speed Calculation**:
   - Speed is calculated using the formula:  
     `Speed (km/h) = (Wheel Circumference) / (Time per Rotation) * 3600 / 1000`.
   - The wheel circumference is a critical parameter, which can be adjusted in the code for different wheel sizes.

3. **Distance Tracking**:
   - The total distance is accumulated by counting wheel rotations and multiplying by the wheel’s circumference.

4. **RPM Calculation**:
   - RPM (Revolutions Per Minute) is calculated based on the time it takes for each full rotation. This helps track the rotational speed of the wheel.

5. **LCD Display**:
   - The LCD shows real-time data, including:
     - Speed (in km/h)
     - RPM (in revolutions per minute)
     - Distance (in meters)
   - The display is continuously updated with new data as the vehicle moves.

6. **Relay Control and Mode Switching**:
   - Relays control the switching between different modes (motor mode, generator mode, and regenerative brake). Based on the accelerator and brake inputs, the system automatically switches between these modes.
   - The system uses debounced buttons to ensure reliable input handling and prevent errors.

7. **EEPROM Storage**:
   - The wheel radius and other configuration settings are stored in the Arduino’s EEPROM, allowing them to persist even after the system is powered off.

### Example Output:
The LCD will display two lines of information:
- **Line 1**: Speed (in km/h) (e.g., `Speed: 12.3 km/h`)
- **Line 2**: Distance (in meters) or RPM (e.g., `Distance: 1245.6 m` or `RPM: 120`)

### Adjusting Wheel Circumference:
To calculate accurate speed and distance, adjust the wheel circumference according to your bike's wheel size. The formula for circumference is:

- **Circumference (meters)** = `Wheel Diameter (meters) * π`

For example, for a wheel diameter of 0.7 meters, the circumference would be approximately **2.199 meters**.

### Troubleshooting:
- **LCD is blank**: Ensure proper wiring, especially the I2C connections (SDA, SCL).
- **Incorrect speed or distance**: Make sure the wheel circumference is set correctly.
- **Sensor not detecting rotations**: Double-check sensor alignment and positioning on the wheel.

### Installation Instructions:
1. Clone this repository to your local machine:
   ```bash
   git clone https://github.com/your-username/electric-arduino-bike-system-controller.git


Open the project in the Arduino IDE.
Upload the BikeSystemController.ino sketch to your Arduino board.
Connect all components according to the wiring guide.
Open the Serial Monitor for debugging (optional).
Once everything is set up, the LCD will display the speed, distance, and RPM in real time.
Contributing:
Feel free to fork this repository and submit issues or pull requests. Contributions are always welcome, especially for:

Adding new features like graphical speed display.
Improving energy efficiency and power management.
Enhancing user interface (UI) with better display options.
Expanding mode functionalities.

License:
