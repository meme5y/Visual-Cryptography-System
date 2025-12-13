// Definições de pinos
const int LED_RED = 5;
const int LED_GREEN = 6;
const int LED_BLUE = 7;
const int BUZZER_PIN = 8;
const int BUTTON_SEND = 2;
const int BUTTON_SPEED = 3;  // Botão para alterar velocidade

// Constantes do protocolo
#define START_BYTE 0xFF
#define END_BYTE 0xFE
#define MAX_MESSAGE_LENGTH 16

// Velocidades disponíveis (ms por bit)
const int SPEEDS[] = {100, 200, 500, 1000}; // Rápido, Normal, Lento, Muito Lento
const int NUM_SPEEDS = 4;

// Chave de criptografia (XOR key)
const byte CRYPTO_KEY = 0xAB;

// Protocolo de comunicação
struct MessagePacket {
  byte startByte;
  byte length;
  byte data[MAX_MESSAGE_LENGTH];
  byte checksum;
  byte endByte;
};

// Variáveis do sistema
bool transmitting = false;
int currentSpeedIndex = 1; // Começa com velocidade Normal (200ms)
int transmissionSpeed = SPEEDS[currentSpeedIndex];

void setup() {
  // Inicialização de pinos
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BUTTON_SEND, INPUT_PULLUP);
  pinMode(BUTTON_SPEED, INPUT_PULLUP);
  
  Serial.begin(9600);
  
  Serial.println("=== SISTEMA DE CRIPTOGRAFIA VISUAL ===");
  Serial.println("Protocolo: SecureLight v1.0");
  Serial.println("Controle: Botão para velocidade");
  Serial.println("======================================");
  
  showStartupSequence();
  displayMainMenu();
  showCurrentSpeed();
}

void loop() {
  // Verificar botão de velocidade
  checkSpeedButton();
  
  // Verificar botão de transmissão
  if (digitalRead(BUTTON_SEND) == LOW && !transmitting) {
    delay(50); // Debounce
    startTransmissionProtocol();
  }
  
  // Verificar comandos serial
  if (Serial.available() && !transmitting) {
    processSerialCommand();
  }
  
  // Feedback visual de espera
  if (!transmitting) {
    showIdleAnimation();
  }
}

/**
 * Verifica botão de velocidade
 * Conceito: Controle de parâmetros via interface física
 */
void checkSpeedButton() {
  static bool lastSpeedButtonState = HIGH;
  bool currentSpeedButtonState = digitalRead(BUTTON_SPEED);
  
  if (lastSpeedButtonState == HIGH && currentSpeedButtonState == LOW) {
    // Botão pressionado - mudar velocidade
    delay(50); // Debounce
    
    currentSpeedIndex = (currentSpeedIndex + 1) % NUM_SPEEDS;
    transmissionSpeed = SPEEDS[currentSpeedIndex];
    
    showCurrentSpeed();
    indicateSpeedChange();
  }
  
  lastSpeedButtonState = currentSpeedButtonState;
}

/**
 * Mostra velocidade atual
 * Conceito: Feedback de configuração do sistema
 */
void showCurrentSpeed() {
  Serial.print("🎚️  Velocidade: ");
  Serial.print(transmissionSpeed);
  Serial.print("ms/bit (");
  
  switch(currentSpeedIndex) {
    case 0: Serial.println("RÁPIDO)"); break;
    case 1: Serial.println("NORMAL)"); break;
    case 2: Serial.println("LENTO)"); break;
    case 3: Serial.println("DEMONSTRAÇÃO)"); break;
  }
}

/**
 * Indica mudança de velocidade
 * Conceito: Feedback visual e auditivo
 */
void indicateSpeedChange() {
  // Feedback sonoro
  tone(BUZZER_PIN, 1800, 200);
  
  // Feedback visual baseado na velocidade
  switch(currentSpeedIndex) {
    case 0: // Rápido - Azul
      setRGBColor(0, 0, 255);
      break;
    case 1: // Normal - Verde
      setRGBColor(0, 255, 0);
      break;
    case 2: // Lento - Amarelo
      setRGBColor(255, 255, 0);
      break;
    case 3: // Demonstração - Roxo
      setRGBColor(255, 0, 255);
      break;
  }
  delay(300);
  setRGBColor(0, 0, 0);
}

