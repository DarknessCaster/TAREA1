#ifndef PROTOCOLO_H
#define PROTOCOLO_H
#define BYTE unsigned char
#define LARGO_DATA 15
#define TX_PIN 
#define RX_PIN
#define CLOCK_PIN

struct Protocolo{
    BYTE CMD; // 4 BITS
    BYTE LNG; // 4 BITS
    BYTE DATA[LARGO_DATA];
    BYTE FCS; // 1 BYTE
    BYTE FRAMES[LARGO_DATA+2];
};

#endif