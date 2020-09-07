/**
 * Trabajo Practico Maquinas de Estado
 * Sistema LastOrder v1.65
 * 
*/

#include "../lib/libs.h"
#include "../lib/prototypes.h"
int main(){
    estados_t estado;
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
                estado = f_leerMaquinas(deposito,e,prod);
            case Almacenar:
                estado = f_dirFinalMaquina(deposito,e,prod);
            case IrUbicacionInicial:
                estado = f_dirInicialMaquina(deposito,e,prod);
            case Error:
                estado = f_error(error);//Todas las maquina de estado necesitan de deposito?
        }
    }

}