#ifndef _LIBS
#define _LIBS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef unsigned char uint8_t;
typedef enum{
    Espera = 0,
    Almacenar = 1,
    IrUbicacionInicial = 2,
    Error = 3
}estados_t;

// Esta struct es la que la maquina envia al server
typedef struct{
    unsigned char nMaquina;//numero de la maquina
    char tipoCaja;//Especifica el tamaño de cajas estandar: A B C o D
    char tipoProd[20];//Nombre del producto que contiene la caja
    int ubiI_fila;
    int ubiI_columna;//ubicacion inicial de donde se encuentra la maquina
}entrega_t;
/**
 * Ejemplo:
 * 45
 * A
 * SJDHNSH8384
 * 12
 * 7
*/
//Es la que el server responde a la maquina
typedef struct{
    char tipoProd[20];//Nombre del producto que contiene la caja
    char tipoCaja;//Especifica el tamaño de cajas estandar: A B C o D
    int ubiF_fila;
    int ubiF_columna;
    int ubiF_estante;
    uint8_t nMaquina;
}deposito_t;

typedef struct{
    uint8_t estantes, filasF, columnasF, filasI, columnasI, maquinas;
}depoGeneral_t;

//Informes de estado que recibe el server
typedef struct{
    uint8_t nMaquina;
    char estado;// 'C' caida   'B' bateria baja 'M' error mecanico
}infEstado_t;

#endif _LIBS