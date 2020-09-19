/**
 * Sistema LastOrder v1.65
 * Programa para la creacion de archivos binarios.
 * (Lista de productos)
*/

#include "../lib/libs.h"

int main(){
    FILE *p;
    deposito_t a;
    char sel = 1;
    printf("Generador de listado para Sistema LastOrder(*o*)/\n");
    do{ 
    printf("\nNombre de Producto: \n");
    gets(a.tipoProd);
    printf("Tipo de Caja: \n");
    scanf("%c",&a.tipoCaja);fflush(stdin);
    printf("Numero de Estante donde se debe almacenar: \n");
    scanf("%d",&a.ubiF_estante);fflush(stdin);
    printf("Numero de Fila: \n");
    scanf("%d",&a.ubiF_fila);fflush(stdin);
    printf("Numero de Columna: \n");
    scanf("%d",&a.ubiF_columna);fflush(stdin);

    p = fopen("listado.dat","ab");
    fwrite(&a,sizeof(a),1,p);
    printf("Mas Productos? 1:SI / 0:NO ");
    scanf("%d",&sel);fflush(stdin);
    }while(sel);
    fclose(p);
}