// ========== PROTOCOLO DE COMUNICAÇÃO ==========

/**
 * Sequência inicial do sistema
 */
void showStartupSequence() {
  // LED vermelho - sistema inicializando
  setRGBColor(255, 0, 0);
  tone(BUZZER_PIN, 1000, 200);
  delay(500);
  
  // LED verde - sistema pronto
  setRGBColor(0, 255, 0);
  tone(BUZZER_PIN, 1500, 200);
  delay(500);
  
  // LED azul - modo criptografia
  setRGBColor(0, 0, 255);
  tone(BUZZER_PIN, 2000, 200);
  delay(500);
  
  setRGBColor(0, 0, 0);
}

/**
 * Mostra menu principal via Serial
 */
void displayMainMenu() {
  Serial.println("\n--- MENU PRINCIPAL ---");
  Serial.println("1. Enviar mensagem padrão");
  Serial.println("2. Enviar mensagem customizada");
  Serial.println("3. Teste de protocolo");
  Serial.println("4. Mostrar chave criptográfica");
  Serial.println("5. Benchmark de velocidade");
  Serial.println("B. Botão velocidade: " + String(SPEEDS[(currentSpeedIndex + 1) % NUM_SPEEDS]) + "ms");
  Serial.println("----------------------");
}

/**
 * Processa comandos da serial
 */
void processSerialCommand() {
  char command = Serial.read();
  
  switch(command) {
    case '1':
      sendPredefinedMessage("HELLO WORLD!");
      break;
    case '2':
      requestCustomMessage();
      break;
    case '3':
      runProtocolTest();
      break;
    case '4':
      showCryptoKey();
      break;
    case '5':
      runSpeedBenchmark();
      break;
    case 'b':
    case 'B':
      // Mudar velocidade via serial também
      currentSpeedIndex = (currentSpeedIndex + 1) % NUM_SPEEDS;
      transmissionSpeed = SPEEDS[currentSpeedIndex];
      showCurrentSpeed();
      break;
    default:
      Serial.println("Comando inválido!");
      displayMainMenu();
  }
}

/**
 * Inicia protocolo de transmissão
 */
void startTransmissionProtocol() {
  transmitting = true;
  Serial.println("\n🚀 INICIANDO PROTOCOLO DE TRANSMISSÃO");
  Serial.print("📡 Velocidade: ");
  Serial.print(transmissionSpeed);
  Serial.println("ms/bit");
  
  // 1. Préâmbulo de sincronização
  sendSyncSequence();
  
  // 2. Handshake inicial
  performHandshake();
  
  // 3. Transmissão de dados
  sendPredefinedMessage("CS ROCKS!");
  
  // 4. Finalização
  endTransmission();
  
  transmitting = false;
  Serial.println("✅ TRANSMISSÃO CONCLUÍDA");
}

// ========== ALGORITMOS CRIPTOGRÁFICOS ==========

/**
 * Criptografa mensagem usando XOR
 */
void encryptMessage(byte data[], int length) {
  Serial.print("🔐 Criptografando: ");
  for(int i = 0; i < length; i++) {
    Serial.print((char)data[i]);
    data[i] = data[i] ^ CRYPTO_KEY; // XOR encryption
  }
  Serial.println();
}

/**
 * Descriptografa mensagem
 */
void decryptMessage(byte data[], int length) {
  for(int i = 0; i < length; i++) {
    data[i] = data[i] ^ CRYPTO_KEY; // XOR decryption
  }
}

/**
 * Calcula checksum para verificação de erro
 */
byte calculateChecksum(byte data[], int length) {
  byte checksum = 0;
  for(int i = 0; i < length; i++) {
    checksum ^= data[i]; // XOR checksum
  }
  return checksum;
}

// ========== PROTOCOLO DE TRANSMISSÃO ==========

/**
 * Envia sequência de sincronização
 */
