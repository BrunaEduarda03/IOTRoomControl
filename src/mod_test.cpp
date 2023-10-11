/**
 * @file mod_test.h
 * @author William Henrique A. Martins (william.martins@ee.ufcg.edu.br)
 *         <adicionar aqui>
 * @brief
 * @version 0.1
 * @date 2023-10-02
 * 
 * @copyright Copyright (c) 2023
 * 
**/

#include <macros.h>
#ifdef COMPILE_TEST

#include <Arduino.h>
#include <EmonLib.h>

// #include <Arduino_FreeRTOS.h>
// #include <semphr.h>

#include "SSD1306Wire.h"
#include "mqqt.h"

// para compilar o demo, modifique o MACRO no include/macros.h
#define SDA 21
#define SCL 22
#define SCT_PIN 33 // vp, read only, adc

#define VRMS 223  // Tensão da rede local

SSD1306Wire display(0x3c, SDA, SCL);
EnergyMonitor sct;
static PubSubClient *mqqt_client;

void task_sct_read(void *param) {
  const double Vrms = VOLTAGE;
  analogSetWidth(12);
  analogSetAttenuation(ADC_11db);
  for(;;) {
    // ler corrente
    long start = micros();
    double Irms = sct.calcIrms(180);
    double avg_time = (1.0e-3f)*(micros() - start)/180;
    // converte valor lido para str
    char message[10], display_message[30];
    sprintf(message, "%2.2f", Irms);
    // dtostrf(Irms, 3, 4, message);
    display.clear();
    display.display();
    sprintf(display_message, "Amp: %s A", message);
    display.drawString(0, 0, display_message);
    sprintf(display_message, "Watt: %2.2f", Irms*VRMS);
    display.drawString(0, 18, display_message);
    display.display();
    bool ret_pub = mqqt()->publish(TOPIC("corrente"), message);
    // if(ret_pub)
    //   Serial.println("Published");		       // Irms
    // else
    //   Serial.println("Not Published");
    Serial.println("Irms " + String(Irms) + " | Power" + String(Irms*VRMS) + " | avg time " \
      + String(avg_time) + "ms");
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
  return;
}

#define ADC_WIDTH 12                
#define ADC_COUNT (1<<ADC_WIDTH)    
#define SCT_SAMPLING_RATE 10000                       
#define SCT_MS_DELAY (int)(1000.0f / SCT_SAMPLING_RATE)  
#define ADC_CALC(x) (3.3f/ADC_COUNT)*x

void sct_read_rms(void* param) {

  analogSetWidth(ADC_WIDTH);
  
  analogSetAttenuation(ADC_11db);

  int g_pin = SCT_PIN;
  // mean
  double g_mean = ADC_COUNT >> 1;
  
  char rms_str[8], power_str[8];
  char rms_display[30], power_display[30];
  
  double sum_sq = 0;

  float alpha = 0.1;

  for(;;) {
    sum_sq = 0;
    // sampling loop
    long start = micros();
    for(int i = 0; i < SCT_SAMPLING_RATE; i++) {
      // reads signal + dc level
      int dc = analogRead(g_pin);
      // updates mean online
      g_mean = (1-alpha)*g_mean + alpha*dc;
      // remove dc level
      int ac = dc - g_mean;
      // compute squares
      sum_sq  += ac * ac;
      // Serial.print(String(ADC_CALC(dc)) + ",");
      vTaskDelay(SCT_MS_DELAY / portTICK_PERIOD_MS);
    }
    long total = micros() - start;
    Serial.println("Offset: " + String(ADC_CALC(g_mean)));
    // Serial.println(" ");
    // vTaskDelay(100);
    double rms = sqrt(sum_sq / SCT_SAMPLING_RATE);
    double rms_conv = rms * (3.3 / ADC_COUNT);
    
    rms_conv = rms_conv * 30;

    sprintf(rms_str, "%2.2lf", rms);
    sprintf(power_str, "%2.2lf", rms);
    
    sprintf(rms_display,   "Irms: %2.2lf A | rms: %2.2lf", rms_conv, rms_conv / 30.f);
    sprintf(power_display, "Power: %2.2lf W", rms_conv*VRMS);
    
    display.clear(); 
    display.display();
    display.drawString(0, 0, rms_display);
    display.drawString(0, 18, power_display);
    display.display();
    Serial.println(String(rms_display) + " | " + String(power_display) + " | avg time " \
      + String(1.0e-3f*total/SCT_SAMPLING_RATE) + "ms");
    bool ret_pub1 = mqqt()->publish(TOPIC("corrente"), rms_str);
    bool ret_pub2 = mqqt()->publish(TOPIC("potencia"), power_str);
    vTaskDelay(1000 / portTICK_PERIOD_MS);
  }
}

void setup() {
  
  Serial.begin(115200);
  Serial.println("Sampling interval: " + String(SCT_MS_DELAY));
  Serial.println("ADC Count: " + String(ADC_COUNT));

  if(!wifi_init()) {
    Serial.println("WiFi not connected");
  } else if(!mqqt_init()) {
    Serial.println("MQQT not connected");
  }
  mqqt_client = mqqt();
  // Resistência interna medida
  double sct_burden = 39.3; // Ohm
  // calibração: relação espiras / resistor de carga
  double sct_cal = 1179 / sct_burden ; 
  // double sct_cal = 1800 / 62 ; 
  sct.current(SCT_PIN, 1);

  display.init();
  display.setContrast(255);
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.display();
  display.flipScreenVertically(); 
  display.drawString(0, 0, "Initialized");
  display.display();

  // xTaskCreate(task_sct_read, "SCT reading", 2*1024, NULL, 10, NULL);
  xTaskCreate(sct_read_rms, "SCT reading", 2*1024, NULL, 40, NULL);
}

void loop() {
  
  if(!mqqt_client->connected()) {
    Serial.println("Erro: MQQT not connected");
    mqqt_client->connect("LIEC_Dev01");
    vTaskDelay(100 / portTICK_PERIOD_MS);
  }

  mqqt_client->loop();

  // int analog = analogRead(SCT_PIN);
  // Serial.println("ADC value: " + String(ADC_CALC(analog)) + " | " + String(analog) );
  // vTaskDelay(1900 / portTICK_PERIOD_MS);
  // put your main code here, to run repeatedly:
  
  vTaskDelay(100 / portTICK_PERIOD_MS);
}

#endif // !COMPILE_TEST