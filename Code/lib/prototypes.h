#ifndef _PROT
#define _PROT

#include "../lib/libs.h"

/**Notas
 * Requisitos Producto:
 * - Debe existir en la Lista de Productos
 * - Su Ubicacion debe existir (tamaño correcto segun
 * valores seteados pro config.conf)
*/

/**
 * Devuelve las caracteristicas generales del Deposito.
*/
depoGeneral_t getConfig(void);

/**
 * Devuelve la posicion donde se halla el valor.
*/
char *getKey(char*);

/** Server lee los datos del producto en la entrada, y los
 * compara por una lista previamente hecha (archivo binario)
 * Devuelve  Almacenar si el producto cumple los requisitos
 * y tiene un lugar donde ir
 * Sino devuelve Error si el producto no es reconocido o no
 * cumple los requisitos.
*/
estados_t f_LeerMaquinas(depoGeneral_t,char *, deposito_t*);

/** 
 * Server manda una serie de comandos que haran mover a la
 * maquina. 
 * Estara pendiente si ocurre algun error.
*/
estados_t f_dirFinalMaquina(depoGeneral_t, char*, deposito_t*);

/**
 * Server manda una serie de comandos que hacen mover a la
 * maquina hacia una posicion libre de Entrada.
 * Estara pendiente si ocurre algun error.
*/
estados_t f_dirInicialMaquina(depoGeneral_t, char*, deposito_t*);



/**
 * El sistema avisa al encargado del problema sucedido.
 * Ademas, dependiendo del error, detiene a la maquina 
 * de su operacion.
 * Valores:
 * p : Producto desconocido
 * m : Maquina desconocida
 * u : Ubicacion del producto desconocida
 * c : caida
 * b : bateria baja
*/
estados_t f_error(depoGeneral_t, char*, deposito_t*);

/**
 * Simula el escaneo de la maquina.
 * Devuelve el producto escaneado junto su ubicacion.
*/
entrega_t SimulMaquina(void);


/**
 * Simula los comandos necesarios para que la maquina
 * sepa donde ir.
 *  lugar=> '0'=Entrada ó '1'=Deposito
*/
void sendLocation(uint8_t,int, int, int,int);

/**
 * Devuelve:
 * 0 - si surgio un problema:
 *      al puntero de error:
 *          c - caida
 *          b - bateria baja
 * 1 - si llego el producto a su destino
 * 
*/
int InformeEstado(uint8_t, char*);

/**
 * Simula el boton de reinicio para cuando
 * el problema persistente halla sido 
 * solucionado
*/
char reparoHumano(char);




#endif