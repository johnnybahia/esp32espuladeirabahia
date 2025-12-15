# 🔌 Configuração para Relé de Contato Seco

## 📋 Entendendo o Relé de Contato Seco

Sua máquina usa um relé de contato seco. Ele funciona de uma destas formas:

### **TIPO A: Relé Normalmente Aberto (NA)**
```
Máquina DESLIGADA → Relé ABERTO → GPIO lê HIGH (1)
Máquina LIGADA    → Relé FECHA  → GPIO lê LOW (0)
```
**Código atual está CORRETO para este tipo** ✓

### **TIPO B: Relé Normalmente Fechado (NF)**
```
Máquina DESLIGADA → Relé FECHA → GPIO lê LOW (0)
Máquina LIGADA    → Relé ABRE  → GPIO lê HIGH (1)
```
**Código atual está INVERTIDO para este tipo** ❌

---

## 🧪 Como Descobrir Qual Tipo Você Tem

### **MÉTODO 1: Teste Visual (Mais Fácil)**

1. Faça upload do código `TESTE_SENSOR.ino`
2. Abra Serial Monitor (115200 baud)
3. **Com máquina DESLIGADA**, veja o que aparece:
   - Aparece `PARADA (HIGH)` → Você tem TIPO A (NA) ✓
   - Aparece `PRODUZINDO (LOW)` → Você tem TIPO B (NF) ❌

4. **LIGUE a máquina** e veja se muda:
   - Mudou para `PRODUZINDO (LOW)` → TIPO A - Código correto! ✓
   - Mudou para `PARADA (HIGH)` → TIPO B - Precisa inverter! ❌

### **MÉTODO 2: Teste com Multímetro**

1. **DESLIGUE a máquina**
2. **Desconecte os cabos** do relé
3. **Meça continuidade** entre os 2 terminais do relé:
   - **SEM continuidade** → TIPO A (NA) ✓
   - **COM continuidade** → TIPO B (NF) ❌

4. **LIGUE a máquina**
5. **Meça continuidade** novamente:
   - **COM continuidade** → TIPO A (NA) ✓
   - **SEM continuidade** → TIPO B (NF) ❌

---

## 🔧 Correção do Código (SE NECESSÁRIO)

### ✅ **SE VOCÊ TEM TIPO A (NA) - Normalmente Aberto**

**O código atual JÁ ESTÁ CORRETO!**

Não precisa fazer nada. O código em `espuladeira` já funciona assim:
```cpp
bool estavaProduzindo = (estadoAtual[i] == LOW);
```

### ❌ **SE VOCÊ TEM TIPO B (NF) - Normalmente Fechado**

**PRECISA INVERTER A LÓGICA**

No arquivo `espuladeira`, **linha 182**, troque:

**DE:**
```cpp
bool estavaProduzindo = (estadoAtual[i] == LOW);
```

**PARA:**
```cpp
bool estavaProduzindo = (estadoAtual[i] == HIGH);
```

Depois faça **novo upload no ESP32**.

---

## 📊 Diagrama de Conexão (Ambos os Tipos)

```
┌─────────────────────┐         ┌──────────────┐
│   MÁQUINA           │         │    ESP32     │
│                     │         │              │
│  ┌──────────────┐   │         │              │
│  │ Relé Contato │   │         │              │
│  │   Seco       │   │         │              │
│  │              │   │         │              │
│  │  Terminal 1 ─┼───┼─────────┤ GPIO XX      │
│  │              │   │         │              │
│  │  Terminal 2 ─┼───┼─────────┤ GND          │
│  │              │   │         │              │
│  └──────────────┘   │         │              │
│                     │         │              │
└─────────────────────┘         └──────────────┘

IMPORTANTE:
- Não importa qual terminal vai em qual GPIO
- Pode trocar Terminal 1 ↔ Terminal 2
- O que importa é descobrir a lógica NA ou NF
```

---

## 🎯 Passo a Passo Completo

### **PASSO 1: Identificar o Tipo**
- [ ] Usei TESTE_SENSOR.ino para identificar
- [ ] Resultado: TIPO A (NA) ou TIPO B (NF)?

### **PASSO 2: Ajustar Código (se necessário)**
- [ ] Se TIPO A → Nada a fazer ✓
- [ ] Se TIPO B → Inverti a linha 182

### **PASSO 3: Testar**
- [ ] Fiz upload do código corrigido
- [ ] Testei com máquina desligada
- [ ] Testei ligando a máquina
- [ ] Testei desligando a máquina

### **PASSO 4: Validar**
- [ ] Máquina desligada → Serial Monitor mostra "PARADA"
- [ ] Liguei máquina → Serial Monitor mostra "PRODUZINDO"
- [ ] Desliguei máquina → Serial Monitor mostra "PARADA"

---

## 💡 Dicas Importantes

### **Bouncing (Ruído)**
Relés podem ter "bouncing" (contato instável). O código já tem:
```cpp
unsigned long debounceDelay = 50; // 50ms de filtro
```

Se tiver muito ruído (muitas detecções falsas), aumente para:
```cpp
unsigned long debounceDelay = 200; // 200ms de filtro
```

### **Teste de Continuidade**
Se seu relé tem mais de 2 terminais, pode ser:
- **3 terminais**: Comum (C), Normalmente Aberto (NA), Normalmente Fechado (NF)
  - Use: **Comum (C) + NA** para TIPO A
  - Use: **Comum (C) + NF** para TIPO B

---

## 📝 Resumo

| Comportamento | Tipo | Ação |
|---------------|------|------|
| Desligada=HIGH, Ligada=LOW | TIPO A (NA) | Código OK ✓ |
| Desligada=LOW, Ligada=HIGH | TIPO B (NF) | Inverter linha 182 |

---

**Após identificar e ajustar, teste e confirme que está funcionando!** 🚀
