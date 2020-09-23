/**
 * Trabajo Practico Maquinas de Estado
 * Sistema LastOrder v1.978
 * 
*/


#include "../lib/prototypes.h"
int main(){
    estados_t estado;
    printf("***Sistema LastOrder v1.978***\n");
    //leer y cargar el archivo de configuracion
    depoGeneral_t deposito = getConfig();

    deposito_t prodAlmacenar;
    deposito_t *prod = &prodAlmacenar;
    char error;
    char *e = &error;
    estado = 0;//Inicio "Hay algun producto"
    estados_t (*paf[])(depoGeneral_t,char*,deposito_t*)={f_LeerMaquinas,f_dirFinalMaquina,f_dirInicialMaquina,f_error};

    while(1)
        estado = (*paf[estado])(deposito,e,prod);

}