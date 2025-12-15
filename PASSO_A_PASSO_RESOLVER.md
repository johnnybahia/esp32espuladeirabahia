# 🔧 PASSO A PASSO - Resolver Problema de Dados Não Chegando na Planilha

## ✅ Status Atual
- ESP32 conectado: ✓
- ESP32 enviando dados: ✓
- Resposta HTTP 200 (OK): ✓
- **Dados NÃO aparecem na planilha: ✗**

---

## 🎯 SOLUÇÃO - Siga EXATAMENTE estes passos:

### **PASSO 1: Verificar ID da Planilha**

#### 1.1 - Abra sua planilha Google Sheets (a nova)

#### 1.2 - Copie o ID da URL
A URL é assim:
```
https://docs.google.com/spreadsheets/d/[ESTE_É_O_ID]/edit
```

Exemplo:
```
https://docs.google.com/spreadsheets/d/1a2B3c4D5e6F7g8H9i0J1k2L3m4N5o6P7q8R9s0T1u2V/edit
                                    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                                    COPIE ESTA PARTE
```

#### 1.3 - Anote o ID aqui:
```
ID da sua planilha: _________________________________
```

#### 1.4 - Compare com o que está no Código.gs
No seu Google Apps Script, procure esta linha:
```javascript
const ID_PLANILHA = "1jApQbNfM7gUyIL9b3I0CuEFePlnr2DMKeuARCIjrq7g";
```

**❓ Os IDs são iguais?**
- [ ] SIM - Vá para o Passo 2
- [ ] NÃO - Atualize o ID no Código.gs e vá para o Passo 4

---

### **PASSO 2: Verificar Nome da Aba**

#### 2.1 - Na sua planilha, verifique:
Você tem uma aba chamada **exatamente** `Página1` ?

**❓ Tem a aba "Página1"?**
- [ ] SIM - Vá para o Passo 3
- [ ] NÃO - Renomeie a aba para "Página1" e vá para o Passo 3

**Dica:** O nome deve ser EXATAMENTE "Página1" (com "P" maiúsculo e acento no "a")

---

### **PASSO 3: Usar Código com Debug**

#### 3.1 - Abra https://script.google.com

#### 3.2 - Abra seu projeto

#### 3.3 - **SUBSTITUA TODO O CÓDIGO** pelo conteúdo do arquivo `Código_Debug.gs` que criei

#### 3.4 - **ATUALIZE O ID DA PLANILHA** na linha 6 (use o ID que você copiou no Passo 1.2)

#### 3.5 - Salve o código (Ctrl+S)

---

### **PASSO 4: Reimplantar**

#### 4.1 - Clique em **"Implantar"** → **"Nova implantação"**

#### 4.2 - Configure:
- **Tipo**: Aplicativo da Web
- **Descrição**: Debug Marfim Bahia
- **Executar como**: Eu
- **Quem tem acesso**: **Qualquer pessoa** ⚠️ IMPORTANTE!

#### 4.3 - Clique **"Implantar"**

#### 4.4 - Copie a URL gerada

#### 4.5 - **❓ A URL é diferente da que está no ESP32?**
- [ ] SIM - Atualize no código ESP32 e faça novo upload
- [ ] NÃO - Continue

---

### **PASSO 5: Testar com Função Debug**

#### 5.1 - No Google Apps Script, selecione a função `testarGravacao`

#### 5.2 - Clique em **"Executar"** (▶️)

#### 5.3 - Autorize o script se solicitado

#### 5.4 - Clique em **"Execuções"** (menu lateral esquerdo)

#### 5.5 - Clique na execução mais recente

#### 5.6 - **LEIA OS LOGS** e anote aqui:

```
✓ ID da planilha aberto: _______________________
✓ Nome da planilha: ____________________________
✓ Aba encontrada: ______________________________
✓ Dados gravados: [ ] SIM  [ ] NÃO
```

