# User Manual - Visual Cryptography System

## Quick Start Guide

### 1. Initial Setup
1. Assemble circuit following hardware guide
2. Connect Arduino to computer via USB
3. Upload firmware using Arduino IDE
4. Open Serial Monitor (Tools → Serial Monitor)

### 2. First Use
1. System shows startup sequence (red → green → blue)
2. Serial Monitor displays main menu
3. System is ready for operation

## Operating Modes

### Mode 1: Serial Control
Send commands via Serial Monitor:
- Type `1` and press Enter: Send "HELLO WORLD!"
- Type `2` and press Enter: Send custom message
- Type `3`: Run protocol test
- Type `4`: Show encryption key
- Type `5`: Run speed benchmark
- Type `B`: Change transmission speed

### Mode 2: Button Control
- **Speed Button (Pin 3)**: Press to cycle through speeds
- **Send Button (Pin 2)**: Press to start transmission

## Transmission Speeds

| Speed Name | Duration | LED Color | Use Case |
|------------|----------|-----------|----------|
| Fast | 100ms/bit | Blue | Quick demonstrations |
| Normal | 200ms/bit | Green | Standard operation |
| Slow | 500ms/bit | Yellow | Learning/observation |
| Demo | 1000ms/bit | Purple | Detailed analysis |

## Visual Indicators

### LED Colors:
- **Red**: Bit 0 transmission, startup phase
- **Green**: Bit 1 transmission, system ready
- **Blue**: Fast speed mode
- **Yellow**: Slow speed mode
- **Purple**: Demo speed mode
- **White**: Sync pattern
- **Cyan**: Handshake successful

### Buzzer Tones:
- **High pitch (2500Hz)**: Bit 1
- **Low pitch (1500Hz)**: Bit 0
- **Medium pitch (1800Hz)**: Speed change

## Common Operations

### Sending a Message:
1. Press Send button OR
2. Type `2` in Serial Monitor
3. Enter your message (max 16 characters)
4. Watch LED transmission pattern

### Changing Speed:
1. Press Speed button on circuit OR
2. Type `B` in Serial Monitor
3. Observe LED color change

### Testing Protocol:
1. Type `3` in Serial Monitor
2. System tests all speeds sequentially
3. Results display in Serial Monitor

## Troubleshooting

### Problem: LED not lighting
- Check resistor connections
- Verify PWM pins are correct
- Test LED with simple blink sketch

### Problem: Buttons not responding
- Check button connections to GND
- Verify pins 2 and 3 are configured as INPUT_PULLUP
- Test with internal pull-up disabled

### Problem: No Serial output
- Check baud rate (9600)
- Verify correct COM port
- Check USB cable connection

### Problem: Transmission errors
- Ensure direct line of sight
- Reduce ambient light
- Use slower speed for reliability

## Advanced Features

### Custom Message Length:
Modify `MAX_MESSAGE_LENGTH` in protocol_definitions.h

### Encryption Key:
Change `CRYPTO_KEY` in protocol_definitions.h

### Adding New Speeds:
Modify `SPEEDS[]` array in main firmware

## Safety Notes
- Do not stare directly at bright LED
- Keep away from moisture
- Use appropriate power supply
- XOR encryption is for educational purposes only
