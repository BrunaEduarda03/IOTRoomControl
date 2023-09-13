#include <IRremote.h>

#ifndef ControleAR_H
#define ControleAR_H

/* Códigos infravermelhos necessários para controlar o ar condicionado ELGIN
 Criado em 15/03/2017
 Autor: Artur Freitas */


void TurnAirConditionerON(IRsend*);
void TurnAirConditionerOFF(IRsend*);

void SetAirConditionerTemp(int, IRsend*);





#endif
