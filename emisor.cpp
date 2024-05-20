#include <wiringPi.h>
#include <stdio.h>
#include <string.h>
#include "funciones.h"

// VARIABLES GLOBALES
Protocolo proto;
int msg_enviados;
char nombre_arch[20];
bool transmissionStarted = false; // Indica si la transmision empieza o no.

int main(){
    //INICIA WIRINGPI
    if(wiringPiSetup() == -1)
    exit(1);

    //CONFIGURA PINES DE ENTRADA SALIDA
    pinMode(TX_PIN, OUTPUT);
    
    // CONFIGURA INTERRUPCION PIN CLOCK
    if (wiringPiISR(DELAY_PIN, INT_EDGE_RISING, &enviarBytes) < 0) {
        printf("No se puede iniciar la función de interrupción\n");
        exit(1);
    }

    //INICIA MENU
    do {
        printf("\n================== MENU ==================\n");
        printf("1. Enviar mensaje de prueba\n");
        printf("2. Enviar mensaje de texto\n");
        printf("3. Buscar archivo txt\n");
        printf("4. Ver cantidad de mensajes enviados\n");
        printf("5. Listar archivos de texto del receptor\n");
        printf("6. Crear archivo y registrar un mensaje\n"); //  *** PUNTAJES EXTRAS: 2.
        printf("7. Cerrar programa receptor\n");
        printf("==============================================\n");
        printf("Ingrese la opcion deseada: ");
        scanf("%d", &proto.CMD);
        printf("%x", proto.CMD);
        getchar(); 
        switch (proto.CMD) {
            case 1:
                printf("\nIngrese el mensaje a enviar (15 caracteres maximo):");
                scanf(" %[^\n]s", proto.DATA);
                empaquetar(proto);
<<<<<<< HEAD
                for(int i = 0; i < 10; i++){ // Para enviar 10 veces?
                    startTransmission();
                    enviarBytes(proto);
=======
                for(int i = 0; i < 10; i++){ // *** Para enviar 10 veces?
                    // Ejecutar emisor
>>>>>>> 30d56c578170773551c0a616ca9ac5f622fedd7d
                    msg_enviados++;
                }
                break;
            case 2:
                printf("\nIngrese el mensaje de texto a enviar (15 caracteres maximo):");
                scanf(" %[^\n]s", proto.DATA);
                empaquetar(proto);
                // Ejecutar emisor
                guardarMensaje((char*)proto.DATA);
                msg_enviados++;
                break;
            case 3:
                printf("\nIngrese el nombre del archivo de texto a mostrar:");
                //scanf(" %[^\n]s", nombre_arch);
                scanf(" %[^\n]s", proto.DATA);
                empaquetar(proto);
                // Ejecutar emisor
                mostrarArchivo(nombre_arch); // *** En realidad el receptor debe ejecutar esta funcion, el mensaje sera nombre del archivo.
                msg_enviados++;
                break;
            case 4:
                printf("Mensajes enviados: %d", msg_enviados); // *** Esto tambien debe ir en el receptor.
                empaquetar(proto);
                // Ejecutar emisor
                msg_enviados++;              
                break;
            case 5:
                empaquetar(proto);
                // Ejecutar emisor
                // *** En receptor ejecutar funcion (funcion pendiente);
                msg_enviados++;                     
                break;
            case 6:
                crearArchivo();
                printf("\nIngrese el mensaje a enviar (15 caracteres maximo):");
                scanf(" %[^\n]s", proto.DATA);
                empaquetar(proto);
                // Ejecutar emisor
                msg_enviados++;
                break;
            case 7:
                printf("\nComunicacion finalizada");
                empaquetar(proto);
                // Ejecutar emisor
                msg_enviados++;
                break;
            default:
                printf("Opción inválida. Por favor, ingrese una opción válida.\n");
                break;
        }
    } while (proto.CMD != 7); // se cierra el emisor si proto.CMD = 7.
    return 0;
}
