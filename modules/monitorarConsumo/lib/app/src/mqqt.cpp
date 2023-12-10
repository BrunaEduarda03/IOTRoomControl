/**
 * @file mqqt.h
 * @author William Henrique A. Martins (william.martins@ee.ufcg.edu.br)
 *          <seu nome> <seu email>
 * @brief Interface MQQT para padronização
 * @version 0.1
 * @date 2023-10-06
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include "mqqt.h"

#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient wifi_client;
PubSubClient mqqt_client(wifi_client);

void mqqt_callback(char* topic, byte* payload, unsigned int length);

bool wifi_init() {
    int attempting = 0;
    // realiza a conexão com o wifi
    WiFi.begin(ssid, pswd);
    // verifica o status da conexão, caso falhe 10 encerra a tentativa
    while(WiFi.status() != WL_CONNECTED) {
        delay(100);
        if(attempting++ < 20) continue;
        return false;
    }
    return true;
}

bool mqqt_init() {
    mqqt_client.setServer(broker, port);
    mqqt_client.setCallback(mqqt_callback);
    if(!mqqt_client.connect("LIEC_Dev01"));
        return false;
    return true;
}

/**
 * @brief Processa as mensagens recebidas pelo cliente dos tópicos
 *  em que foi feito uma subscrição
 * @param topic 
 * @param payload 
 * @param length 
 */
void mqqt_callback(char* topic, byte* payload, unsigned int length)
{
    // converte os bytes recebidos para uma string
    String message(reinterpret_cast<char*>(payload), length);
    Serial.println("Recieved");
    // tratamento de dados
    // ...
}

PubSubClient* mqqt() {
    return &mqqt_client;
}