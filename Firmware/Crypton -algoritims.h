// encryption_algorithms.h
// Cryptographic functions for SecureLight Protocol
// Educational implementation - NOT for real security
// Developed by: Fernando Augusto & [Nome do Amigo]

#ifndef ENCRYPTION_ALGORITHMS_H
#define ENCRYPTION_ALGORITHMS_H

#include <Arduino.h>
#include "protocol_definitions.h"

/**
 * @brief Encrypts data using XOR cipher
 * 
 * @param data Array of bytes to encrypt
 * @param length Number of bytes in array
 * 
 * XOR encryption is symmetric: encrypt(decrypt(data)) = data
 * This is for EDUCATIONAL purposes only
 */
void encryptMessage(byte data[], int length) {
  Serial.print("🔐 Criptografando: \"");
  for(int i = 0; i < length; i++) {
    Serial.print((char)data[i]);
  }
  Serial.print("\" → ");
  
  for(int i = 0; i < length; i++) {
    data[i] = data[i] ^ CRYPTO_KEY;
  }
  
  Serial.print("Hex: ");
  for(int i = 0; i < length; i++) {
    if(data[i] < 0x10) Serial.print("0");
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.println();
}

/**
 * @brief Decrypts XOR-encrypted data
 * 
 * @param data Array of encrypted bytes
 * @param length Number of bytes
 * 
 * Note: XOR is symmetric, so decryption uses same function
 * For clarity, we provide separate function
 */
void decryptMessage(byte data[], int length) {
  Serial.print("🔓 Descriptografando: Hex: ");
  for(int i = 0; i < length; i++) {
    if(data[i] < 0x10) Serial.print("0");
    Serial.print(data[i], HEX);
    Serial.print(" ");
  }
  Serial.print(" → \"");
  
  for(int i = 0; i < length; i++) {
    data[i] = data[i] ^ CRYPTO_KEY;
    Serial.print((char)data[i]);
  }
  Serial.println("\"");
}

/**
 * @brief Calculates XOR checksum for error detection
 * 
 * @param data Array of bytes
 * @param length Number of bytes
 * @return byte XOR checksum
 * 
 * Simple error detection: XOR of all bytes
 * If any single bit changes, checksum changes
 */
byte calculateChecksum(byte data[], int length) {
  byte checksum = 0;
  for(int i = 0; i < length; i++) {
    checksum ^= data[i];
  }
  return checksum;
}

/**
 * @brief Validates message using checksum
 * 
 * @param data Array of bytes
 * @param length Number of bytes
 * @param receivedChecksum Checksum received with message
 * @return bool True if checksum matches
 */
bool validateChecksum(byte data[], int length, byte receivedChecksum) {
  byte calculated = calculateChecksum(data, length);
  
  if(calculated == receivedChecksum) {
    Serial.print("✅ Checksum válido: 0x");
    Serial.println(calculated, HEX);
    return true;
  } else {
    Serial.print("❌ Checksum inválido! Recebido: 0x");
    Serial.print(receivedChecksum, HEX);
    Serial.print(", Calculado: 0x");
    Serial.println(calculated, HEX);
    return false;
  }
}

/**
 * @brief Simple substitution cipher (ROT13 variant)
 * 
 * @param data Array of bytes (ASCII text)
 * @param length Number of bytes
 * 
 * Alternative encryption for demonstration
 * Each character shifted by 13 positions in alphabet
 */
void substituteCipher(byte data[], int length) {
  for(int i = 0; i < length; i++) {
    if(data[i] >= 'A' && data[i] <= 'Z') {
      data[i] = ((data[i] - 'A' + 13) % 26) + 'A';
    } else if(data[i] >= 'a' && data[i] <= 'z') {
      data[i] = ((data[i] - 'a' + 13) % 26) + 'a';
    }
    // Non-alphabetic characters unchanged
  }
}

/**
 * @brief Generates a simple pseudo-random key
 * 
 * @param seed Seed value for generation
 * @return byte Generated key
 * 
 * Simple LCG (Linear Congruential Generator)
 * For educational purposes only
 */
byte generateKey(byte seed) {
  // Simple LCG parameters
  const byte a = 75;
  const byte c = 74;
  const byte m = 256;
  
  return (a * seed + c) % m;
}

/**
 * @brief Displays cryptographic configuration
 */
void showCryptoKey() {
  Serial.println("\n🔑 CONFIGURAÇÃO CRIPTOGRÁFICA:");
  Serial.print("Chave XOR: 0x");
  if(CRYPTO_KEY < 0x10) Serial.print("0");
  Serial.println(CRYPTO_KEY, HEX);
  
  Serial.print("Chave (decimal): ");
  Serial.println(CRYPTO_KEY);
  
  Serial.print("Chave (binário): ");
  for(int i = 7; i >= 0; i--) {
    Serial.print((CRYPTO_KEY >> i) & 1);
  }
  Serial.println();
  
  Serial.print("Chave (ASCII): ");
  if(CRYPTO_KEY >= 32 && CRYPTO_KEY <= 126) {
    Serial.print("'");
    Serial.print((char)CRYPTO_KEY);
    Serial.println("'");
  } else {
    Serial.println("[Não imprimível]");
  }
  
  Serial.println("Algoritmo: XOR Stream Cipher");
  Serial.println("Segurança: NÍVEL EDUCATIVO - Não use para dados sensíveis!");
  Serial.println("\n💡 Nota: XOR é simétrico - mesma chave para criptografar/descriptografar");
}

#endif // ENCRYPTION_ALGORITHMS_H
