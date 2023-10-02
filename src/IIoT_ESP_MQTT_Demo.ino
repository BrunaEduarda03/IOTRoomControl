#include <macros.h>
// para compilar o demo, modifique o MACRO no include/macros.h
#ifdef COMPILE_DEMO

//####################################################################################
// Universidade Federal de Campina Grande
// Centro de Engenharia Elétrica e Informática
// Graduação em Engenharia Elétrica
//
// Professor : Rafael Bezerra Correia Lima
// Engenheiro: Christian Charles Dias
//
// Disciplina: TEEE - Industrial Internet of Things - 2017.2
//
// Descrição: Utilização do ESP8266 com protocolo MQTT
//
//####################################################################################

//************************************************************************************
// Bibliotecas
#include <Wire.h>  // Only needed for Arduino 1.6.5 and earlier
#include "SSD1306Wire.h" // legacy include: `#include "SSD1306.h"`
#include <WiFi.h>
#include <PubSubClient.h>   // Documentação https://pubsubclient.knolleary.net/api.html
#include <OneWire.h>
#include <DallasTemperature.h>
#include <IRremote.h>
#include <driver/adc.h>
#include <driver/gpio.h>
#include <esp_adc_cal.h>
#include "ControleAr.h"
#include "DisplayMethods.h"

//************************************************************************************
// Declarações dos pinos
#define MIN_CAPACITANCE 120
// Data wire is connected to GPIO15
#define TEMPERATURE_ONE_WIRE 27

#define SEND_IR_PIN 26
#define PRESENCE_SENSOR_PIN 25

#define ReleUpDown 4
#define ReleOnOff 0
#define LightSensorPin 34
#define TemperatureSensorPin 27
#define V_REF 1100

//************************************************************************************
// Configuração da rede
const char* SSID = "LIEC_Wireless2";                // Nome da rede Wi-Fi
const char* PASSWORD = "0987ABCDEF";                // senha da rede Wi-Fi


//************************************************************************************
// Configuração para MQTT
const char* BROKER_MQTT = "broker.hivemq.com";      // IP/host do broker
//const char* BROKER_MQTT = "150.165.52.188";         // IP/host do broker
int BROKER_PORT = 1883;                             // Porta do broker

const char* CLIENT_ID = "LIEC_Sala_119_IIoT_01";             // ID do client único para cada cliente conectado ao BROKER
const char* TOPIC_PUBLISH_Temp = "LIEC/Sala_119/Temperature";     // Tópicos para PUBLISH
const char* TOPIC_PUBLISH_Light = "LIEC/Sala_119/Light";     // Tópicos para PUBLISH
const char* TOPIC_PUBLISH_Presence = "LIEC/Sala_119/Presence";     // Tópicos para PUBLISH
const char* TOPIC_SUBSCRIBE_Curtain = "LIEC/Sala_119/Curtain";  // Tópicos para SUBSCRIBE
const char* TOPIC_SUBSCRIBE_AirConditioner = "LIEC/Sala_119/Air_Conditioner";  // Tópicos para SUBSCRIBE


WiFiClient espClient;                       // Instancia objeto espClient
PubSubClient MQTT(espClient);               // instancia objeto mqtt


//************************************************************************************
// Variáveis GLOBAIS (are devil)
int delayTime = 1000;                       // Publica a cada x ms
int lastTime = 0;                          // Tempo do envio da última mensagem
float light = 0;
float temperature = 0;
float current = 0;

char mqtt_message[50];
String msg;
bool passSomeone = false;
bool someoneTouch  = false;

SSD1306Wire  display(0x3c, 21, 22);

// Setup a oneWire instance to communicate with a OneWire device
OneWire oneWire(TEMPERATURE_ONE_WIRE);
// Pass our oneWire reference to Dallas Temperature sensor
DallasTemperature sensors(&oneWire);

DeviceAddress temperatureSensor = { 0x28, 0x3E, 0x2F, 0x74, 0x06, 0x00, 0x00, 0x00 }; // Address found using "GetSensorAddress.ino"

IRsend irsend(SEND_IR_PIN); // The IRemote lib doesn't suport the esp32 as a sender, but Andreas Spiess make a adaptation on the lib and works... using "Definitive-Guide-to-IR"
// For more detail: https://www.youtube.com/watch?v=gADIb1Xw8PE

esp_adc_cal_characteristics_t characteristics11DB;
//************************************************************************************
// Protótipos de funções
void initWiFi();                            // Se conecta a rede Wi-Fi
void initMQTT();                            // Inicializa configurações do MQTT
typedef void (*Demo)(void);

int demoMode = 0;
int counter = 2;

void ShowLIECLogo() {
  display.drawXbm(0, 0, LIEC_width, LIEC_height, LIEC_bits);
}

void ShowTemperature () {
  display.setTextAlignment(TEXT_ALIGN_LEFT);
  display.setFont(ArialMT_Plain_16);
  display.drawString(0, 0, "Temperatura:");

  display.setFont(ArialMT_Plain_24);
  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(128, 33, String(temperature) + " ºC");

}

Demo demos[] = {ShowLIECLogo, ShowTemperature};



//************************************************************************************
// setup
void setup()
{
  Serial.begin(115200);                     // Inicializa UART
  initWiFi();                               // Se conecta a rede Wi-Fi
  initMQTT();                               // Inicializa configurações do MQTT

  pinMode(PRESENCE_SENSOR_PIN, INPUT);
  pinMode(35, INPUT);

  pinMode(ReleOnOff, OUTPUT);
  pinMode(ReleUpDown, OUTPUT);

  digitalWrite(ReleOnOff, HIGH);  // The relay module used in this project is : LOW -> ON && HIGH -> OFF
  digitalWrite(ReleUpDown, HIGH);

  sensors.begin(); // Inicialize all temperature sensores in the wire

  // Initialising the UI will init the display too.
  display.init();
  display.flipScreenVertically();
  display.setFont(ArialMT_Plain_10);

  // Calculate ADC characteristics i.e. gain and offset factors
  esp_adc_cal_get_characteristics(V_REF, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, &characteristics11DB);
}



