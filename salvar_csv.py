import requests
from bs4 import BeautifulSoup
import csv
from datetime import datetime
import os
import sys

# configs
ESP32_URL  = "http://172.20.10.11"
CSV_PATH   = "/tmp/dados_sensor.csv"
CSV_HEADER = ['Timestamp', 'Temperatura (C°)', 'Pressão (hPa)', 'Altitude (m)']


def obter_dados_esp32(url):
    try:
        print(f"🌐 Conectando ao ESP32 em {url}...")
        response = requests.get(url, timeout=5)
        response.raise_for_status()
    except requests.RequestException as e:
        raise ConnectionError(f"Erro na conexão com o ESP32: {e}")

    soup     = BeautifulSoup(response.text, 'html.parser')
    leituras = soup.find_all('p')

    if len(leituras) < 3:
        raise ValueError("HTML retornado não contém dados esperados (3 leituras).")
    try:
        temperatura = leituras[0].text.split(":")[1].strip().split()[0]
        pressao     = leituras[1].text.split(":")[1].strip().split()[0]
        altitude    = leituras[2].text.split(":")[1].strip().split()[0]
    except (IndexError, ValueError) as e:
        raise ValueError("Erro ao extrair valores das leituras HTML: " + str(e))
    return temperatura, pressao, altitude


def salvar_csv(caminho, dados):
    os.makedirs(os.path.dirname(caminho), exist_ok=True)

    novo_arquivo = not os.path.exists(caminho)
    with open(caminho, 'a', newline='', encoding='utf-8') as arquivo:
        escritor = csv.writer(arquivo)
        if novo_arquivo:
            escritor.writerow(CSV_HEADER)
            escritor.writerow([datetime.now().strftime("%Y-%m-%d %H:%M:%S"), *dados])


def main():
    try:
        temperatura, pressao, altitude = obter_dados_esp32(ESP32_URL)
        salvar_csv(CSV_PATH, [temperatura, pressao, altitude])

        print("Dados coletados e salvos com sucesso!")
        print(f"Temperatura: {temperatura} °C")
        print(f"Pressão: {pressao} hPa")
        print(f"Altitude: {altitude} m")
        print(f"Arquivo salvo em: {CSV_PATH}")

    except Exception as erro:
        print(f"\nOcorreu um erro: {erro}")
        sys.exit(1)


if __name__ == "__main__":
    main()
