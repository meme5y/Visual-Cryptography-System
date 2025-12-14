# Step-by-Step Assembly Guide

## Step 1: Prepare Components
1. Gather all components from the list
2. Identify the RGB LED pins:
   - Longest pin = Common Cathode (GND)
   - Shortest pins = Anodes (R, G, B)

## Step 2: Build the Circuit

### Stage A: RGB LED Connection
1. Connect RGB LED cathode to GND rail on breadboard
2. Connect 220Ω resistor to red anode, then to Arduino Pin 5
3. Connect 220Ω resistor to green anode, then to Arduino Pin 6
4. Connect 220Ω resistor to blue anode, then to Arduino Pin 7

### Stage B: Button Configuration
1. Place two buttons on breadboard
2. Connect one side of first button to Arduino Pin 2
3. Connect one side of second button to Arduino Pin 3
4. Connect other sides of both buttons to GND

### Stage C: Buzzer Connection
1. Connect positive terminal of buzzer to Arduino Pin 8
2. Connect negative terminal to GND

### Stage D: Power Connections
1. Connect Arduino 5V to breadboard power rail
2. Connect Arduino GND to breadboard ground rail

## Step 3: Verification
1. Double-check all connections
2. Ensure no short circuits
3. Verify resistor values (220Ω)

## Step 4: Software Setup
1. Install Arduino IDE from arduino.cc
2. Clone this repository
3. Open `firmware/securelight_protocol.ino`
4. Select correct board and port
5. Upload the code

## Step 5: Testing
1. Open Serial Monitor (9600 baud)
2. System should show startup sequence
3. Press speed button to cycle through modes
4. Use serial commands to test transmission

## Troubleshooting:
- **LED not lighting**: Check resistor values, polarity
- **Buttons not working**: Check pull-up resistor configuration
- **No serial output**: Check baud rate, USB connection
