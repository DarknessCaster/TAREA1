#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include "funciones.h"

Protocolo proto; // Deberia recibir proto desde emisor
int msg_c_err = 0; // mensajes con error
int msg_s_err = 0; // Mensaje sin error detectado... seria lo mismo que recibidos correctamente?
int msg_total = 0; // mensajes en total
float porcentaje_a = 0; // porcentaje de acierto
float porcentaje_e = 0;
bool estado = true;
//VARIABLES GLOBALES
volatile int errors = 0;
volatile int nbits = 0;
volatile int nbytes = 0;
bool transmissionStarted = false;
bool parity = 0;
int nones = 0;
BYTE FRAMES[LARGO_DATA+2]; // PAQUETE RECIBIDO
bool parityError = 0;
volatile BYTE len = 10; // LARGO

int main(){
    //INICIA WIRINGPI
    if(wiringPiSetup() == -1)
    exit(1);

    //CONFIGURA PINES DE ENTRADA SALIDA
    pinMode(RX_PIN, INPUT);

    //CONFIGURA INTERRUPCION PIN CLOCK (PUENTEADO A PIN PWM)
    if(wiringPiISR(DELAY_PIN, INT_EDGE_RISING, &cb_receptor) < 0){
        printf("Unable to start interrupt function\n");
    }
    printf("Delay\n");
    desempaquetar(proto)
    while(nbytes < proto.LNG) // NBYTES MENOR A LONGITUD DE DATA??a
        delay(300); 
    switch(proto.CMD){
        case 1:
            estado = desempaquetar(proto, proto.LNG+2);
            if (estado == true) // Si no hay error
                msg_s_err++; 
            else // Si hay error
                msg_c_err++; 
            
            msg_total++; 
            if (msg_total == 10){
                porcentaje_a = 100*(msg_s_err/msg_total);
                porcentaje_e = 100*(msg_c_err/msg_total);
                printf("El porcentaje de acierto es: %f\n", porcentaje_a);
                printf("El porcentaje de error es: %f\n", porcentaje_e);
            }
            break;
        case 2:
            desempaquetar(proto, proto.LNG+2);
            guardarMensaje((char*)proto.DATA);
            break;
        case 3:
            
            break;
        default:
            break;
    }
    return 0;
}