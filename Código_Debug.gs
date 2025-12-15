// ==========================================================
// VERSÃO COM DEBUG - USE PARA DIAGNOSTICAR PROBLEMAS
// ==========================================================

// ID DA PLANILHA - MARFIM BAHIA (ATUALIZADO)
const ID_PLANILHA = "1f2XTPxMZUQIDXEEYfxQSLyWRVQDnGs4sccT3FrdDcW4";

function getSS() {
  try {
    if (ID_PLANILHA && ID_PLANILHA !== "") {
      Logger.log("Tentando abrir planilha com ID: " + ID_PLANILHA);
      return SpreadsheetApp.openById(ID_PLANILHA);
    }
  } catch (e) {
    Logger.log("ERRO ao abrir pelo ID: " + e.message);
  }
  Logger.log("Usando planilha ativa");
  return SpreadsheetApp.getActiveSpreadsheet();
}

function doGet(e) {
  if (e && e.parameter && e.parameter.maquina) {
    return salvarDadosESP32(e);
  }
  return ContentService.createTextOutput("Sistema funcionando - Aguardando dados do ESP32");
}

function salvarDadosESP32(e) {
  var lock = LockService.getScriptLock();
  try {
    lock.waitLock(10000);
  } catch (e) {
    Logger.log("ERRO: Lock timeout");
    return ContentService.createTextOutput("BUSY");
  }

  try {
    var maquina = e.parameter.maquina;
    var evento = e.parameter.evento;
    var duracao = e.parameter.duracao;

    Logger.log("Recebido - Máquina: " + maquina + " | Evento: " + evento + " | Duração: " + duracao);

    // ============================================================
    // FILTRO: Bloquear registros de TESTE
    // ============================================================
    var maquinaUpper = String(maquina).toUpperCase();
    if (maquinaUpper.indexOf("TESTE") > -1) {
      Logger.log("⚠️ Registro de TESTE bloqueado: " + maquina);
      return ContentService.createTextOutput("OK");
    }
    // ============================================================

    var ss = getSS();
    if (!ss) {
      Logger.log("ERRO: Planilha não encontrada");
      return ContentService.createTextOutput("ERROR: PLANILHA");
    }

    Logger.log("Planilha aberta: " + ss.getName());

    var sheet = ss.getSheetByName("Página1");
    if (!sheet) {
      Logger.log("ERRO: Aba 'Página1' não encontrada");
      Logger.log("Abas disponíveis: " + ss.getSheets().map(s => s.getName()).join(", "));
      sheet = ss.getActiveSheet();
      Logger.log("Usando aba ativa: " + sheet.getName());
    }

    var dataAtual = new Date();
    var timezone = Session.getScriptTimeZone();
    var dataStr = Utilities.formatDate(dataAtual, timezone, "dd/MM/yyyy");
    var horaStr = Utilities.formatDate(dataAtual, timezone, "HH:mm:ss");

    Logger.log("Tentando gravar: [" + dataStr + ", " + horaStr + ", " + maquina + ", " + evento + ", " + duracao + "]");

    sheet.appendRow([dataStr, horaStr, maquina, evento, duracao]);

    Logger.log("✓ Dados gravados com sucesso!");

    return ContentService.createTextOutput("OK");

  } catch (error) {
    Logger.log("ERRO CRÍTICO: " + error.message);
    Logger.log("Stack: " + error.stack);
    return ContentService.createTextOutput("ERROR: " + error.message);
  } finally {
    lock.releaseLock();
  }
}

// FUNÇÃO DE TESTE - Execute esta função manualmente
function testarGravacao() {
  var e = {
    parameter: {
      maquina: "TESTE_MANUAL_FUNCAO",
      evento: "TEMPO PRODUZINDO",
      duracao: "123"
    }
  };

  var resultado = salvarDadosESP32(e);
  Logger.log("Resultado: " + resultado.getContent());

  // Verificar logs
  Logger.log("\n=== VERIFIQUE OS LOGS ACIMA ===");
  Logger.log("1. Verifique se o ID da planilha está correto");
  Logger.log("2. Verifique se a aba 'Página1' foi encontrada");
  Logger.log("3. Verifique se os dados foram gravados");
  Logger.log("4. Vá na planilha e veja se apareceu linha com TESTE_MANUAL_FUNCAO");
}
