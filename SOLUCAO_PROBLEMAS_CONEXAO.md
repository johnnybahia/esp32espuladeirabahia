# 🔧 Solução de Problemas - ESP32 não enviando dados para Planilha

## 🎯 Problema Relatado
O ESP32 está executando o procedimento mas a informação não chega na planilha Google.

---

## ✅ Checklist de Diagnóstico

### 1️⃣ **Verificar Serial Monitor do ESP32**

Abra o Serial Monitor (115200 baud) e observe as mensagens:

#### ✅ Se aparecer: `<< [WIFI] Sucesso! (200)`
- **Significado**: ESP32 está enviando corretamente
- **Problema**: Está no Google Apps Script
- **Vá para**: Seção 2 (Verificar Google Apps Script)

#### ❌ Se aparecer: `xx [WIFI] Erro: -1` ou similar
- **Significado**: Problema de conexão WiFi
- **Solução**: Verificar SSID e senha WiFi
- **Vá para**: Seção 3 (Problemas de WiFi)

#### ❌ Se aparecer: `<< [WIFI] HTTP Error: 302` ou `404`
- **Significado**: URL do Google Script incorreta ou não implantada
- **Vá para**: Seção 4 (Verificar URL do Script)

#### ❌ Se aparecer: `<< [WIFI] HTTP Error: 403`
- **Significado**: Problema de permissões no Google Script
- **Vá para**: Seção 5 (Configurar Permissões)

---

## 2️⃣ **Verificar Google Apps Script**

### Passo 1: Verificar se o script está implantado

1. Acesse: https://script.google.com
2. Abra seu projeto do Apps Script
3. Clique em **"Implantar"** → **"Gerenciar implantações"**
4. Verifique se há uma implantação ativa
5. **IMPORTANTE**: Se fez alterações recentes, precisa fazer uma **NOVA IMPLANTAÇÃO**

### Passo 2: Verificar ID da Planilha no Código.gs

No arquivo `Código.gs`, procure esta linha:

```javascript
const ID_PLANILHA = "1jApQbNfM7gUyIL9b3I0CuEFePlnr2DMKeuARCIjrq7g";
```

**Verifique se este ID está correto:**
1. Abra sua planilha Google Sheets
2. Olhe a URL: `https://docs.google.com/spreadsheets/d/[ID_AQUI]/edit`
3. Copie o ID da URL
4. Substitua no código se estiver diferente

### Passo 3: Verificar nome da aba na planilha

O código procura por uma aba chamada **"Página1"**. Verifique se:
- [ ] A planilha tem uma aba chamada exatamente "Página1"
- [ ] Se não tiver, renomeie a aba para "Página1"
- [ ] Ou altere o código para usar o nome correto

---

## 3️⃣ **Problemas de WiFi**

### Se o ESP32 não conecta no WiFi:

```cpp
// Verificar no código espuladeira:
const char* ssid = "MARFIM_CEARA";      // Está correto?
const char* password = "marfimm0403";   // Está correta?
```

**Teste:**
1. Conecte seu celular no WiFi "MARFIM_CEARA"
2. Use a senha "marfimm0403"
3. Se conectar → WiFi OK
4. Se não conectar → Verificar nome/senha do WiFi

---

## 4️⃣ **Verificar e Atualizar URL do Google Script**

### Como obter a URL correta:

1. Acesse: https://script.google.com
2. Abra seu projeto
3. Clique em **"Implantar"** → **"Nova implantação"**
4. Em "Tipo", selecione **"Aplicativo da Web"**
5. Configure:
   - **Executar como**: Eu (seu email)
   - **Quem tem acesso**: Qualquer pessoa
6. Clique em **"Implantar"**
7. **COPIE A URL** que aparecer
8. Cole no código ESP32:

```cpp
String GoogleScriptURL = "SUA_URL_AQUI";
```

### ⚠️ IMPORTANTE:
- Toda vez que alterar o código do Google Apps Script, precisa fazer uma **NOVA IMPLANTAÇÃO**
- Use **"Nova implantação"** (não reutilizar a antiga se mudou o código)

---

## 5️⃣ **Configurar Permissões Corretamente**

### No Google Apps Script:

1. Clique em **"Implantar"** → **"Nova implantação"**
2. Em **"Quem tem acesso"**, selecione: **"Qualquer pessoa"**
3. Confirme e copie a nova URL
4. Atualize a URL no código ESP32

### Dar permissões ao script:

1. No editor do Apps Script, clique em **"Executar"** (▶️)
2. Escolha a função `doGet`
3. Autorize o acesso quando solicitado
4. Aceite todas as permissões

---

## 6️⃣ **Testar URL Manualmente (MUITO IMPORTANTE!)**

### Teste a URL no navegador:

Copie a URL do Google Script e adicione parâmetros de teste:

```
SUA_URL?maquina=TESTE&evento=TEMPO%20PRODUZINDO&duracao=10
```

