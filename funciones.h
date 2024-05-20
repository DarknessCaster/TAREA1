#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "protocolo.h"

int empaquetar(Protocolo &proto);
bool desempaquetar(Protocolo&proto); 
void guardarMensaje(char cadena[]);
void mostrarArchivo(char cadena[]);
void crearArchivo();
int fcs(BYTE * arr, int tam);
void cb_emisor(void);
void cb_receptor(void);
void recibirBytes();
void startTransmission();
void procesarBit(bool level);

#endif