void sendSyncSequence() {
  Serial.println("📡 Enviando sequência de sincronização...");
  
  // Padrão de sincronização: 10101010
  for(int i = 0; i < 8; i++) {
    if(i % 2 == 0) {
      setRGBColor(255, 255, 255); // Bit 1 - Branco
    } else {
      setRGBColor(0, 0, 0);       // Bit 0 - Preto
    }
    tone(BUZZER_PIN, 2000, 50);
    delay(transmissionSpeed / 2);
  }
  setRGBColor(0, 0, 0);
  delay(transmissionSpeed * 2);
}

/**
 * Realiza handshake inicial
 */
void performHandshake() {
  Serial.println("🤝 Realizando handshake...");
  
  // Envia byte de início
  sendByte(START_BYTE);
  
  // Aguarda reconhecimento (simulado)
  delay(transmissionSpeed * 3);
  
  // Feedback de handshake bem-sucedido
  setRGBColor(0, 255, 255);
  tone(BUZZER_PIN, 1800, 300);
  delay(300);
  setRGBColor(0, 0, 0);
}

/**
 * Envia mensagem pré-definida
 */
void sendPredefinedMessage(const char* message) {
  int length = strlen(message);
  
  // Criar pacote de mensagem
  MessagePacket packet;
  packet.startByte = START_BYTE;
  packet.length = length;
  packet.endByte = END_BYTE;
  
  // Copiar dados
  for(int i = 0; i < length; i++) {
    packet.data[i] = message[i];
  }
  
  // Criptografar dados
  encryptMessage(packet.data, length);
  
  // Calcular checksum
  packet.checksum = calculateChecksum(packet.data, length);
  
  // Transmitir pacote completo
  transmitPacket(packet);
}

/**
 * Transmite pacote completo
 */
void transmitPacket(MessagePacket packet) {
  Serial.println("\n📦 TRANSMITINDO PACOTE:");
  Serial.print("Start Byte: 0x");
  Serial.println(packet.startByte, HEX);
  Serial.print("Length: ");
  Serial.println(packet.length);
  
  // Transmitir start byte
  sendByte(packet.startByte);
  
  // Transmitir length
  sendByte(packet.length);
  
  // Transmitir dados
  Serial.print("Data (encrypted): ");
  for(int i = 0; i < packet.length; i++) {
    Serial.print("0x");
    Serial.print(packet.data[i], HEX);
    Serial.print(" ");
    sendByte(packet.data[i]);
  }
  Serial.println();
  
  // Transmitir checksum
  Serial.print("Checksum: 0x");
  Serial.println(packet.checksum, HEX);
  sendByte(packet.checksum);
  
  // Transmitir end byte
  sendByte(packet.endByte);
}

/**
 * Envia um byte via LED RGB
 */
void sendByte(byte data) {
  Serial.print("🔸 Enviando byte: 0x");
  Serial.print(data, HEX);
  Serial.print(" (");
  Serial.print(data, BIN);
  Serial.println(")");
  
  // Envia cada bit do byte (MSB first)
  for(int bitPos = 7; bitPos >= 0; bitPos--) {
    bool bit = (data >> bitPos) & 1;
    transmitBit(bit);
    
    // Log do bit
    Serial.print(bit ? "1" : "0");
  }
  Serial.println();
  
  delay(transmissionSpeed); // Espaço entre bytes
}

/**
 * Transmite um bit individual
 */
void transmitBit(bool bit) {
  if(bit) {
    // Bit 1 - LED Verde brilhante
    setRGBColor(0, 255, 0);
    tone(BUZZER_PIN, 2500, 50); // Tom alto para bit 1
  } else {
    // Bit 0 - LED Vermelho suave
    setRGBColor(255, 0, 0);
    tone(BUZZER_PIN, 1500, 50); // Tom baixo para bit 0
  }
  
  delay(transmissionSpeed);
  setRGBColor(0, 0, 0); // Desliga entre bits
  delay(transmissionSpeed / 4);
}

/**
 * Finaliza transmissão
 */
void endTransmission() {
  Serial.println("🔚 Finalizando transmissão...");
  
  // Sequência de término
  for(int i = 0; i < 3; i++) {
    setRGBColor(255, 255, 0); // Amarelo
    tone(BUZZER_PIN, 1200, 100);
    delay(200);
    setRGBColor(0, 0, 0);
    delay(200);
  }
}

// ========== FUNÇÕES AUXILIARES ==========

/**
 * Define cor do RGB
 */
