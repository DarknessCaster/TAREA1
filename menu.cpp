#include <stdio.h>
#include <string.h>
#include "funciones.h"

BYTE opcion = 0;
BYTE mensaje[15];
Protocolo proto;

int main(){
    do {
        printf("\n========== MENU ==========\n");
        printf("1. Enviar mensaje de prueba\n");
        printf("2. Enviar mensaje de texto\n");
        printf("3. Buscar archivo txt\n");
        printf("4. Ver cantidad de mensajes enviados\n");
        printf("5. Listar archivos de texto del receptor\n");
        printf("6. Crear archivo y registrar un mensaje\n"); //  PUNTAJES EXTRAS: 2.
        printf("7. Cerrar programa receptor\n");
        printf("==========================\n");
        printf("Ingrese la opcion deseada: ");
        scanf("%d", &proto.CMD);
        getchar(); 
        switch (proto.CMD) {
            case 1:
                printf("\nIngrese el mensaje a enviar (15 caracteres maximo):");
                scanf(" %[^\n]s", proto.DATA);
                empaquetar(proto);
                // Ejecutar emisor
                break;
            case 2:
                printf("\nIngrese el mensaje de texto a enviar (15 caracteres maximo):");
                scanf(" %[^\n]s", proto.DATA);
                empaquetar(proto);
                // Ejecutar emisor
                break;
            case 3:
                
                break;
            case 4:
                break;
            case 5:
                
                break;
            case 6:
                crearArchivo();
                printf("\nIngrese el mensaje a enviar (15 caracteres maximo):");
                scanf(" %[^\n]s", proto.DATA);
                empaquetar(proto);
                // Ejecutar emisor
                break;
            default:
                break;
        }
    } while (opcion != 7);
    return 0;
}