# 📊 Comparação: Código Antigo (Funcionando) vs Código Novo

## ✅ CONCLUSÃO: Os códigos são IDÊNTICOS em lógica!

---

## 🔍 Diferenças Encontradas:

### **1. URL do Google Script**
```cpp
// CÓDIGO ANTIGO (funcionando):
GoogleScriptURL = "...AKfycbyoMZd9g_A7IIgcCajQm71OZTEf6R4kMWQvJXy79C6W8MR24OH_Q2sQ9-uko1q9uvH8fg/exec";

// CÓDIGO NOVO:
GoogleScriptURL = "...AKfycbxQdLvIma_qjqCBI1qy9pj320xlOEcLHjtsa1DzotntVjoxpl81TWP62VHNdgqkTIr-/exec";
```
✅ **Normal** - URLs diferentes para planilhas diferentes

---

### **2. Número de Máquinas**
```cpp
// CÓDIGO ANTIGO:
const int qtdMaquinas = 4;
int pinos[qtdMaquinas] = {27, 26, 25, 33};

// CÓDIGO NOVO:
const int qtdMaquinas = 5;
int pinos[qtdMaquinas] = {27, 26, 25, 33, 32};
```
✅ **Normal** - 5 máquinas agora (adicionou GPIO 32)

---

### **3. Nomes das Máquinas**
```cpp
// CÓDIGO ANTIGO:
"ESPULADEIRA CHINESA 2 BOCAS"
"ESPULADEIRA TORRE 2 BOCAS"
"ESPULADEIRA TORRE 4 BOCAS"
"ESPULADEIRA LONGO 2 BOCAS"

// CÓDIGO NOVO:
"ESPULADEIRA LONGO 2 BOCAS 1"
"ESPULADEIRA LONGO 2 BOCAS 2"
"ESPULADEIRA TORRE 4 BOCAS"
"ESPULADEIRA CHINESA 2 BOCAS 1"
"ESPULADEIRA CHINESA 2 BOCAS 2"
```
✅ **Normal** - Nomes atualizados

---

## 🎯 LÓGICA IDÊNTICA EM AMBOS:

### **Linha Crítica (IGUAL nos 2 códigos):**
```cpp
bool estavaProduzindo = (estadoAtual[i] == LOW);
```

**Isso significa:**
- LOW = PRODUZINDO
- HIGH = PARADA

✅ **Se o código antigo funciona com esta lógica, o novo também deveria!**

---

## ❓ Por que o código novo só detecta "PARADA"?

### **Possíveis causas:**

#### **1️⃣ Máquinas Novas Têm Relé Diferente**
```
Código Antigo → Máquinas antigas → Relé TIPO A (NA)
Código Novo   → Máquinas novas   → Relé TIPO B (NF) ???
```

**HIPÓTESE MAIS PROVÁVEL:**
- As máquinas **ANTIGAS** usam relé Normalmente Aberto (NA)
- As máquinas **NOVAS** usam relé Normalmente Fechado (NF)

**TESTE:**
1. Pegue o ESP32 que está funcionando (código antigo)
2. Conecte no GPIO 27 da máquina ANTIGA
3. Veja se funciona → SIM
4. Conecte no GPIO 27 da máquina NOVA
5. Veja se funciona → ???

Se não funcionar com a máquina nova, confirma que o relé é diferente!

---

#### **2️⃣ Máquinas Novas Estão Desligadas**
```
Se as 5 máquinas novas estiverem desligadas:
→ Relé ABERTO → GPIO lê HIGH → Detecta "PARADA"
```

**TESTE:**
- LIGUE uma das máquinas novas
- Deixe rodando por 30 segundos
- DESLIGUE
- Veja se envia "TEMPO PRODUZINDO"

---

#### **3️⃣ Conexão Física Diferente**
```
Máquinas antigas: Terminal A = Sinal, Terminal B = GND
Máquinas novas  : Terminal B = Sinal, Terminal A = GND ???
```

**TESTE:**
- Inverta os terminais do relé
- Veja se passa a funcionar

---

## 🔧 SOLUÇÃO RÁPIDA

### **SE as máquinas novas têm relé invertido:**

No código novo, **TROQUE a linha 182:**

**DE:**
```cpp
bool estavaProduzindo = (estadoAtual[i] == LOW);
```

**PARA:**
```cpp
bool estavaProduzindo = (estadoAtual[i] == HIGH);
```

---

## 📋 Checklist de Diagnóstico

- [ ] Testei código antigo em máquina antiga → Funciona?
- [ ] Testei código antigo em máquina nova → Funciona?
- [ ] Se não funcionar → Relé é diferente!
- [ ] Liguei máquina nova por 30s e desliguei
- [ ] Observei se envia "PRODUZINDO"
- [ ] Se não enviar → Precisa inverter lógica

---

## ✅ RESUMO

**O código está CORRETO!**

A diferença está nas **máquinas**, não no código.

**Próximo passo:**
1. Teste com o código `TESTE_SENSOR.ino`
2. Veja o estado com máquina DESLIGADA
3. Veja o estado com máquina LIGADA
4. Se estiver invertido → Mude 1 linha (182)

---

**O código está perfeito! Só precisa ajustar para o tipo de relé das máquinas novas.** ✓
