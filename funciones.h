#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "protocolo.h"

int empaquetar(Protocolo &proto);
bool desempaquetar(Protocolo&proto, int tam); 
void guardarMensaje(char cadena[]);
void mostrarArchivo(char cadena[]);
void crearArchivo();
int fcs(BYTE * arr, int tam);
void enviarBytes(Protocolo proto, bool transmissionStarted);
void recibirBytes();
void startTransmission();

#endif