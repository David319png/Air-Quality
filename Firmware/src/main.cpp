// 1. PEGA AQUÍ LAS 3 LÍNEAS DE "DEVICE INFO" DE TU DISPOSITIVO EN BLYNK:
#define BLYNK_TEMPLATE_ID   "TMPL2Zd_eksBi"
#define BLYNK_TEMPLATE_NAME "Estacion de gases"
#define BLYNK_AUTH_TOKEN    "1gXlH_cqu5102T9ER6Cjl0QqmtWwBT8D"

#define BLYNK_PRINT Serial

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

// 2. CREDENCIALES DE TU RED WI-FI (2.4 GHz):
char ssid[] = "POCO_X4";
char pass[] = "david2341";

// 3. PINES ADC1 COMPATIBLES CON WI-FI EN ESP32-S3:
const int PIN_MQ135 = 10; // Calidad de aire / vapores
const int PIN_MQ2   = 9;  // Gas inflamable / humo

BlynkTimer timer;

int leerPromedioADC(int pin) {
  long suma = 0;
  for (int i = 0; i < 10; i++) {
    suma += analogRead(pin);
    delay(5);
  }
  return suma / 10;
}

void enviarLecturasBlynk() {
  int adc135 = leerPromedioADC(PIN_MQ135);
  int adc2   = leerPromedioADC(PIN_MQ2);

  String est135 = (adc135 < 1350) ? "Limpio" : (adc135 < 2100) ? "Moderado" : "ALERTA";
  String est2   = (adc2 < 2850)   ? "Limpio" : (adc2 < 3150)   ? "Moderado" : "ALERTA";
  String resumen = "Aire: " + est135 + " | Gas: " + est2;

// ORDEN EXACTO SEGÚN TUS DATASTREAMS EN BLYNK:
  Blynk.virtualWrite(V0, adc135); // MQ135 (Entero)
  Blynk.virtualWrite(V1, est135); // MQ_135 Estado (Cadena)
  Blynk.virtualWrite(V2, adc2);   // MQ2 (Entero)
  Blynk.virtualWrite(V3, est2);   // MQ_2 Estado (Cadena)

  Serial.printf("MQ135 (Pin 10): %d [%s] | MQ2 (Pin 9): %d [%s]\n",
                adc135, est135.c_str(), adc2, est2.c_str());
}

void setup() {
  Serial.begin(115200);
  delay(1500);

  analogReadResolution(12);
  analogSetPinAttenuation(PIN_MQ135, ADC_6db);
  analogSetPinAttenuation(PIN_MQ2,   ADC_6db);

  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);

  timer.setInterval(2000L, enviarLecturasBlynk);
}

void loop() {
  Blynk.run();
  timer.run();
}