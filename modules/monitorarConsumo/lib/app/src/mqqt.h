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

#ifndef MQQT_H
#define MQQT_H

#include <PubSubClient.h>

static const char* ssid = "LIEC_119";
static const char* pswd = "0987ABCDEF";

static const char* broker = "public.mqtthq.com";
static int port = 1883;

#define SERVER_ROOT "IOTRoom"               // endereço raíz do broker
#define CONCATENATE(a, b, sep) a sep b
#define TOPIC(x) CONCATENATE(SERVER_ROOT, x, "/")

bool mqqt_init();
bool wifi_init();
/**
 * @brief Obtêm a referência mútavel do client mqqt
 * 
 * @return const PubSubClient& 
 */
PubSubClient* mqqt();

#endif //!MQQT