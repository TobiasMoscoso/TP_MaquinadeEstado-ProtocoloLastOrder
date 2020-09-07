#ifndef _PROT
#define _PROT

#include "../lib/libs.h"

/**Notas
 * Requisitos Producto:
 * - Debe existir en la Lista de Productos
 * - Su Ubicacion debe existir (tamaño correcto segun
 * valores seteados pro config.conf)
*/

depoGeneral_t getConfig(void);
/**
 * Devuelve las caracteristicas generales del Deposito.
*/

char *getKey(char*);
/**
 * Devuelve la posicion donde se halla el valor.
*/

estados_t f_LeerMaquinas(depoGeneral_t,char *, deposito_t*);
/** Server lee los datos del producto en la entrada, y los
 * compara por una lista previamente hecha (archivo binario)
 * Devuelve  Almacenar si el producto cumple los requisitos
 * y tiene un lugar donde ir
 * Sino devuelve Error si el producto no es reconocido o no
 * cumple los requisitos.
*/

estados_t f_dirFinalMaquina(depoGeneral_t, char*, deposito_t*);
/** 
 * Server manda una serie de comandos que haran mover a la
 * maquina. 
 * Estara pendiente si ocurre algun error.
*/

estados_t f_dirInicialMaquina(depoGeneral_t, char*, deposito_t*);
/**
 * Server manda una serie de comandos que hacen mover a la
 * maquina hacia una posicion libre de Entrada.
 * Estara pendiente si ocurre algun error. En caso de siniestro
 * cambiara el caracter del puntero e con respecto al error
 * sucedido.
*/

estados_t f_error(char);
/**
 * El sistema avisa al encargado del problema sucedido.
 * Ademas, dependiendo del error, detiene a la maquina 
 * de su operacion.
 * Valores:
 * P : Producto indeseado en la Lista
 * p : Producto desconocido
 * u : Ubicacion del porducto desconocida
 * c : caida
 * b : bateria baja
*/

entrega_t SimulMaquina(void);
/**
 * Simula el escaneo de la maquina.
 * Devuelve el producto escaneado junto su ubicacion.
*/
void sendUbiFinal(uint8_t,int, int, int);
/**
 * Simula los comandos necesarios para que la maquina
 * sepa donde ir.
*/

int InformeEstado(uint8_t, char*);
/**
 * Devuelve:
 * 0 - si surgio un problema:
 *      c - caida
 *      b - bateria baja
 * 1 - si llego el producto a su destino
 * 
*/

#endif _PROT