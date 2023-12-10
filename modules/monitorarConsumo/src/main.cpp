
/**
 * @file main.h
 * @author William Henrique A. Martins (william.martins@ee.ufcg.edu.br)
 * @brief 
 * @version 0.1
 * @date 2023-10-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include <macros.h>

// para compilar o demo, modifique o MACRO no include/macros.h

#include <macros.h>
#ifdef COMPILE_MAIN

#include <Arduino.h>

// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>

#include "SSD1306Wire.h"
#include "mqqt.h"

// para compilar o demo, modifique o MACRO no include/macros.h


#define SDA 21
#define SCL 22
SSD1306Wire display(0x3c, SDA, SCL);
static PubSubClient *mqqt_client;

#define ADC_WIDTH 12                
#define ADC_COUNT (1<<ADC_WIDTH)    
#define SCT_NPOINTS 1000
#define SCT_SAMPLING_RATE 5000                       
#define SCT_MS_DELAY (int)(SCT_NPOINTS / SCT_SAMPLING_RATE)  
#define ADC_CALC(x) (3.3f/ADC_COUNT)*x                    // Fator de conversão
#define SCT_BURDEN 62                                     // Resistor de carga
#define SCT_RATIO  1860                                   // Relação de transformação de corrente
#define SCT_V2A    SCT_RATIO/SCT_BURDEN                   // Inclinação da reta i1(v2)
#define SCT_VRMS 223                                      // Tensão da rede local

#define SCT_PIN 33 // adc

void sct_read_rms(void* param) {

  // configuração do ADC
  analogSetWidth(ADC_WIDTH);
  analogSetAttenuation(ADC_11db);

  int g_pin = SCT_PIN;
  // mean
  double g_mean = ADC_COUNT >> 1;
  
  char rms_str[8], power_str[8];
  char rms_display[30], power_display[30];
  
  double sum_sq = 0;

  float alpha = 0.10;

  for(;;) {
    sum_sq = 0;
    // sampling loop
    long start = micros();
    for(int i = 0; i < SCT_NPOINTS; i++) {
      // reads signal + dc level
      int dc = analogRead(g_pin);
      // updates mean online
      g_mean = (1-alpha)*g_mean + alpha*dc;
      // g_mean = (g_mean + (dc-g_mean)/ADC_COUNT);
      // remove dc level
      int ac = dc - g_mean;
      // compute squares
      sum_sq  += ac * ac;
      // Serial.print(String(ADC_CALC(dc)) + ",");
      // vTaskDelay(1 / portTICK_PERIOD_MS);
    }
    long total = micros() - start;
    Serial.println("Offset: " + String(ADC_CALC(g_mean)));
    // Serial.println(" ");
    // vTaskDelay(100);
    
    // compute root mean square of SCT reading
    double v2_rms = sqrt(sum_sq / SCT_NPOINTS);
    v2_rms = v2_rms * (3.3 / ADC_COUNT);
    
    // expected current input
    double i1 = v2_rms * SCT_V2A;
    
    sprintf(rms_str, "%2.2lf", i1);
    sprintf(power_str, "%2.2lf", i1);
    sprintf(rms_display,   "Irms: %2.2lf A | rms: %2.2lf", i1, i1 / 30.f);
    sprintf(power_display, "Power: %2.2lf W", i1*SCT_VRMS);
    
    display.clear(); 
    display.display();
    display.drawString(0, 0, rms_display);
    display.drawString(0, 18, power_display);
    display.display();
    Serial.println(String(rms_display) + " | " + String(power_display) + " | avg time " \
      + String(1.0e-3f*total/SCT_SAMPLING_RATE) + "ms");

    if(mqqt_client != NULL) {
      bool ret_pub1 = mqqt()->publish(TOPIC("corrente"), rms_str);
      bool ret_pub2 = mqqt()->publish(TOPIC("potencia"), power_str);
    }
    
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  
  DEBUG_ONLY( Serial.begin(115200) );
  DEBUG_ONLY( Serial.println("Sampling interval: " + String(SCT_MS_DELAY)) );
  DEBUG_ONLY( Serial.println("ADC Count: " + String(ADC_COUNT)) );

  // Inicializa o WiFi e o MQQT
  if(!wifi_init()) {
    Serial.println("WiFi not connected");
  } else { 
    if(!mqqt_init()) {
      Serial.println("MQQT not connected");
      mqqt_client = NULL;
    } else                  // MQQT inicializado
      mqqt_client = mqqt(); // recupera o endereço do cliente MQQT
  }
  
  display.init();
  display.setContrast(255);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.clear();
  display.display();
  display.flipScreenVertically(); 
  display.drawString(0, 0, "Initialized");
  display.display();

  xTaskCreate(sct_read_rms, "SCT reading", 2*1024, NULL, 40, NULL);
}

void loop() {
  
  if(!mqqt_client->connected()) {
    DEBUG_ONLY( Serial.println("Erro: MQQT not connected") );
    mqqt_client->connect("LIEC_Dev01");
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }

  mqqt_client->loop();

  int analog = analogRead(SCT_PIN);
  Serial.println("ADC value: " + String(ADC_CALC(analog)) + " | " + String(analog) );
  vTaskDelay(1900 / portTICK_PERIOD_MS);
  
  vTaskDelay(100 / portTICK_PERIOD_MS);
}

#endif