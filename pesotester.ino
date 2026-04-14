#include "HX711.h"

#define DT 40
#define SCK 41

HX711 scale;

float factor_calibracion = 83500; // EJEMPLO

void setup() {
  Serial.begin(9600);
  scale.begin(DT, SCK);

  scale.set_scale(factor_calibracion);
  scale.tare();
}

void loop() {
  float masa = scale.get_units(10);

  Serial.print("Masa: ");
  Serial.print(masa);
  Serial.println(" kg");

  delay(1000);
}
