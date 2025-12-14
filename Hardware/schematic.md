# Circuit Schematic - Visual Cryptography System

## Components Required:
- Arduino Uno/Nano
- RGB LED (Common Cathode)
- 3x 220Ω Resistors
- 2x Push Buttons
- Piezo Buzzer
- Breadboard and Jumper Wires

## Connection Diagram:

### Arduino Pinout:
```
LED_RED    -> Pin 5 (PWM)
LED_GREEN  -> Pin 6 (PWM)
LED_BLUE   -> Pin 7 (PWM)
BUZZER     -> Pin 8
BUTTON_SEND -> Pin 2 (with pull-up)
BUTTON_SPEED -> Pin 3 (with pull-up)
```

### RGB LED Connections:
```
RGB LED:
  Red Pin   -> 220Ω -> Arduino Pin 5
  Green Pin -> 220Ω -> Arduino Pin 6
  Blue Pin  -> 220Ω -> Arduino Pin 7
  Cathode   -> GND
```

### Buttons Configuration:
```
BUTTON_SEND:
  One side -> Arduino Pin 2
  Other side -> GND

BUTTON_SPEED:
  One side -> Arduino Pin 3
  Other side -> GND
```

### Buzzer Connection:
```
Piezo Buzzer:
  Positive -> Arduino Pin 8
  Negative -> GND
```

## Power Requirements:
- Arduino powered via USB (5V, 500mA)
- RGB LED current: ~20mA per color (max)
- Total current draw: < 100mA
