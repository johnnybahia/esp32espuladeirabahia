# 🔌 Guia Completo de Instalação - Pinos GPIO ESP32

## 📍 Diagrama de Conexões

```
╔══════════════════════════════════════════════════════════════════╗
║                         ESP32 - PINOUT                           ║
╚══════════════════════════════════════════════════════════════════╝

                    ┌─────────────────────┐
                    │                     │
                    │      ESP32 DEV      │
                    │                     │
     GND ◄──────────┤ GND            3.3V ├──────────► 3.3V
                    │                     │
  Canal 1 ◄──────────┤ GPIO 27        GND ├──────────► GND
  Canal 2 ◄──────────┤ GPIO 26            │
  Canal 3 ◄──────────┤ GPIO 25            │
  Canal 4 ◄──────────┤ GPIO 33            │
  Canal 5 ◄──────────┤ GPIO 32            │
                    │                     │
                    │                     │
                    └─────────────────────┘
```

## 🏭 Conexões por Máquina

### Canal 1 - ESPULADEIRA LONGO 2 BOCAS 1
```
┌─────────────────────────────┐         ┌──────────────┐
│ ESPULADEIRA LONGO 2 BOCAS 1 │         │    ESP32     │
│                             │         │              │
│  [Sensor/Relé]              │         │              │
│      │                      │         │              │
│      ├─── Sinal ────────────┼─────────┤ GPIO 27      │
│      │                      │         │              │
│      └─── GND ──────────────┼─────────┤ GND          │
└─────────────────────────────┘         └──────────────┘

🔴 IMPORTANTE: Sinal deve ser 0-3.3V
```

### Canal 2 - ESPULADEIRA LONGO 2 BOCAS 2
```
┌─────────────────────────────┐         ┌──────────────┐
│ ESPULADEIRA LONGO 2 BOCAS 2 │         │    ESP32     │
│                             │         │              │
│  [Sensor/Relé]              │         │              │
│      │                      │         │              │
│      ├─── Sinal ────────────┼─────────┤ GPIO 26      │
│      │                      │         │              │
│      └─── GND ──────────────┼─────────┤ GND          │
└─────────────────────────────┘         └──────────────┘

🔴 IMPORTANTE: Sinal deve ser 0-3.3V
```

### Canal 3 - ESPULADEIRA TORRE 4 BOCAS
```
┌─────────────────────────────┐         ┌──────────────┐
│  ESPULADEIRA TORRE 4 BOCAS  │         │    ESP32     │
│                             │         │              │
│  [Sensor/Relé]              │         │              │
│      │                      │         │              │
│      ├─── Sinal ────────────┼─────────┤ GPIO 25      │
│      │                      │         │              │
│      └─── GND ──────────────┼─────────┤ GND          │
└─────────────────────────────┘         └──────────────┘

🔴 IMPORTANTE: Sinal deve ser 0-3.3V
```

### Canal 4 - ESPULADEIRA CHINESA 2 BOCAS 1
```
┌─────────────────────────────┐         ┌──────────────┐
│ESPULADEIRA CHINESA 2 BOCAS 1│         │    ESP32     │
│                             │         │              │
│  [Sensor/Relé]              │         │              │
│      │                      │         │              │
│      ├─── Sinal ────────────┼─────────┤ GPIO 33      │
│      │                      │         │              │
│      └─── GND ──────────────┼─────────┤ GND          │
└─────────────────────────────┘         └──────────────┘

🔴 IMPORTANTE: Sinal deve ser 0-3.3V
```

### Canal 5 - ESPULADEIRA CHINESA 2 BOCAS 2
```
┌─────────────────────────────┐         ┌──────────────┐
│ESPULADEIRA CHINESA 2 BOCAS 2│         │    ESP32     │
│                             │         │              │
│  [Sensor/Relé]              │         │              │
│      │                      │         │              │
│      ├─── Sinal ────────────┼─────────┤ GPIO 32      │
│      │                      │         │              │
│      └─── GND ──────────────┼─────────┤ GND          │
└─────────────────────────────┘         └──────────────┘

🔴 IMPORTANTE: Sinal deve ser 0-3.3V
```

## 📋 Tabela Resumida de Conexões

| Canal | Máquina                       | GPIO  | Cor Sugerida Cabo | Observação |
|-------|-------------------------------|-------|-------------------|------------|
| 1     | ESPULADEIRA LONGO 2 BOCAS 1   | 27    | 🔴 Vermelho       | Sinal      |
| 2     | ESPULADEIRA LONGO 2 BOCAS 2   | 26    | 🟠 Laranja        | Sinal      |
| 3     | ESPULADEIRA TORRE 4 BOCAS     | 25    | 🟡 Amarelo        | Sinal      |
| 4     | ESPULADEIRA CHINESA 2 BOCAS 1 | 33    | 🟢 Verde          | Sinal      |
| 5     | ESPULADEIRA CHINESA 2 BOCAS 2 | 32    | 🔵 Azul           | Sinal      |
| -     | Todos                         | GND   | ⚫ Preto          | Terra comum|

## ⚡ Diagrama de Proteção (SE NECESSÁRIO)

