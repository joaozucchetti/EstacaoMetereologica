# 🌤️ Estação Meteorológica com ESP32 + BMP280

Este projeto implementa uma **estação meteorológica simples** utilizando um **ESP32** e o sensor **BMP280**. Os dados de temperatura, pressão atmosférica e altitude estimada são exibidos em tempo real através de um servidor web acessível na mesma rede Wi-Fi.

## Disciplina: Redes de Comunicação e Aplicações Distribuidas (iot)
## Acadêmicos
  - João Vitor Machado Zucchetti
  - Ana Cazarotto
---

## 📦 Componentes Utilizados

- ESP32
- Sensor BMP280 (conectado via I2C)
- Conexão Wi-Fi (rede local)
- Cabos jumper
- Fonte de alimentação para o ESP32

---

## ⚙️ Funcionalidades

- Conexão Wi-Fi com IP fixo
- Leitura contínua de temperatura, pressão e altitude
- Interface web simples e responsiva
- Atualização dos dados a cada requisição

---

## 🖥️ Interface Web

A página gerada pelo ESP32 exibe:

- 🌡️ **Temperatura (°C)**
- 🧭 **Pressão Atmosférica (hPa)**
- 🏔️ **Altitude Estimada (m)**

> Interface web simples, acessível via navegador no IP configurado (por padrão: `http://192.168.0.100`)

---

## 🔌 Conexões I2C

| BMP280 | ESP32                |
|--------|----------------------|
| VCC    | 3.3V                 |
| GND    | GND                  |
| SCL    | GPIO 22 (SCL padrão) |
| SDA    | GPIO 21 (SDA padrão) |

---

## 📡 Configuração de Rede

- **SSID:** `iPhone`  
- **Senha:** `123456789`  
- **IP Fixo:** `192.168.0.100`

> Você pode alterar essas informações diretamente no código fonte, se necessário.

---

## 🛠️ Bibliotecas Necessárias

Instale as seguintes bibliotecas na IDE Arduino:

- `WiFi.h`
- `WebServer.h`
- `Wire.h`
- `Adafruit Sensor`
- `Adafruit BMP280`

---

## 🧠 Código-fonte

O código realiza:

1. Conexão com a rede Wi-Fi
2. Inicialização do sensor BMP280
3. Criação de um servidor HTTP
4. Exibição dos dados meteorológicos em página HTML

Você pode encontrar o código completo no arquivo `main.ino` ou `sketch.ino`.

---

## 🚀 Como Usar

1. Abra o código na IDE Arduino
2. Conecte o ESP32 ao seu computador
3. Faça o upload do código
4. Conecte-se à mesma rede Wi-Fi configurada no ESP32
5. Acesse `http://192.168.0.100` no navegador
6. Veja os dados do BMP280 atualizados em tempo real

---

## 📷 Imagens (opcional)

Adicione aqui imagens do circuito montado ou capturas de tela da página web:

```html
<!-- Exemplo: -->
<!-- ![Interface Web](imagens/interface_web.png) -->