//************************************************************************************
// Loop principal
void loop()
{
  if (!MQTT.connected())
  {
    reconnectMQTT();                          // Reconecta ao Broker
  }

  reconnectWiFi();                            // Reconecta caso necessário
  MQTT.loop();                                // Deve ser chamado regularmente. Tratamento de mensagens recebidas

  if (!passSomeone) {
    passSomeone = (digitalRead(PRESENCE_SENSOR_PIN) == HIGH); // See if someone pass
  }

  if (!someoneTouch) {
    if (touchRead(T3) > MIN_CAPACITANCE) {
      someoneTouch = true;
    }

  }
  
  // Publica mensagem a cada delayTime
  if (millis() - lastTime > delayTime)
  {
    //SetAirConditionerTemp(24, &irsend);
    
    sensors.requestTemperatures(); // Request the temperature of the sensores
    temperature = sensors.getTempC(temperatureSensor); // Gets the response of the sensor of interest
    
    

    light = adc1_to_voltage(ADC1_CHANNEL_6, &characteristics11DB); // FALTA FAZER, AINDA VAI DEPENDER DE COMO SERÁ COLOCADO O SENSOR DE LUMINOSIDADE
    current = adc1_to_voltage(ADC1_CHANNEL_7, &characteristics11DB);
    
    // Publish only if someone pass
    if (passSomeone) {
      msg = "Movimento";
    } else {
      msg = "Ocioso";
    }
    passSomeone = false;

    if (someoneTouch) {
      demoMode++;
      if (demoMode == counter) {
        demoMode = 0;
      }
    }
    someoneTouch = false;
    ShowInDisplay();
    
    msg.toCharArray(mqtt_message, sizeof(mqtt_message));  // Converte para array de char
    MQTT.publish(TOPIC_PUBLISH_Presence, mqtt_message);


    // Publish the temperature measure by the DS18D20
    msg = String(temperature);//temperature
    msg.toCharArray(mqtt_message, sizeof(mqtt_message));  // Converte para array de char
    MQTT.publish(TOPIC_PUBLISH_Temp, mqtt_message);

    // Publish how bright is the room
    msg = String(light);
    msg.toCharArray(mqtt_message, sizeof(mqtt_message));  // Converte para array de char
    MQTT.publish(TOPIC_PUBLISH_Light, mqtt_message);

    lastTime = millis(); // Save the last time that the loop finished
  }
}



//************************************************************************************
// Função para inicializa e se conectar a rede Wi-Fi
void initWiFi()
{
  delay(10);
  Serial.println("Conectando-se em: " + String(SSID));
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }

  Serial.println();
  Serial.print("Conectado na Rede " + String(SSID) + " | IP => ");
  Serial.println(WiFi.localIP());
}


//************************************************************************************
// Funcão para inicializar MQTT
void initMQTT()
{
  MQTT.setServer(BROKER_MQTT, BROKER_PORT);
  MQTT.setCallback(mqtt_callback);
}


//************************************************************************************
// Função que recebe as mensagens publicadas
void mqtt_callback(char* topic, byte* payload, unsigned int length)
{
  String message;
  for (int i = 0; i < length; i++)
  {
    char c = (char)payload[i];
    message += c;
  }
  message.toUpperCase();
  if (strcmp(topic, TOPIC_SUBSCRIBE_Curtain) == 0) {
    if (message == "DOWN") {
      digitalWrite(ReleUpDown, LOW);
      digitalWrite(ReleOnOff, LOW);
    }
    else if (message == "UP") {
      digitalWrite(ReleUpDown, HIGH);
      digitalWrite(ReleOnOff, LOW);
    }
    else {
      digitalWrite(ReleUpDown, HIGH);
      digitalWrite(ReleOnOff, HIGH);
    }
  }
  else if (strcmp(topic, TOPIC_SUBSCRIBE_AirConditioner) == 0) {

    if (message == "OFF") {
      TurnAirConditionerOFF(&irsend);
    }
    else if (message == "ON") {
      TurnAirConditionerON(&irsend);
    }
    else {

      int temp = message.toInt();
      SetAirConditionerTemp(temp, &irsend);
    }
  }

}


//************************************************************************************
// Função para se reconectar ao Broker
void reconnectMQTT()
{
  while (!MQTT.connected())
  {
    Serial.println("Tentando se conectar ao Broker MQTT: " + String(BROKER_MQTT));

    if (MQTT.connect(CLIENT_ID))
    {
      Serial.println("Conectado");
      MQTT.subscribe(TOPIC_SUBSCRIBE_Curtain);
      MQTT.subscribe(TOPIC_SUBSCRIBE_AirConditioner);
    }
    else
    {
      Serial.println("Falha ao Reconectar");
      Serial.println("Tentando se reconectar em 2 segundos");
      delay(2000);
    }
  }
}


//************************************************************************************
// Função para se reconectar a rede Wi-Fi
void reconnectWiFi()
{
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
}

//************************************************************************************
// Função para mostrar mensagem no display

void ShowInDisplay() {
  display.clear();

  demos[demoMode]();

  display.setTextAlignment(TEXT_ALIGN_RIGHT);
  display.drawString(10, 128, String(millis()));
  // write the buffer to the display
  display.display();
}

#endif