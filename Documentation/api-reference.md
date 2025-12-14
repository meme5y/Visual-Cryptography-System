# API Reference - SecureLight Protocol

## Core Functions

### `void setup()`
Initializes pins, serial communication, and shows startup sequence.

### `void loop()`
Main program loop handling button inputs, serial commands, and idle animation.

## Protocol Functions

### `void sendByte(byte data)`
Transmits a single byte via LED.
- **Parameters**: `data` - byte to transmit
- **Returns**: None
- **Side effects**: Activates LED and buzzer

### `void transmitBit(bool bit)`
Transmits a single bit.
- **Parameters**: `bit` - boolean value (0 or 1)
- **Returns**: None
- **Bit mapping**: 1=Green, 0=Red

### `void sendSyncSequence()`
Transmits synchronization pattern (10101010).

## Cryptographic Functions

### `void encryptMessage(byte data[], int length)`
Applies XOR encryption to data array.
- **Parameters**: 
  - `data[]` - byte array to encrypt
  - `length` - array length
- **Algorithm**: `data[i] ^ 0xAB`

### `byte calculateChecksum(byte data[], int length)`
Calculates XOR checksum for error detection.

## User Interface Functions

### `void showCurrentSpeed()`
Displays current transmission speed via Serial.

### `void indicateSpeedChange()`
Provides visual/auditory feedback when speed changes.

### `void displayMainMenu()`
Shows available serial commands.

## Speed Control Functions

### `void checkSpeedButton()`
Handles speed button press, cycles through available speeds.

### Global Variables:
- `transmissionSpeed`: Current bit duration in ms
- `currentSpeedIndex`: Index in SPEEDS array
- `SPEEDS[]`: Array of available speeds [100, 200, 500, 1000]

## Communication Functions

### `void processSerialCommand()`
Processes user input from Serial Monitor.

### Available Commands:
- `1`: Send "HELLO WORLD!"
- `2`: Send custom message
- `3`: Run protocol test
- `4`: Show crypto key
- `5`: Run speed benchmark
- `B`: Change speed

## Utility Functions

### `void setRGBColor(int red, int green, int blue)`
Sets RGB LED color using PWM.
- **Parameters**: Color intensities (0-255)

### `void showIdleAnimation()`
Displays pulsing animation based on current speed.
