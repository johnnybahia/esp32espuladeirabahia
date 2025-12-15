# Sistema de Monitoramento de Produção - Marfim Bahia

Sistema de monitoramento em tempo real de máquinas espuladeiras utilizando ESP32, Google Sheets e interface web.

## 📋 Descrição do Sistema

Este sistema monitora 5 máquinas espuladeiras em tempo real, registrando tempos de produção e paradas em uma planilha Google Sheets e exibindo os dados em uma interface web interativa.

## 🏭 Máquinas Monitoradas

1. **ESPULADEIRA LONGO 2 BOCAS 1**
2. **ESPULADEIRA LONGO 2 BOCAS 2**
3. **ESPULADEIRA TORRE 4 BOCAS**
4. **ESPULADEIRA CHINESA 2 BOCAS 1**
5. **ESPULADEIRA CHINESA 2 BOCAS 2**

## 🔌 Mapeamento de Pinos GPIO do ESP32

### Conexões das Máquinas

| Máquina                       | GPIO ESP32 | Canal Físico | Observação         |
|-------------------------------|------------|--------------|-------------------|
| ESPULADEIRA LONGO 2 BOCAS 1   | **GPIO 27** | Canal 1      | Entrada Digital   |
| ESPULADEIRA LONGO 2 BOCAS 2   | **GPIO 26** | Canal 2      | Entrada Digital   |
| ESPULADEIRA TORRE 4 BOCAS     | **GPIO 25** | Canal 3      | Entrada Digital   |
| ESPULADEIRA CHINESA 2 BOCAS 1 | **GPIO 33** | Canal 4      | Entrada Digital   |
| ESPULADEIRA CHINESA 2 BOCAS 2 | **GPIO 32** | Canal 5      | Entrada Digital   |

### Lógica de Sinal

- **Sinal LOW (0V)**: Máquina em PRODUÇÃO
- **Sinal HIGH (3.3V)**: Máquina PARADA

### Configuração dos Pinos

- Todos os pinos estão configurados como `INPUT_PULLUP`
- Debounce configurado em 50ms para evitar leituras falsas
- Leitura não-bloqueante para garantir resposta rápida

## 🔧 Arquitetura do Sistema

### Componentes

1. **ESP32**: Microcontrolador que monitora os sensores das máquinas
2. **Google Apps Script**: Backend que processa e armazena os dados
3. **Google Sheets**: Banco de dados em nuvem
4. **Interface Web**: Dashboard HTML/JavaScript para visualização

### Comunicação

```
ESP32 → WiFi → Google Apps Script → Google Sheets
                      ↓
              Interface Web (HTML)
```

## 📡 Configuração de Rede

### WiFi

- **SSID**: `MARFIM_CEARA`
- **Senha**: Configurada no código
- **DNS**: 8.8.8.8 (Google DNS)

### URL do Google Script

```
https://script.google.com/macros/s/AKfycbxQdLvIma_qjqCBI1qy9pj320xlOEcLHjtsa1DzotntVjoxpl81TWP62VHNdgqkTIr-/exec
```

## 📊 Dados Coletados

Para cada máquina, o sistema registra:

- ✅ Tempo em produção (segundos)
- 🔴 Tempo parada (segundos)
- 📅 Data e hora de cada evento
- 🎯 Metas de produção por turno
- 📈 Histórico completo de eventos

## 🚀 Como Instalar

### 1. Upload do Código no ESP32

```bash
# Instalar biblioteca do ESP32 no Arduino IDE
# Conectar ESP32 via USB
# Selecionar placa: ESP32 Dev Module
# Upload do arquivo 'espuladeira'
```

### 2. Configurar Google Apps Script

1. Criar nova planilha Google Sheets
2. Acessar Extensões → Apps Script
3. Colar o código do arquivo `Código.gs`
4. Implantar como Web App
5. Copiar URL gerada

### 3. Atualizar Configurações

No arquivo `espuladeira`, ajustar:
- WiFi SSID e senha (se necessário)
- URL do Google Script (linha 12)

## 🔌 Conexão Física - Guia de Instalação

### Materiais Necessários

- ESP32 Dev Module
- Cabos jumper
- Fonte de alimentação 5V para ESP32
- Relés ou optoacopladores (se necessário para isolamento)

### Passo a Passo de Conexão

#### Para cada máquina:

1. **Identifique o sinal de saída da máquina** (normalmente um relé ou sensor)
2. **Conecte ao GPIO correspondente**:
   - Fio do sinal → GPIO (conforme tabela acima)
   - GND da máquina → GND do ESP32
3. **Verifique a tensão do sinal** (deve ser 3.3V max para ESP32)
4. **Use um optoacoplador se o sinal for > 3.3V**

#### Exemplo de Conexão - ESPULADEIRA LONGO 2 BOCAS 1:

```
Máquina (Sinal) ──→ GPIO 27
Máquina (GND)   ──→ GND ESP32
```

### ⚠️ IMPORTANTE - Segurança Elétrica

- ✋ **NUNCA conecte tensões acima de 3.3V diretamente no ESP32**
- 🔒 Use optoacopladores para isolar o ESP32 da máquina
- 🔌 Certifique-se de ter GND comum entre ESP32 e máquinas
- ⚡ Verifique polaridade antes de conectar

## 🖥️ Interface Web

### Funcionalidades

- 📊 Dashboard em tempo real
- 📈 Gráficos de produção últimos 30 dias
- 🔴 Alertas de paradas críticas
- 📋 Relatórios por família de máquinas
- 🔍 Busca de máquinas
- 📊 Estatísticas consolidadas

### Acesso

1. Abrir URL do Google Apps Script no navegador
2. Fazer login com credenciais configuradas
3. Visualizar dashboard em tempo real

## 🛠️ Manutenção

### Verificação de Conexão

O código ESP32 inclui mensagens de debug via Serial Monitor:
- Conexão WiFi
- Envio de dados
- Detecção de eventos

### Monitoramento

Abrir Serial Monitor (115200 baud) para ver:
```
Conectando WiFi....
Conectado! IP: 192.168.x.x
>> Evento detectado: ESPULADEIRA LONGO 2 BOCAS 1
>> [WIFI] Enviando: ESPULADEIRA LONGO 2 BOCAS 1 | Evento: PRODUZINDO
<< [WIFI] Sucesso! (200)
```

## 🔄 Multitarefa

O sistema utiliza os 2 núcleos do ESP32:

- **Core 1**: Leitura dos sensores (não-bloqueante)
- **Core 0**: Envio WiFi (não interfere na leitura)

Isso garante que nenhum evento seja perdido durante transmissões WiFi.

## 📞 Suporte

Para dúvidas ou problemas:
1. Verificar conexões físicas
2. Verificar Serial Monitor para mensagens de erro
3. Verificar conectividade WiFi
4. Verificar URL do Google Script

## 📝 Changelog

### Versão Atual (2025)
- ✅ Atualização para 5 máquinas
- ✅ Nova URL do Google Script
- ✅ Empresa: Marfim Bahia
- ✅ Mapeamento GPIO documentado
- ✅ Sistema multitarefa otimizado

---

**Desenvolvido para Marfim Bahia** 🏭
