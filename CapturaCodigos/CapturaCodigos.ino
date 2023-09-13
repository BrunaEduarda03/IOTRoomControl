/*
Author: AnalysIR
Revision: 1.0

This code is provided to overcome an issue with Arduino IR libraries
It allows you to capture raw timings for signals longer than 255 marks & spaces.
Typical use case is for long Air conditioner signals.

You can use the output to plug back into IRremote, to resend the signal.

This Software was written by AnalysIR.

Usage: Free to use, subject to conditions posted on blog below.
Please credit AnalysIR and provide a link to our website/blog, where possible.

Copyright AnalysIR 2014

Please refer to the blog posting for conditions associated with use.
http://www.analysir.com/blog/2014/03/19/air-conditioners-problems-recording-long-infrared-remote-control-signals-arduino/

Connections:
IR Receiver      Arduino
V+          ->  +5v
GND          ->  GND
Signal Out   ->  Digital Pin 2
(If using a 3V Arduino, you may connect V+ to +3V)
*/
#include <IRremote.h>
#define LEDPIN 14
//you may increase this value on Arduinos with greater than 2k SRAM
#define maxLen 800

IRsend irsend(5);
volatile  unsigned int irBuffer[maxLen]; //stores timings - volatile because changed by ISR
volatile unsigned int x = 0; //Pointer thru irBuffer - volatile because changed by ISR

unsigned int OFF[197] = {6400,7000, 850,1300, 900,1300, 800,1400, 650,1500, 650,1550, 600,1600, 550,1600, 550,1650, 550,550, 
550,550, 550,600, 550,550, 550,600, 500,600, 550,550, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 550,1650, 550,1650, 
500,1650, 550,1650, 550,550, 550,550, 550,600, 550,550, 550,600, 500,600, 550,550, 550,550, 550,1650, 550,1600, 550,1650, 550,1600, 
550,1650, 550,1600, 550,1650, 550,1600, 550,600, 550,550, 550,600, 550,550, 550,550, 550,600, 500,600, 550,550, 550,1650, 550,1600, 550,1650, 
550,550, 550,600, 550,550, 550,600, 500,1650, 550,550, 550,550, 550,600, 550,1600, 550,1650, 550,1600, 550,1650, 550,550, 550,1650, 550,1600, 
600,1600, 550,600, 550,1600, 550,550, 550,1650, 550,1600, 550,600, 550,550, 550,600, 550,1600, 550,600, 500,1650, 550,600, 500,600, 500,600, 550,
1600, 550,600, 550,1600, 550,600, 550,1600, 550,600, 550,550, 550,1650, 550,550, 550,1650, 500,600, 500,1650, 550,600, 500,1650, 550,1650, 500,7350, 550};  // UNKNOWN B99B0EA9
void setup() {
  Serial.begin(115200); //change BAUD rate as required
  pinMode(23, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(23), rxIR_Interrupt_Handler, CHANGE);//set up ISR for receiving IR signal
}

void loop() {
  // put your main code here, to run repeatedly:
  irsend.sendRaw(OFF, 197, 38);  
  Serial.println(F("Press the button on the remote now - once only"));
  delay(5000); // pause 5 secs
  if (x) { //if a signal is captured
    digitalWrite(LEDPIN, HIGH);//visual indicator that signal received
    Serial.println();
    Serial.print(F("Raw: (")); //dump raw header format - for library
    Serial.print((x - 1));
    Serial.print(F(") "));
    detachInterrupt(0);//stop interrupts & capture until finshed here
    for (int i = 1; i < x; i++) { //now dump the times
      if (!(i & 0x1)) Serial.print(F("-"));
      Serial.print(irBuffer[i] - irBuffer[i - 1]);
      Serial.print(F(", "));
    }
    x = 0;
    Serial.println();
    Serial.println();
    digitalWrite(LEDPIN, LOW);//end of visual indicator, for this time
    attachInterrupt(0, rxIR_Interrupt_Handler, CHANGE);//re-enable ISR for receiving IR signal
  }

}

void rxIR_Interrupt_Handler() {
  if (x > maxLen) return; //ignore if irBuffer is already full
  irBuffer[x++] = micros(); //just continually record the time-stamp of signal transitions

}