**Exemplo completo:**
```
https://script.google.com/macros/s/AKfycbxQdLvIma_qjqCBI1qy9pj320xlOEcLHjtsa1DzotntVjoxpl81TWP62VHNdgqkTIr-/exec?maquina=TESTE&evento=TEMPO%20PRODUZINDO&duracao=10
```

**Cole no navegador e pressione Enter.**

#### ✅ Se aparecer "OK":
- Google Script está funcionando!
- Verifique se apareceu uma linha na planilha
- Se apareceu → Problema está no ESP32
- Se não apareceu → Problema no código do Apps Script

#### ❌ Se aparecer erro ou página em branco:
- URL incorreta ou script não implantado corretamente
- Refaça a implantação (passos na seção 4)

---

## 7️⃣ **Verificar Estrutura da Planilha**

A planilha deve ter:

### Aba "Página1" com colunas:
| Data | Hora | Máquina | Evento | Duração |
|------|------|---------|--------|---------|

### Outras abas necessárias:
- **LOGIN**: Para controle de acesso
- **TURNOS**: Para configuração de turnos
- **FAMILIAS**: Para agrupamento de máquinas

**Se não tiver essas abas, o sistema pode não funcionar corretamente.**

---

## 8️⃣ **Código de Teste Simplificado**

Se quiser testar apenas a comunicação, use este código simplificado no ESP32:

```cpp
#include <WiFi.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>

const char* ssid = "MARFIM_CEARA";
const char* password = "marfimm0403";
String GoogleScriptURL = "SUA_URL_AQUI";

void setup() {
  Serial.begin(115200);

  WiFi.begin(ssid, password);
  Serial.print("Conectando WiFi");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado!");
  Serial.println("IP: " + WiFi.localIP().toString());

  // TESTE DE ENVIO
  Serial.println("\n=== INICIANDO TESTE ===");
  enviarTeste();
}

void enviarTeste() {
  if(WiFi.status() == WL_CONNECTED) {
    WiFiClientSecure client;
    client.setInsecure();
    HTTPClient http;

    String url = GoogleScriptURL + "?maquina=TESTE&evento=TEMPO%20PRODUZINDO&duracao=99";

    Serial.println("URL: " + url);

    http.begin(client, url);
    int httpCode = http.GET();

    Serial.print("HTTP Code: ");
    Serial.println(httpCode);

    if (httpCode > 0) {
      String payload = http.getString();
      Serial.println("Resposta: " + payload);
    } else {
      Serial.println("Erro: " + http.errorToString(httpCode));
    }

    http.end();
  }
}

void loop() {
  delay(10000);
}
```

**Como usar:**
1. Substitua `"SUA_URL_AQUI"` pela URL do seu Google Script
2. Faça upload no ESP32
3. Abra Serial Monitor (115200 baud)
4. Observe a resposta
5. Verifique se apareceu na planilha

---

## 9️⃣ **Checklist Final de Verificação**

- [ ] WiFi conectado (Serial Monitor mostra IP)
- [ ] URL do Google Script correta
- [ ] Google Script implantado como "Aplicativo da Web"
- [ ] Permissões: "Qualquer pessoa"
- [ ] Planilha tem aba "Página1"
- [ ] ID da planilha correto no Código.gs
- [ ] Teste manual da URL no navegador funcionou
- [ ] Aparece "OK" quando testa a URL
- [ ] Dados aparecem na planilha no teste manual

---

## 🔟 **Principais Causas do Problema**

### 🥇 Causa #1 (mais comum): Script não reimplantado
**Solução**: Fazer nova implantação após alterações no código

### 🥈 Causa #2: Permissões incorretas
**Solução**: Configurar "Quem tem acesso" como "Qualquer pessoa"

### 🥉 Causa #3: URL antiga no ESP32
**Solução**: Copiar URL da nova implantação

### Causa #4: ID da planilha incorreto
**Solução**: Verificar ID no Código.gs

### Causa #5: Nome da aba diferente
**Solução**: Renomear aba para "Página1" ou ajustar código

---

## 📞 **Próximos Passos**

1. **Execute o teste manual da URL no navegador** (Seção 6)
2. **Relate o resultado**:
   - Se aparecer "OK" → Problema no ESP32
   - Se der erro → Problema no Google Script
3. **Envie as mensagens do Serial Monitor**
4. **Informe o que aparece no navegador ao testar a URL**

---

## 💡 **Dica Importante**

A causa mais comum deste problema é:
**O Google Apps Script foi alterado mas não foi REIMPLANTADO**

Sempre que alterar o código do Apps Script:
1. Salvar (Ctrl+S)
2. **Implantar** → **Nova implantação**
3. Copiar a **nova URL**
4. Atualizar a URL no ESP32
5. Fazer novo upload no ESP32

---

**Boa sorte na resolução!** 🚀
