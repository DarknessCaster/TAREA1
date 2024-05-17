#include <stdio.h>
#include <string.h>
#include "funciones.h"

Protocolo proto; // Deberia recibir proto desde emisor
int msg_c_err = 0;
int msg_s_err = 0; // Mensaje sin error detectado... seria lo mismo que recibidos correctamente?
int msg_total = 0;
float porcentaje_a = 0;
float porcentaje_e = 0;
bool estado = true;

int main(){
    printf("\n================== MENU ==================\n");
    printf("1. Enviar mensaje de prueba\n");
    printf("2. Enviar mensaje de texto\n");
    printf("3. Buscar archivo txt\n");
    printf("4. Ver cantidad de mensajes enviados\n");
    printf("5. Listar archivos de texto del receptor\n");
    printf("6. Crear archivo y registrar un mensaje\n"); //  PUNTAJES EXTRAS: 2.
    printf("7. Cerrar programa receptor\n");
    printf("==============================================\n");
    printf("Ingrese la opcion deseada: ");
    scanf("%d", &proto.CMD);
    getchar(); 
    switch(proto.CMD){
        case 1:
            estado = desempaquetar(proto, proto.LNG+2);
            if (estado == true){
                msg_s_err++;
            } else{
                msg_c_err++;
            } 
            msg_total++;
            if (msg_total == 10){
                porcentaje_a = 100*(msg_s_err/msg_total);
                porcentaje_e = 100*(msg_c_err/msg_total);
                printf("El porcentaje de acierto es: %f\n", porcentaje_a);
                printf("El porcentaje de error es: %f\n", porcentaje_e);
            }
            break;
        default:
            break;
    }
    return 0;
}