#### 5.7 - Vá na planilha e verifique:
**❓ Apareceu uma linha com "TESTE_MANUAL_FUNCAO"?**
- [ ] SIM - Problema resolvido! Vá para o Passo 6
- [ ] NÃO - Vá para o Passo 7 (Diagnóstico Avançado)

---

### **PASSO 6: Testar via URL (Teste Final)**

#### 6.1 - Abra o navegador

#### 6.2 - Cole a URL do seu Google Apps Script e adicione os parâmetros:
```
SUA_URL?maquina=TESTE_NAVEGADOR&evento=TEMPO%20PRODUZINDO&duracao=777
```

Exemplo completo:
```
https://script.google.com/macros/s/AKfycbxQdLvIma_qjqCBI1qy9pj320xlOEcLHjtsa1DzotntVjoxpl81TWP62VHNdgqkTIr-/exec?maquina=TESTE_NAVEGADOR&evento=TEMPO%20PRODUZINDO&duracao=777
```

#### 6.3 - Pressione Enter

#### 6.4 - **❓ O que aparece na tela?**
- [ ] "OK"
- [ ] Erro (qual?): _______________________
- [ ] Página em branco

#### 6.5 - Vá na planilha
**❓ Apareceu linha com "TESTE_NAVEGADOR"?**
- [ ] SIM - ✅ PROBLEMA RESOLVIDO! ESP32 vai funcionar!
- [ ] NÃO - Vá para o Passo 7

---

### **PASSO 7: Diagnóstico Avançado**

Se chegou aqui, o problema pode ser:

#### Causa A: Permissões Incorretas
1. No Google Apps Script, vá em **"Configurações do projeto"** (⚙️)
2. Role até "Permissões"
3. Clique em "Mostrar arquivo de manifesto do Apps Script"
4. Verifique se tem estas permissões:
```json
{
  "oauthScopes": [
    "https://www.googleapis.com/auth/spreadsheets",
    "https://www.googleapis.com/auth/script.external_request"
  ]
}
```

#### Causa B: Planilha com Proteção
1. Na planilha, clique com botão direito na aba "Página1"
2. Vá em "Proteger planilha e intervalos"
3. **Remova todas as proteções**

#### Causa C: Conta Google Diferente
1. Verifique se você está logado na mesma conta Google em:
   - Google Sheets (planilha)
   - Google Apps Script (código)
   - Navegador (teste)

---

## 📊 **CHECKLIST DE VERIFICAÇÃO FINAL**

Antes de pedir ajuda, confirme:

- [ ] ID da planilha está correto no Código.gs
- [ ] Aba "Página1" existe na planilha
- [ ] Google Apps Script foi reimplantado
- [ ] "Quem tem acesso" está como "Qualquer pessoa"
- [ ] Executei a função `testarGravacao()` e li os logs
- [ ] Testei a URL manualmente no navegador
- [ ] Não há proteções na aba "Página1"
- [ ] Estou logado na mesma conta Google em tudo

---

## 🎯 **SOLUÇÃO MAIS COMUM (90% dos casos)**

O problema geralmente é:
1. **ID da planilha incorreto** no Código.gs
2. **Script não reimplantado** após alterações
3. **Permissões incorretas** ("Qualquer pessoa" não selecionado)

**Refaça os Passos 1, 4 e 6** com atenção!

---

## 📞 **Reportar Problema**

Se mesmo após seguir todos os passos o problema persistir, envie:

1. ✅ Screenshot dos logs da função `testarGravacao()`
2. ✅ ID da planilha (da URL)
3. ✅ ID da planilha no Código.gs
4. ✅ Nome das abas da planilha
5. ✅ O que aparece ao testar URL no navegador
6. ✅ Screenshot das configurações de implantação

---

## ✅ **APÓS RESOLVER**

Quando funcionar:
1. **Substitua** o Código_Debug.gs pelo Código.gs original
2. **Reimplante** novamente
3. **Teste** o ESP32

**Boa sorte!** 🚀
