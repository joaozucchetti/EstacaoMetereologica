🌤️ Estação Meteorológica com ESP32 + BMP280
Este projeto implementa uma estação meteorológica simples utilizando um ESP32 e o sensor BMP280. Os dados de temperatura, pressão atmosférica e altitude estimada são exibidos em tempo real através de um servidor web acessível na mesma rede Wi-Fi.

📦 Componentes Utilizados
ESP32
Sensor BMP280 (conectado via I2C)
Conexão Wi-Fi (rede local)
Cabos jumper
Fonte de alimentação para o ESP32

⚙️ Funcionalidades
Conexão Wi-Fi com IP fixo
Leitura contínua de temperatura, pressão e altitude
Interface web simples e responsiva
Atualização automática dos dados a cada requisição

🖥️ Interface Web
A página gerada pelo ESP32 exibe:

🌡️ Temperatura (°C)

🧭 Pressão Atmosférica (hPa)

🏔️ Altitude Estimada (m)

Interface web simples, acessível via navegador no IP configurado (por padrão: http://192.168.0.100).

🔌 Conexões I2C
BMP280	ESP32
VCC	3.3V
GND	GND
SCL	GPIO 22 (SCL padrão)
SDA	GPIO 21 (SDA padrão)

📡 Configuração de Rede
SSID: iPhone
Senha: 123456789
IP Fixo: 192.168.0.100
Você pode alterar essas informações diretamente no código fonte, se necessário.

🛠️ Bibliotecas Necessárias
Instale as seguintes bibliotecas na IDE Arduino:
WiFi.h
WebServer.h
Wire.h
Adafruit Sensor
Adafruit BMP280

🧠 Código-fonte
O código realiza:
Conexão com a rede Wi-Fi
Inicialização do sensor BMP280
Criação de um servidor HTTP
Atualização dos dados via HTML
Você pode copiar o código completo no arquivo main.ino.

🚀 Como Usar
Carregue o código no ESP32 através da IDE Arduino.
Certifique-se de estar na mesma rede Wi-Fi do ESP32.
Acesse o IP http://192.168.0.100 em um navegador.
Visualize os dados atualizados.