void setRGBColor(int red, int green, int blue) {
  analogWrite(LED_RED, red);
  analogWrite(LED_GREEN, green);
  analogWrite(LED_BLUE, blue);
}

/**
 * Animação de espera
 */
void showIdleAnimation() {
  static unsigned long lastUpdate = 0;
  static int hue = 0;
  
  if(millis() - lastUpdate > 100) {
    // Gradiente suave de cores - indica velocidade atual
    int r, g, b;
    
    switch(currentSpeedIndex) {
      case 0: // Rápido - Azul
        r = 0; g = 0; b = (sin(hue * 0.017) + 1) * 127;
        break;
      case 1: // Normal - Verde
        r = 0; g = (sin(hue * 0.017) + 1) * 127; b = 0;
        break;
      case 2: // Lento - Amarelo
        r = (sin(hue * 0.017) + 1) * 127; 
        g = (sin(hue * 0.017) + 1) * 127; 
        b = 0;
        break;
      case 3: // Demonstração - Roxo
        r = (sin(hue * 0.017) + 1) * 127;
        g = 0;
        b = (sin(hue * 0.017) + 1) * 127;
        break;
    }
    
    setRGBColor(r, g, b);
    hue = (hue + 1) % 360;
    lastUpdate = millis();
  }
}

// ========== FUNÇÕES DE TESTE E DEMONSTRAÇÃO ==========

/**
 * Executa teste de protocolo
 */
void runProtocolTest() {
  Serial.println("\n🧪 EXECUTANDO TESTE DE PROTOCOLO");
  
  // Teste em todas as velocidades
  for(int i = 0; i < NUM_SPEEDS; i++) {
    Serial.print("\n--- Teste velocidade ");
    Serial.print(SPEEDS[i]);
    Serial.println("ms ---");
    
    int originalSpeed = transmissionSpeed;
    transmissionSpeed = SPEEDS[i];
    
    unsigned long startTime = millis();
    sendByte(0x55); // Byte de teste: 01010101
    unsigned long endTime = millis();
    
    Serial.print("Duração: ");
    Serial.print(endTime - startTime);
    Serial.println("ms");
    
    transmissionSpeed = originalSpeed;
    delay(500);
  }
  
  Serial.println("\n✅ Teste de protocolo concluído!");
}

/**
 * Mostra chave criptográfica
 */
void showCryptoKey() {
  Serial.println("\n🔑 CONFIGURAÇÃO CRIPTOGRÁFICA:");
  Serial.print("Chave XOR: 0x");
  Serial.println(CRYPTO_KEY, HEX);
  Serial.print("Chave (bin): ");
  Serial.println(CRYPTO_KEY, BIN);
  Serial.println("Algoritmo: XOR Stream Cipher");
  Serial.println("Segurança: Educacional - Não use para dados sensíveis!");
}

/**
 * Benchmark de velocidade
 */
void runSpeedBenchmark() {
  Serial.println("\n⏱️  BENCHMARK DE VELOCIDADE");
  
  Serial.println("Testando todas as velocidades disponíveis:");
  
  for(int i = 0; i < NUM_SPEEDS; i++) {
    int testSpeed = SPEEDS[i];
    unsigned long startTime = millis();
    
    // Transmitir mensagem de teste
    String testMsg = "TEST";
    for(int j = 0; j < testMsg.length(); j++) {
      sendByte(testMsg[j]);
    }
    
    unsigned long endTime = millis();
    
    Serial.print("Velocidade ");
    Serial.print(testSpeed);
    Serial.print("ms: ");
    Serial.print((32.0 / (endTime - startTime)) * 1000); // bps
    Serial.println(" bps");
    
    delay(500);
  }
}

/**
 * Solicita mensagem customizada
 */
void requestCustomMessage() {
  Serial.println("\n💫 Digite a mensagem para transmitir (max 16 chars):");
  while(!Serial.available()) {
    // Aguarda entrada
    delay(100);
  }
  
  String message = Serial.readString();
  message.trim();
  
  if(message.length() > 0 && message.length() <= MAX_MESSAGE_LENGTH) {
    sendPredefinedMessage(message.c_str());
  } else {
    Serial.println("❌ Mensagem muito longa ou vazia!");
  }
}
