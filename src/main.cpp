
/**
 * @file main.h
 * @author William Henrique A. Martins (william.martins@ee.ufcg.edu.br)
 *         <adicionar aqui>
 * @brief 
 * @version 0.1
 * @date 2023-10-02
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <Arduino.h>
#include <macros.h>
#include <hello_world.h>

// para compilar o demo, modifique o MACRO no include/macros.h
#ifdef COMPILE_MAIN

void setup() {
  Serial.begin(115200);
  const char* text = hello_word();
  Serial.printf("%s", text);
}

void loop() {
  // put your main code here, to run repeatedly:
}

#endif