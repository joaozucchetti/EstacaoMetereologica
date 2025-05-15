#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

#define SEALEVELPRESSURE_HPA (1013.25)

Adafruit_BMP280 bmp;

float temperatura, pressao, altitude;

// conexao wifi
const char* ssid = "Ana";
const char* senha = "13579000";

// ips fixos
WebServer server(80);
IPAddress local_IP(192, 168, 0, 100);
IPAddress gateway(192, 168, 0, 1);
IPAddress subnet(255, 255, 255, 0);
IPAddress primaryDNS(8, 8, 8, 8);
IPAddress secondaryDNS(8, 8, 4, 4);

void setup() {
  Serial.begin(115200);
  delay(100);
  Serial.println("Iniciando ESP32...");

  // procurar o sensor na porta 
  if (!bmp.begin(0x76)) {
    Serial.println("❌ Sensor BMP280 não encontrado. Verifique as conexões!");
    while (1);
  }
  Serial.println("✅ Sensor BMP280 detectado.");

  // config da rede
  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
    Serial.println("❌ Falha ao configurar IP fixo!");
  } else {
    Serial.println("✅ IP fixo configurado.");
  }

  Serial.print("Conectando à rede: ");
  Serial.println(ssid);
  WiFi.begin(ssid, senha);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\n✅ Wi-Fi conectado!");
  Serial.print("Endereço IP: ");
  Serial.println(WiFi.localIP());

  // rotas servidor web
  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("✅ Servidor HTTP iniciado!");
}

void loop() {
  server.handleClient();
}


void handle_OnConnect() {
  temperatura = bmp.readTemperature();
  pressao = bmp.readPressure() / 100.0F;
  altitude = bmp.readAltitude(SEALEVELPRESSURE_HPA);

  Serial.println("Requisição recebida:");
  Serial.printf("Temperatura: %.2f °C\n", temperatura);
  Serial.printf("Pressão: %.2f hPa\n", pressao);
  Serial.printf("Altitude: %.2f m\n", altitude);
  server.send(200, "text/html", SendHTML(temperatura, pressao, altitude));
}

void handle_NotFound() {
  server.send(404, "text/plain", "Página não encontrada");
}

// html da pag 
String SendHTML(float temperatura, float pressao, float altitude) {
  String ptr = "<!DOCTYPE html><html>\n";
  ptr += "<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0\">\n";
  ptr += "<title>ESP32 + BMP280</title>\n";
  ptr += "<style>body{font-family:Helvetica;text-align:center;margin-top:50px;} p{font-size:24px;}</style>\n";
  ptr += "</head><body>\n";
  ptr += "<h1>Leituras do BMP280</h1>\n";
  ptr += "<p>Temperatura: " + String(temperatura) + " &deg;C</p>\n";
  ptr += "<p>Pressão: " + String(pressao) + " hPa</p>\n";
  ptr += "<p>Altitude estimada: " + String(altitude) + " m</p>\n";
  ptr += "</body></html>\n";
  return ptr;
}