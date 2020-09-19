/**
 * Trabajo Practico Maquinas de Estado
 * Sistema LastOrder v1.65
 * 
*/
//gcc main.c functions.c -o combined

#include "../lib/prototypes.h"
int main(){
    estados_t estado;
    printf("***Sistema LastOrder v1.798***\n");
    //leer y cargar el archivo de configuracion
    depoGeneral_t deposito = getConfig();
    char error;
    deposito_t prodAlmacenar;
    deposito_t *prod = &prodAlmacenar;
    char *e = &error;
    estado = 0;//Inicio "Hay algun producto"


    while(1){
        switch(estado){
            case Espera:
                estado = f_LeerMaquinas(deposito,e,prod);break;
            case Almacenar:
                estado = f_dirFinalMaquina(deposito,e,prod);break;
            case IrUbicacionInicial:
                estado = f_dirInicialMaquina(deposito,e,prod);break;
            case Error:
                estado = f_error(deposito,e,prod);break;//Todas las maquina de estado necesitan de deposito?
        }
    }

}