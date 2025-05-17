#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

// Objeto do sensor BMP280
Adafruit_BMP280 bmp;

// Variáveis para armazenar os dados do sensor
float temperatura, pressao, altitude;

// Dados da rede Wi-Fi
const char* ssid = "iPhone";
const char* senha = "123456789";

// Criação do servidor web na porta 80
WebServer server(80);

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Iniciando ESP32...");

  // Inicialização do sensor BMP280
  if (!bmp.begin(0x76)) {
    Serial.println("❌ Sensor BMP280 não encontrado. Verifique as conexões!");
    while (1); // trava o programa se não encontrar o sensor
  }
  Serial.println("✅ Sensor BMP280 detectado.");

  // Conecta-se à rede Wi-Fi
  Serial.print("Conectando à rede: ");
  Serial.println(ssid);
  WiFi.begin(ssid, senha);

  // Aguarda conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n✅ Wi-Fi conectado!");
  Serial.print("Endereço IP atribuído: ");
  Serial.println(WiFi.localIP());

  // Define as rotas do servidor
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);
  
  // Inicia o servidor
  server.begin();
  Serial.println("✅ Servidor HTTP iniciado!");
}

void loop() {
  server.handleClient();
  delay(100); // reduz carga no processador
}

void handle_OnConnect() {
  // Lê os dados do sensor
  temperatura = bmp.readTemperature();
  pressao = bmp.readPressure() / 100.0F;  // Converte Pa para hPa
  altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);

  // Log no Serial Monitor
  Serial.println("Requisição recebida:");
  Serial.printf("Temperatura: %.2f °C\n", temperatura);
  Serial.printf("Pressão: %.2f hPa\n", pressao);
  Serial.printf("Altitude: %.2f m\n", altitude);
  Serial.println("___________\n");

  // Responde com a página HTML
  server.send(200, "text/html", SendHTML(temperatura, pressao, altitude));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Página não encontrada");
}

String SendHTML(float temperatura, float pressao, float altitude) {
  String html = "<!DOCTYPE html><html lang='pt-BR'>\n";
  html += "<head>\n";
  html += "<meta charset='UTF-8'>\n";
  html += "<meta name='viewport' content='width=device-width, initial-scale=1.0'>\n";
  html += "<meta http-equiv='refresh' content='3'>\n";
  html += "<title>ESP32 + BMP280</title>\n";
  html += "<style>\n";
  html += "body { font-family: Arial, sans-serif; background-color: #f0f8ff; margin: 0; padding: 0; }\n";
  html += "h1 { background-color: #007ACC; color: white; padding: 20px; margin: 0; }\n";
  html += ".container { padding: 30px; text-align: center; }\n";
  html += ".card { background-color: white; border-radius: 10px; padding: 20px; box-shadow: 0 4px 8px rgba(0,0,0,0.1); display: inline-block; }\n";
  html += "p { font-size: 22px; margin: 10px 0; }\n";
  html += "</style>\n";
  html += "</head><body>\n";
  html += "<h1>Leitura de dados utilizando sensor BMP280</h1>\n";
  html += "<div class='container'>\n";
  html += "<div class='card'>\n";
  html += "<p>🌡️ Temperatura: <strong>" + String(temperatura, 2) + " &deg;C</strong></p>\n";
  html += "<p>🔵 Pressão: <strong>" + String(pressao, 2) + " hPa</strong></p>\n";
  html += "<p>⛰️ Altitude estimada: <strong>" + String(altitude, 2) + " m</strong></p>\n";
  html += "</div>\n";
  html += "</div>\n";
  html += "</body></html>\n";
  return html;
}
