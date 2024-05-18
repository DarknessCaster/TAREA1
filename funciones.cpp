#include "funciones.h"
#include <string.h>
#include <stdio.h>

int empaquetar(Protocolo &proto){
    // if (proto.LNG + 2 > LARGO_DATA + 2){
    //     return -1;
    // } 
    proto.LNG = strlen((const char*)proto.DATA);
    proto.FRAMES[0] = (proto.CMD & 0x0F) | ((proto.LNG & 0x0F) << 4);
    memcpy(&proto.FRAMES[1], proto.DATA, proto.LNG);
    proto.FCS = fcs(proto.FRAMES, proto.LNG+1);
    proto.FRAMES[proto.LNG+1] = (proto.FCS) & 0xFF;
    return proto.LNG +2;
}

bool desempaquetar(Protocolo&proto, int tam){
    // if (tam != proto.LNG+2){
    //     return false;
    // }
    proto.CMD = proto.FRAMES[0] & 0x0F;
    proto.LNG = ((proto.FRAMES[0] >> 4) & 0x0F);
    if (proto.LNG > 0 && proto.LNG <= LARGO_DATA){
        for(int i = 0; i < proto.LNG; i++){
            proto.DATA[i] = proto.FRAMES[i+1] & 0xFF;
        }
    } 
    proto.FCS = proto.FRAMES[proto.LNG+1];
    int fcs_recibido = fcs(proto.FRAMES, proto.LNG+1);
    if (fcs_recibido != proto.FCS){
        return false;
    } 
    return true;
}

bool desempaquetar2(Protocolo&proto, int tam){
    if (tam != proto.LNG+2){                            //filtro 1, corrrespondiente al largo total del mensaje
        return false;
    }
    proto.CMD = proto.FRAMES[0] & 0x0F;
    proto.LNG = ((proto.FRAMES[0] >> 4) & 0x0F);
    if (proto.LNG > 0 && proto.LNG <= LARGO_DATA){      
        for(int i = 0; i < proto.LNG; i++){
            proto.DATA[i] = proto.FRAMES[i+1] & 0xFF;
        }
    } 
    proto.FCS = proto.FRAMES[proto.LNG+1];
    int fcs_recibido = fcs(proto.FRAMES, proto.LNG+1);
    if (fcs_recibido != proto.FCS){                     //filtro 2, correspondiente a la comparacion de los fcs 
        return false;
    } 
    return true;
}

void guardarMensaje(char cadena[]){
    FILE *archivo;
    printf("\n La cadena en la funcion es %s", cadena);
    int aux;
    //FILE *archivo = fopen("mensajes.txt", "a+");
    archivo = fopen("mensajes.txt", "a+");
    aux = fgetc(archivo); // Lee el primer caracter del archivo
        if(aux != EOF){ // Si el archivo esta vacio su primer caracter sera "EOF". Solo cuando se comienza a escribir en el archivo no es necesario un salto de linea.
            fseek(archivo, 0, SEEK_END);
            fprintf(archivo, "\n");
        }
    
        for(int i=0; i<15 ; i++){ // Se hace asi por si hay espacios en la cadena de caracteres.
            if(strcmp(&cadena[i], "\0") == 0){ // Evita escribir caracteres nulos cuando el largo de la cadena guardada es menor a 15.
                break;
            }
            fprintf(archivo, "%c", cadena[i]); // Escribe en el archivo la cadena caracter a caracter.                      
        }
        fclose(archivo);
}

void mostrarArchivo(char cadena[]){
    char aux[15];
    FILE *lectura = fopen(strcat((cadena), ".txt"), "r");
    if(lectura == NULL){
        printf("\n El archivo %s no existe en nuestros registros.", cadena);
    }else if(fgetc(lectura) == EOF){
        printf("\n El archivo %s existe pero esta vacio.", cadena);
    }else{
        printf("\n Contenido de %s:\n", cadena);
        while(feof(lectura) == 0){
            fgets(aux, 15, lectura);
            printf("%s", aux);
        }
    }
    fclose(lectura);
}

void crearArchivo(){ // crea un archivo de texto a partir de un nombre entregado, si existe devuelve mensaje de error.
    char cadena[25];
    char aux[15];
    printf("\n Ingrese el nombre del archivo que desea crear: ");
    scanf(" %[^\n]s", cadena);
    FILE *lectura = fopen(strcat((cadena), ".txt"), "r");
    if(lectura != NULL){
        printf("\n El archivo %s ya existe en nuestros registros.", cadena);
    }else{
        printf("\n El archivo %s fue creado con exito.", cadena);
        fopen(cadena, "a+");
    }
}

int fcs(BYTE * arr, int tam){
    int sum_bits = 0;
    for(int i=0; i<tam; i++){
        for(int j=0; j<8; j++){
            sum_bits += (arr[i] >> j) & 0x01;
        } 
    }
    return sum_bits;
}

void enviarBytes(){

}

void recibirBytes(){
    
}
