#include "HX711.h"

#define DT 40
#define SCK 41

HX711 scale;

float factor_calibracion = 1;
float peso_conocido = 0;

void setup() {
  Serial.begin(9600);
  scale.begin(DT, SCK);

  Serial.println("=== CALIBRACION CELDA DE CARGA ===");
  Serial.println("Quita todo el peso...");
  delay(5000);

  scale.tare(); // poner en cero
  Serial.println("Cero ajustado.");

  Serial.println("\nColoca un peso conocido sobre la celda.");
  Serial.println("Luego escribe el valor en kg en el monitor serial:");
}

void loop() {

  // Espera a que el usuario escriba el peso
  if (Serial.available()) {

    peso_conocido = Serial.parseFloat();

    Serial.print("Peso ingresado: ");
    Serial.print(peso_conocido);
    Serial.println(" kg");

    delay(2000); // tiempo para estabilizar

    long lectura = scale.get_value(20); // lectura cruda promedio

    Serial.print("Lectura cruda: ");
    Serial.println(lectura);

    factor_calibracion = lectura / peso_conocido;

    Serial.print("Factor de calibracion: ");
    Serial.println(factor_calibracion);

    Serial.println("\nUsa este valor en tu codigo:");
    Serial.print("scale.set_scale(");
    Serial.print(factor_calibracion);
    Serial.println(");");

    Serial.println("\n--- Reinicia para repetir calibracion ---");

    while (1); // detiene el programa
  }
}
