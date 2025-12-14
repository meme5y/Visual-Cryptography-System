# SecureLight Protocol v1.0 Specification

## Overview
SecureLight is a visual cryptography protocol that transmits encrypted data via RGB LED light patterns. The system uses XOR encryption and includes error checking.

## Protocol Layers

### 1. Physical Layer
- **Medium**: Visible light (RGB LED)
- **Encoding**: Color intensity modulation
- **Bit representation**:
  - Bit 1: Green light (255 intensity)
  - Bit 0: Red light (255 intensity)
- **Speed control**: 100ms, 200ms, 500ms, 1000ms per bit

### 2. Data Link Layer
- **Frame structure**: Start byte → Length → Data → Checksum → End byte
- **Error detection**: XOR checksum
- **Synchronization**: 10101010 preamble

### 3. Application Layer
- **Message format**: ASCII text (max 16 chars)
- **Encryption**: XOR stream cipher with 0xAB key
- **User interface**: Serial commands and physical buttons

## Packet Format

```
┌─────────┬────────┬─────────────────┬──────────┬─────────┐
│ START   │ LENGTH │     DATA        │ CHECKSUM │   END   │
│ (0xFF)  │ (1B)   │ (1-16 bytes)    │ (1B)     │ (0xFE)  │
└─────────┴────────┴─────────────────┴──────────┴─────────┘
```

## Transmission Sequence

1. **Sync Pattern**: 8-bit alternating 1/0 pattern
2. **Handshake**: Start byte transmission
3. **Data Frame**: Complete packet transmission
4. **Termination**: End byte with acknowledgment

## Security Features
- XOR encryption with fixed key
- Variable transmission speeds
- Error detection via checksum
- Physical layer obfuscation

## Limitations
- Line-of-sight required
- Limited to 16 bytes per message
- XOR encryption not suitable for sensitive data
- Ambient light interference possible
