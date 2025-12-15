# 📝 Resumo das Alterações Realizadas

## Data: 2025-12-15

### 🎯 Objetivo
Atualizar o sistema de monitoramento para a nova configuração da Marfim Bahia com 5 máquinas e nova fonte de dados.

---

## 🔧 Alterações Realizadas

### 1. Código ESP32 (`espuladeira`)

#### ✅ URL do Google Script Atualizada
- **Anterior**: `https://script.google.com/macros/s/AKfycbyoMZd9g_A7IIgcCajQm71OZTEf6R4kMWQvJXy79C6W8MR24OH_Q2sQ9-uko1q9uvH8fg/exec`
- **Nova**: `https://script.google.com/macros/s/AKfycbxQdLvIma_qjqCBI1qy9pj320xlOEcLHjtsa1DzotntVjoxpl81TWP62VHNdgqkTIr-/exec`

#### ✅ Máquinas Atualizadas (de 4 para 5)

**Configuração Anterior:**
```
ESPULADEIRA CHINESA 2 BOCAS
ESPULADEIRA TORRE 2 BOCAS
ESPULADEIRA TORRE 4 BOCAS
ESPULADEIRA LONGO 2 BOCAS
```

**Nova Configuração:**
```
ESPULADEIRA LONGO 2 BOCAS 1      → GPIO 27
ESPULADEIRA LONGO 2 BOCAS 2      → GPIO 26
ESPULADEIRA TORRE 4 BOCAS        → GPIO 25
ESPULADEIRA CHINESA 2 BOCAS 1    → GPIO 33
ESPULADEIRA CHINESA 2 BOCAS 2    → GPIO 32
```

#### ✅ Documentação de Pinos Adicionada
- Adicionado mapeamento detalhado de GPIO no código
- Comentários explicativos sobre cada conexão
- Tabela de referência rápida

---

### 2. Interface Web (`Index.html`)

#### ✅ Nome da Empresa Atualizado
- Logo atualizado para "Marfim Bahia"
- Mantida compatibilidade com sistema existente

---

### 3. Documentação Criada

#### ✅ README.md
Criado documento completo com:
- Descrição do sistema
- Lista de máquinas monitoradas
- Mapeamento completo GPIO
- Arquitetura do sistema
- Guia de instalação
- Procedimentos de manutenção
- Solução de problemas

#### ✅ GUIA_INSTALACAO_PINOS.md
Criado guia técnico detalhado com:
- Diagramas visuais de conexão
- Conexões por máquina (com desenhos ASCII)
- Tabela resumida de conexões com cores sugeridas
- Diagrama de proteção (optoacoplador)
- Checklist de instalação completo
- Lista de materiais necessários
- Avisos de segurança
- Tabela de testes
- Solução de problemas comuns

---

## 📊 Mapeamento de Pinos GPIO

| Canal | Máquina                       | GPIO ESP32 | Cabo Sugerido |
|-------|-------------------------------|------------|---------------|
| 1     | ESPULADEIRA LONGO 2 BOCAS 1   | GPIO 27    | Vermelho      |
| 2     | ESPULADEIRA LONGO 2 BOCAS 2   | GPIO 26    | Laranja       |
| 3     | ESPULADEIRA TORRE 4 BOCAS     | GPIO 25    | Amarelo       |
| 4     | ESPULADEIRA CHINESA 2 BOCAS 1 | GPIO 33    | Verde         |
| 5     | ESPULADEIRA CHINESA 2 BOCAS 2 | GPIO 32    | Azul          |

---

## ⚠️ Pontos Importantes

### Para Instalação Física:
1. **Conectar cada máquina no GPIO correspondente**
2. **Verificar que sinal é ≤ 3.3V** (usar optoacoplador se necessário)
3. **GND comum** entre ESP32 e todas as máquinas
4. **Testar uma máquina por vez** após instalação

### Para Programação:
1. **Fazer upload** do novo código no ESP32
2. **Verificar Serial Monitor** (115200 baud) após upload
3. **Confirmar conexão WiFi**
4. **Testar envio de dados** para cada máquina

---

## 🔍 Como Identificar Cada Entrada na Placa

### Ao Conectar os Cabos:

**ESPULADEIRA LONGO 2 BOCAS 1** → Procure o pino marcado **GPIO27** (ou D27)
**ESPULADEIRA LONGO 2 BOCAS 2** → Procure o pino marcado **GPIO26** (ou D26)
**ESPULADEIRA TORRE 4 BOCAS** → Procure o pino marcado **GPIO25** (ou D25)
**ESPULADEIRA CHINESA 2 BOCAS 1** → Procure o pino marcado **GPIO33** (ou D33)
**ESPULADEIRA CHINESA 2 BOCAS 2** → Procure o pino marcado **GPIO32** (ou D32)

**GND** → Qualquer pino marcado como GND (tem vários na placa)

---

## ✅ Checklist de Validação

- [x] URL do Google Script atualizada
- [x] 5 máquinas configuradas no código
- [x] Pinos GPIO definidos e documentados
- [x] Comentários explicativos adicionados no código
- [x] Nome da empresa atualizado (Marfim Bahia)
- [x] README.md criado
- [x] Guia de instalação de pinos criado
- [x] Documentação de segurança incluída
- [x] Tabelas de referência rápida criadas

---

## 📋 Próximos Passos Recomendados

1. **Fazer upload do código atualizado no ESP32**
2. **Conectar fisicamente cada máquina conforme tabela**
3. **Testar conexão de cada máquina individualmente**
4. **Verificar envio de dados no Serial Monitor**
5. **Confirmar dados chegando na planilha Google**
6. **Validar visualização na interface web**

---

## 📞 Suporte

Em caso de dúvidas sobre as alterações:
1. Consultar `README.md` para visão geral
2. Consultar `GUIA_INSTALACAO_PINOS.md` para detalhes técnicos
3. Verificar Serial Monitor para debug
4. Revisar este documento para entender o que foi alterado

---

**Alterações realizadas por:** Claude Code
**Data:** 2025-12-15
**Versão:** 2.0 - Marfim Bahia (5 máquinas)
