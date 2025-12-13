// protocol_definitions.h
// SecureLight Protocol Constants and Definitions
// Developed by: Fernando Augusto & [Nome do Amigo]
// Location: Mozambique
// Project: Visual Cryptography System

#ifndef PROTOCOL_DEFINITIONS_H
#define PROTOCOL_DEFINITIONS_H

#include <Arduino.h>

// ==================== PROTOCOL CONSTANTS ====================

// Frame delimiters
#define START_BYTE 0xFF    // 255 in decimal
#define END_BYTE   0xFE    // 254 in decimal

// Message constraints
#define MAX_MESSAGE_LENGTH 16  // Maximum payload size

// Transmission speed options (milliseconds per bit)
const int SPEEDS[] = {100, 200, 500, 1000};
const int NUM_SPEEDS = 4;

// Speed indices for easy reference
#define SPEED_FAST     0  // 100ms/bit
#define SPEED_NORMAL   1  // 200ms/bit  
#define SPEED_SLOW     2  // 500ms/bit
#define SPEED_DEMO     3  // 1000ms/bit

// Cryptography configuration
const byte CRYPTO_KEY = 0xAB;  // XOR encryption key

// ==================== HARDWARE PINOUT ====================

// LED RGB pins (PWM capable)
const int LED_RED = 5;
const int LED_GREEN = 6;
const int LED_BLUE = 7;

// Audio feedback
const int BUZZER_PIN = 8;

// User interface buttons
const int BUTTON_SEND = 2;   // Interrupt-capable pin
const int BUTTON_SPEED = 3;  // Interrupt-capable pin

// ==================== PROTOCOL STRUCTURES ====================

/**
 * @brief Complete message packet structure
 * 
 * This structure defines the format of all transmitted messages
 * in the SecureLight protocol v1.0
 */
typedef struct {
  byte startByte;                    // Always 0xFF
  byte length;                       // Number of data bytes (1-16)
  byte data[MAX_MESSAGE_LENGTH];     // Encrypted payload
  byte checksum;                     // XOR of all data bytes
  byte endByte;                      // Always 0xFE
} MessagePacket;

// ==================== TIMING CONSTANTS ====================

// Button debounce time (milliseconds)
const unsigned long DEBOUNCE_DELAY = 50;

// Synchronization pattern timing (percentage of bit time)
const float SYNC_BIT_FRACTION = 0.5;  // Sync bits are half duration

// Inter-byte spacing (percentage of bit time)  
const float BYTE_SPACING_FRACTION = 1.0;  // Full bit time between bytes

// ==================== AUDIO FEEDBACK ====================

// Tone frequencies for different events (Hz)
const int TONE_STARTUP_LOW = 1000;
const int TONE_STARTUP_MID = 1500;
const int TONE_STARTUP_HIGH = 2000;
const int TONE_BIT_1 = 2500;    // High tone for bit 1
const int TONE_BIT_0 = 1500;    // Low tone for bit 0
const int TONE_SPEED_CHANGE = 1800;
const int TONE_HANDSHAKE = 1800;
const int TONE_END = 1200;

// Tone durations (milliseconds)
const int TONE_DURATION_SHORT = 50;
const int TONE_DURATION_MEDIUM = 100;
const int TONE_DURATION_LONG = 200;
const int TONE_DURATION_STARTUP = 200;

// ==================== COLOR DEFINITIONS ====================

// RGB colors for different states
typedef struct {
  int red;
  int green;
  int blue;
} RGBColor;

// Pre-defined colors
const RGBColor COLOR_RED = {255, 0, 0};
const RGBColor COLOR_GREEN = {0, 255, 0};
const RGBColor COLOR_BLUE = {0, 0, 255};
const RGBColor COLOR_YELLOW = {255, 255, 0};
const RGBColor COLOR_PURPLE = {255, 0, 255};
const RGBColor COLOR_CYAN = {0, 255, 255};
const RGBColor COLOR_WHITE = {255, 255, 255};
const RGBColor COLOR_BLACK = {0, 0, 0};

// Speed-specific idle animation colors
const RGBColor SPEED_COLORS[] = {
  {0, 0, 255},    // Fast - Blue
  {0, 255, 0},    // Normal - Green
  {255, 255, 0},  // Slow - Yellow
  {255, 0, 255}   // Demo - Purple
};

// ==================== SYSTEM STATES ====================

/**
 * @brief Main system states
 */
enum SystemState {
  STATE_IDLE,          // Waiting for user input
  STATE_TRANSMITTING,  // Actively transmitting data
  STATE_RECEIVING,     // Receiving data (future use)
  STATE_ERROR          // Error state
};

/**
 * @brief Transmission substates
 */
enum TransmissionState {
  TX_SYNC,             // Sending synchronization pattern
  TX_HANDSHAKE,        // Performing handshake
  TX_DATA,             // Transmitting data packets
  TX_COMPLETE          // Transmission complete
};

#endif // PROTOCOL_DEFINITIONS_H