### Caso o sinal da máquina seja > 3.3V, use um optoacoplador:

```
Máquina (5V/12V/24V)          Optoacoplador              ESP32
    │                              │                       │
    ├─── Sinal ──────► LED+ ───   │                       │
    │                  LED-  ───┐  │                       │
    └─── GND ─────────────────┘  │                       │
                                  │                       │
                              VCC ├──────────────────► 3.3V
                              GND ├──────────────────► GND
                          OUTPUT  ├──────────────────► GPIO XX
```

**Modelo sugerido**: PC817 (optoacoplador comum)

## 🔧 Checklist de Instalação

### Antes de Ligar

- [ ] Verificar que todos os cabos estão bem conectados
- [ ] Verificar que GND está comum entre ESP32 e máquinas
- [ ] Verificar tensão de sinal (multímetro) - deve ser ≤ 3.3V
- [ ] Verificar que não há curto-circuito entre pinos
- [ ] Código carregado corretamente no ESP32

### Após Ligar

- [ ] LED do ESP32 acende
- [ ] Abrir Serial Monitor (115200 baud)
- [ ] Verificar mensagem "Conectando WiFi..."
- [ ] Verificar mensagem "Conectado! IP: xxx.xxx.xxx.xxx"
- [ ] Verificar mensagem "SISTEMA MULTITAREFA INICIADO!"

### Teste Individual de Cada Máquina

1. Ligar máquina 1 (ESPULADEIRA LONGO 2 BOCAS 1)
2. Verificar no Serial Monitor: ">> Evento detectado: ESPULADEIRA LONGO 2 BOCAS 1"
3. Verificar envio: "<< [WIFI] Sucesso! (200)"
4. Repetir para cada máquina

## 🛠️ Ferramentas Necessárias

- 🔧 Chave Phillips/Fenda (para abertura de caixas)
- 🔌 Multímetro (para medir tensões)
- ✂️ Alicate de corte
- 🔨 Alicate de crimpar (se usar terminais)
- 📏 Régua/Fita métrica
- 🏷️ Etiquetas para identificar cabos
- 💻 Computador com Arduino IDE

## 📝 Lista de Materiais

### Essenciais

- 1x ESP32 Dev Module
- 1x Cabo USB (para programação)
- 1x Fonte 5V (para alimentar ESP32)
- 5x Cabos de sinal (comprimento conforme layout da fábrica)
- 5x Cabos GND (ou usar GND comum)

### Opcionais (Proteção)

- 5x Optoacopladores PC817 (se sinal > 3.3V)
- 5x Resistores 220Ω (para LED do optoacoplador)
- 1x Caixa de proteção para ESP32
- Terminais/conectores conforme necessidade

## ⚠️ AVISOS DE SEGURANÇA

### 🚨 ATENÇÃO

1. **DESLIGAR ENERGIA** antes de fazer conexões
2. **NÃO conectar sinais > 3.3V** diretamente no ESP32
3. **USAR proteção (optoacoplador)** se sinal > 3.3V
4. **VERIFICAR polaridade** antes de ligar
5. **TER GND COMUM** entre ESP32 e todas as máquinas
6. **NÃO trabalhar sozinho** em instalações elétricas
7. **USAR EPI** adequado

### 📞 Em Caso de Problemas

1. **Desligar tudo imediatamente**
2. **Verificar todas as conexões**
3. **Medir tensões com multímetro**
4. **Consultar Serial Monitor** para mensagens de erro
5. **Revisar este guia** passo a passo

## 🎯 Solução de Problemas Comuns

### Problema: ESP32 não conecta no WiFi
**Solução**:
- Verificar SSID e senha no código
- Verificar se WiFi está disponível
- Aproximar ESP32 do roteador

### Problema: Máquina não é detectada
**Solução**:
- Verificar conexão do cabo no GPIO correto
- Verificar GND comum
- Verificar sinal com multímetro
- Testar manualmente ligando/desligando máquina

### Problema: Dados não aparecem na planilha
**Solução**:
- Verificar URL do Google Script
- Verificar conexão WiFi
- Verificar Serial Monitor para erros HTTP
- Testar URL manualmente no navegador

### Problema: ESP32 reinicia sozinho
**Solução**:
- Verificar alimentação (fonte adequada)
- Verificar se não há curto-circuito
- Verificar se código não tem loop infinito

## 📊 Tabela de Testes

| Máquina                       | GPIO | Teste OK | Data Teste | Responsável |
|-------------------------------|------|----------|------------|-------------|
| ESPULADEIRA LONGO 2 BOCAS 1   | 27   | [ ]      |            |             |
| ESPULADEIRA LONGO 2 BOCAS 2   | 26   | [ ]      |            |             |
| ESPULADEIRA TORRE 4 BOCAS     | 25   | [ ]      |            |             |
| ESPULADEIRA CHINESA 2 BOCAS 1 | 33   | [ ]      |            |             |
| ESPULADEIRA CHINESA 2 BOCAS 2 | 32   | [ ]      |            |             |

---

**Imprima este guia e mantenha na área de instalação** 📋
