//INCLUSIONES
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//MACROS
#define DELAY_PIN 0 // Pin utilizado para interrupciones
#define TX_PIN 2 // Pin de transmision (salida)

#define BYTE unsigned char

//DECLARACION DE PROTOTIPOS
void cb(void);
void startTransmission();

//VARIABLES GLOBALES
volatile int nbits = 0; // contador de bits enviados
BYTE bytes[10] = {1,2,3,4,5,6,7,8,9,10}; // DATA
volatile int nbytes = 0; // contador de bytes enviados
BYTE len = strlen((const char*)bytes); // longitud de data
int nones = 0;
bool transmissionStarted = false; // Indica si la transmision empieza o no.

int main(){
  //INICIA WIRINGPI
  if(wiringPiSetup() == -1)
    exit(1);

  /*CONFIGURA INTERRUPCION PIN CLOCK (PUENTEADO A PIN PWM)
  * Configura una interrupcion en DELAY_PIN para activarse en un flanco
  * ascendente (INT_EDGE_RISING). La funcion de interrupcion es cb.
  */
  if(wiringPiISR(DELAY_PIN, INT_EDGE_RISING, &cb) < 0){
    printf("Unable to start interrupt function\n");
  }

  //CONFIGURA PINES DE ENTRADA SALIDA
  pinMode(TX_PIN, OUTPUT);
  
  //  printf("Delay\n");
  //  delay(5000);
  startTransmission(); // inicia la transmision
  while(transmissionStarted)
    delay(2000);
  
  return 0;
}

void cb(void){
  if(transmissionStarted){ // Si transmision se inicia...
    //Escribe en el pin TX
    if(nbits == 0){
      digitalWrite(TX_PIN, 0); // Se envia bit de inicio
    }else if(nbits < 9){
      // envia bit a bit el dato hasta enviar el byte
      digitalWrite(TX_PIN, (bytes[nbytes] >> (nbits-1)) & 0x01); 
//      printf("%d",(bytes[nbytes]>>(nbits-1))&0x01);
    }else if(nbits == 9){
//      printf("\n");
      nones = (bytes[nbytes]&0x01) + ((bytes[nbytes]&0x02)>>1) + ((bytes[nbytes]&0x04)>>2) + 
        ((bytes[nbytes]&0x08)>>3) + ((bytes[nbytes]&0x10)>>4) + ((bytes[nbytes]&0x20)>>5) + 
        ((bytes[nbytes]&0x40)>>6) + ((bytes[nbytes]&0x80)>>7);
      digitalWrite(TX_PIN, nones%2==0); //Bit de paridad
    }else{
      digitalWrite(TX_PIN, 1); //Canal libre durante 2 clocks
    }

    //Actualiza contador de bits
    nbits++;

    //Actualiza contador de bytes
    if(nbits == 11){
      nbits = 0;
      nbytes++;

      //Finaliza la comunicación
      if(nbytes==len){
        transmissionStarted = false;
        nbytes = 0;
      }
    }
  }else{
    //Canal en reposo
    digitalWrite(TX_PIN, 1);
  }
}

void startTransmission(){
  transmissionStarted = true;
}
