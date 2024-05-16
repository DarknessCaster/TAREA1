#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "protocolo.h"

int empaquetar(Protocolo &proto);
bool desempaquetar(Protocolo&proto, int tam);
int fcs(BYTE * arr, int tam);
void crearArchivo();
void mostrarArchivo();
void guardarMensaje(char cadena[]);

#endif