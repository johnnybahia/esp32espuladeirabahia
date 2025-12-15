// ============================================================
// CÓDIGO DE TESTE - VERIFICAR SINAL DOS SENSORES
// ============================================================
// Use este código para verificar qual GPIO está mudando
// quando você liga/desliga cada máquina
// ============================================================

#include <WiFi.h>

// Configuração dos pinos (mesma do código principal)
const int qtdMaquinas = 5;
String nomes[qtdMaquinas] = {
  "ESPULADEIRA LONGO 2 BOCAS 1",      // GPIO 27
  "ESPULADEIRA LONGO 2 BOCAS 2",      // GPIO 26
  "ESPULADEIRA TORRE 4 BOCAS",        // GPIO 25
  "ESPULADEIRA CHINESA 2 BOCAS 1",    // GPIO 33
  "ESPULADEIRA CHINESA 2 BOCAS 2"     // GPIO 32
};
int pinos[qtdMaquinas] = {27, 26, 25, 33, 32};

// Variáveis de controle
int estadoAtual[5];
int estadoAnterior[5];

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("\n\n==============================================");
  Serial.println("   TESTE DE SENSORES - MARFIM BAHIA");
  Serial.println("==============================================\n");

  // Configura todos os pinos
  for(int i = 0; i < qtdMaquinas; i++) {
    pinMode(pinos[i], INPUT_PULLUP);
    estadoAtual[i] = digitalRead(pinos[i]);
    estadoAnterior[i] = estadoAtual[i];
  }

  Serial.println("CONFIGURAÇÃO:");
  Serial.println("  - LOW (0) = Máquina PRODUZINDO");
  Serial.println("  - HIGH (1) = Máquina PARADA");
  Serial.println("\nSe estiver ao contrário, o sinal está invertido!\n");

  // Mostra estado inicial de todos
  Serial.println("ESTADO INICIAL:");
  Serial.println("------------------------------------------");
  for(int i = 0; i < qtdMaquinas; i++) {
    String estado = (estadoAtual[i] == LOW) ? "PRODUZINDO" : "PARADA";
    Serial.print("GPIO ");
    Serial.print(pinos[i]);
    Serial.print(" - ");
    Serial.print(nomes[i]);
    Serial.print(": ");
    Serial.print(estado);
    Serial.print(" (");
    Serial.print(estadoAtual[i]);
    Serial.println(")");
  }
  Serial.println("------------------------------------------\n");

  Serial.println("MONITORANDO MUDANÇAS...");
  Serial.println("Ligue/desligue as máquinas e observe as mensagens:\n");
}

void loop() {
  bool houveAlteracao = false;

  for(int i = 0; i < qtdMaquinas; i++) {
    estadoAtual[i] = digitalRead(pinos[i]);

    // Detectou mudança
    if (estadoAtual[i] != estadoAnterior[i]) {
      houveAlteracao = true;

      Serial.println("╔═══════════════════════════════════════════╗");
      Serial.print("║ MUDANÇA DETECTADA em GPIO ");
      Serial.print(pinos[i]);
      Serial.println("           ║");
      Serial.println("╠═══════════════════════════════════════════╣");
      Serial.print("║ Máquina: ");
      Serial.println(nomes[i]);
      Serial.print("║ Estado ANTERIOR: ");
      Serial.print(estadoAnterior[i] == LOW ? "LOW (0) = PRODUZINDO" : "HIGH (1) = PARADA");
      Serial.println("    ║");
      Serial.print("║ Estado ATUAL   : ");
      Serial.print(estadoAtual[i] == LOW ? "LOW (0) = PRODUZINDO" : "HIGH (1) = PARADA");
      Serial.println("    ║");

      if (estadoAnterior[i] == HIGH && estadoAtual[i] == LOW) {
        Serial.println("║                                           ║");
        Serial.println("║ ✓ Mudou de PARADA para PRODUZINDO        ║");
        Serial.println("║   (A máquina FOI LIGADA)                 ║");
      } else if (estadoAnterior[i] == LOW && estadoAtual[i] == HIGH) {
        Serial.println("║                                           ║");
        Serial.println("║ ✓ Mudou de PRODUZINDO para PARADA        ║");
        Serial.println("║   (A máquina FOI DESLIGADA)              ║");
      }

      Serial.println("╚═══════════════════════════════════════════╝\n");

      estadoAnterior[i] = estadoAtual[i];
    }
  }

  delay(100); // Verifica a cada 100ms
}

// ============================================================
// COMO USAR ESTE CÓDIGO:
// ============================================================
//
// 1. Faça upload deste código no ESP32
//
// 2. Abra o Serial Monitor (115200 baud)
//
// 3. Ligue UMA máquina por vez
//
// 4. Observe as mensagens:
//    - Qual GPIO detectou a mudança?
//    - Está detectando corretamente?
//    - O estado LOW/HIGH está correto?
//
// 5. Teste DESLIGAR a máquina
//
// 6. Verifique se detecta a mudança de volta
//
// EXEMPLO DE RESULTADO CORRETO:
// ------------------------------
// 1. Máquina desligada = PARADA (HIGH)
// 2. Liga a máquina = Muda para PRODUZINDO (LOW)
// 3. Desliga a máquina = Muda para PARADA (HIGH)
//
// SE ESTIVER INVERTIDO:
// ---------------------
// 1. Máquina desligada = PRODUZINDO (LOW)
// 2. Liga a máquina = Muda para PARADA (HIGH)
//
// → Neste caso, precisa inverter a lógica no código principal!
//
// ============================================================
