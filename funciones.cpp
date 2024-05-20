#include "wiringPi.h"
#include <string.h>
#include <stdio.h>
#include "funciones.h"

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
    return true; // Desempaquetado correctamente
}

void startTransmission(){
  transmissionStarted = true;
}

void guardarMensaje(char cadena[]){ // Guarda 
    FILE *archivo;
    // printf("\n La cadena en la funcion es %s", cadena); // Para probar que la cadena este bien en este punto.
    int aux;
    archivo = fopen("mensajes.txt", "a+"); // Abre el archivo "mensajes.txt" en la carpeta actual, si no existe lo crea.
    aux = fgetc(archivo); // Lee el primer caracter del archivo.
        if(aux != EOF){ // Si el archivo esta vacio su primer caracter sera "EOF". Solo cuando se comienza a escribir en el archivo no es necesario un salto de linea.
            fseek(archivo, 0, SEEK_END); // Lleva al inicio del archivo, al primer caracter.
            fprintf(archivo, "\n");
        }
    
        for(int i=0; i<15 ; i++){ // Se hace asi por si hay espacios en la cadena de caracteres, en lugar de solo hacer un fprintf() del string completo.
            if(strcmp(&cadena[i], "\0") == 0){ // Finaliza la escritura de caracteres en el archivo cuando se llega al final del string.
                break;
            }
            fprintf(archivo, "%c", cadena[i]); // Escribe en el archivo la cadena caracter a caracter.
        }
        fclose(archivo);
}

void mostrarArchivo(char cadena[]){ // Muestra el contenido de un archivo cuyo nombre es ingresado por el usuario, si no existe devuelve mensaje de error.
    char aux[15]; 
    FILE *lectura = fopen(strcat((cadena), ".txt"), "r"); // Se concatena el ".txt" al final del nombre entregado e intenta abrir el archivo. 
    if(lectura == NULL){
        printf("\n El archivo %s no existe en nuestros registros.", cadena);
    }else if(fgetc(lectura) == EOF){
        printf("\n El archivo %s existe pero esta vacio.", cadena);
    }else{
        printf("\n Contenido de %s:\n", cadena);
        while(feof(lectura) == 0){ // Mientras que no se halla llegado al final del archivo referenciado por el puntero "lectura" imprime por pantalla cada mensaje en el archivo.
            fgets(aux, 15, lectura);
            printf("%s", aux);
        }
    }
    fclose(lectura);
}

void crearArchivo(){ // Crea un archivo de texto en la carpeta actual a partir de un nombre entregado, si el archivo ya existe devuelve mensaje de error.
    char cadena[25];
    char aux[15];
    printf("\n Ingrese el nombre del archivo que desea crear: ");
    scanf(" %[^\n]s", cadena);
    FILE *lectura = fopen(strcat((cadena), ".txt"), "r"); // Se concatena el ".txt" al final del nombre entregado e intenta abrir el archivo. 
    if(lectura != NULL){ // Si el intento de apertura del archivo no devuelve NULL significa que si existe.
        printf("\n El archivo %s ya existe en nuestros registros.", cadena);
    }else{
        fopen(cadena, "a+");
        printf("\n El archivo %s fue creado con exito.", cadena);
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

void cb_emisor(void) {
    if (transmissionStarted) { // Si transmision se inicia...
        // Escribe en el pin TX
        if (nbits == 0) {
            digitalWrite(TX_PIN, 0); // Se envia bit de inicio
        } 
        else if (nbits < 9) {
            // envia bit a bit el dato hasta enviar el byte
            digitalWrite(TX_PIN, (proto.FRAMES[nbytes] >> (nbits-1)) & 0x01); 
            // printf("%d", (p.FRAMES[nbytes] >> (nbits-1)) & 0x01);
        } 
        else if (nbits == 9) {
            // printf("\n");
            // Guardar bits activos (cantidad de 1s) en la variable nones
            nones = (proto.FRAMES[nbytes] & 0x01) + ((proto.FRAMES[nbytes] & 0x02) >> 1) + ((proto.FRAMES[nbytes] & 0x04) >> 2) + 
                    ((proto.FRAMES[nbytes] & 0x08) >> 3) + ((proto.FRAMES[nbytes] & 0x10) >> 4) + ((proto.FRAMES[nbytes] & 0x20) >> 5) + 
                    ((proto.FRAMES[nbytes] & 0x40) >> 6) + ((proto.FRAMES[nbytes] & 0x80) >> 7);

            digitalWrite(TX_PIN, nones % 2 == 0); // Se envia el Bit de paridad PAR 
        } 
        else {
            digitalWrite(TX_PIN, 1); // Canal libre durante 2 clocks
        }
        
        // Actualiza contador de bits
        nbits++;

        // Actualiza contador de bytes
        if (nbits == 11) {
            nbits = 0;
            nbytes++;

            // Finaliza la comunicación
            if (nbytes == proto.LNG+1) {
                transmissionStarted = false;
                nbytes = 0;
            }
        }
    } 
    else { // Si no ha iniciado la transmision...
        // Canal en reposo
        digitalWrite(TX_PIN, 1);
    }
}

void cb_receptor(void){
  bool level = digitalRead(RX_PIN);
  //  printf("%d",level);
  if (transmissionStarted){
    processBit(level);
  }
  else if(level == 0 && !transmissionStarted){
    transmissionStarted = true;
    nbits = 1;
  }
}