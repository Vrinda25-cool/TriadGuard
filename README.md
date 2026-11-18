# TriadGuard: An Adaptive Hysteresis Control System for Weight-Based Thermal Regulation in Agricultural Dehydration Applications
**TriadGuard** is an intelligent, closed-loop agricultural dehydration system engineered to prevent case hardening and nutrient degradation during food drying. Unlike conventional constant-temperature dryers, TriadGuard continuously tracks real-time sample weight loss alongside ambient chamber conditions, dynamically adjusting thermal output using adaptive hysteresis control logic.

## Key Features
* **Weight-Adaptive Thermal Regulation:** Monitors continuous moisture loss via a strain-gauge load cell to modulate heating intensity as the produce dries.
* **Prevents Case Hardening:** Dynamically lowers thermal stress during later drying stages so surface moisture does not seal internal water inside the produce.
* **Adaptive Hysteresis Control:** Protects mechanical relays from rapid switching (relay chattering) while maintaining stable chamber kinetics.
* **Forced-Convection Airflow:** Ensures uniform heat distribution and efficient moisture evacuation across the drying tray.

## Hardware Architecture
* **Microcontroller:** Arduino Uno
* **Mass Sensing:** Strain-Gauge Load Cell + HX711 24-Bit ADC Amplifier
* **Environmental Sensing:** DHT22 Digital Temperature & Humidity Sensor
* **Heating Elements:** 12V High-Intensity LED Heating Modules
* **Airflow:** 12V DC Forced-Convection Fan
* **Switching:** Relay Module Assembly

## How It Works
1. **Baseline Calibration:** The system tares the empty tray and records the initial wet weight of the agricultural produce.
2. **Real-Time Telemetry:** The HX711 tracks mass reduction (moisture evaporation rate) while the DHT22 monitors internal temperature and relative humidity.
3. **Adaptive Control Loop:** As moisture content drops, the firmware dynamically shifts the target temperature thresholds and hysteresis band.
4. **Actuation:** Relays switch the 12V LED heaters and forced-convection fan to maintain optimal drying kinetics until target moisture equilibrium is reached.
