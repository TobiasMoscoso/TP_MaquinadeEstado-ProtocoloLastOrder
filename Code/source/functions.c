#include "../lib/libs.h"
#include "../lib/prototypes.h"


depoGeneral_t getConfig(void){
    depoGeneral_t depo;
    char i;
    char caracteristicas[6][15] = {"Estantes","FilasF","ColumnasF",
    "FilasI","ColumnasI","Maquinas"};
    char cadena[20], *key, *val;
    FILE *c;

    c= fopen("config.conf","rb");

    fgets(cadena,20,c);

    while(!feof(c)){
        if((*key) != '#' && strlen(key) >= 0){
            val = getKey(key);
            for(i=0;i<6;i++){
                if(!strcmp(key,caracteristicas[i])){
                    switch(i){
                        case 0://Estantes
                        depo.estantes = atoi(val);
                        case 1://FilasF
                        depo.filasF = atoi(val);
                        case 2://ColumnasF
                        depo.columnasF = atoi(val);
                        case 3://FilasI
                        depo.filasI = atoi(val);
                        case 4://ColumnasI
                        depo.columnasI = atoi(val);
                        case 5://Maquinas
                        depo.maquinas = atoi(val);
                    }
                }
            }
        }
    }

}

char *getKey(char *key){
    char i = 0;
    while(*(key+i) != ' '){
        i++;
    }
    *(key+i) = 0;
    return key+i+1;
}

estados_t f_LeerMaquinas(depoGeneral_t depo, char *e, deposito_t *prod){
    FILE *p;
    deposito_t productoList;
    entrega_t productoIn = SimulMaquina();
    //compara con listado.dat
    //Debe coincidir tipoCaja y tipoProd
    
    if(productoIn.ubiI_columna > depo.columnasI && productoIn.ubiI_fila > depo.filasI){
        //Ubicacion del producto desconocida
        e = 'u';
        return Error;
    }

    fopen("listado.dat","rb");//solo lectura
    fread(&productoList,sizeof(productoList),1,p);
    while(!feof(p)){
        
        if(productoList.ubiF_fila > depo.filasF && productoList.ubiF_columna > depo.columnasF && productoList.ubiF_estante > depo.estantes){
            //Producto indeseado en la Lista
            e = 'P';
            fclose(p);
            return Error;
        }

        if(!strcmp(productoList.tipoProd, productoIn.tipoProd) && productoList.tipoCaja == productoIn.tipoCaja){
            //El producto existe, necesito su ubicacion Final... como la devuelvo?
                strcpy(prod->tipoProd,productoList.tipoProd);
                prod->tipoCaja = productoList.tipoCaja;
                prod->ubiF_fila = productoList.ubiF_fila;
                prod->ubiF_columna = productoList.ubiF_columna;
                prod->ubiF_estante = productoList.ubiF_estante;
                fclose(p);
                return Almacenar;
        }
        else{
            fclose(p);
            // Producto desconocido
            e = 'p';
            return Error;
        }
        
    }
}

entrega_t SimulMaquina(){
    entrega_t producto;
    printf("***SIMULACION MAQUINA***\nMAQUINA ANALIZANDO PRODUCTO...\n");
    system("pause");
    printf("Numero de Maquina: ");
    scanf("%d",&producto.nMaquina);fflush(stdin);
    printf("\nTipo de Caja: ");
    scanf("%c",&producto.tipoCaja);fflush(stdin);
    printf("\nTipo de Producto: ");
    gets(producto.tipoProd);
    printf("\nFila de Entrada Deposito: ");
    scanf("%d",&producto.ubiI_fila);fflush(stdin);
    printf("\nColumna de Entrada Deposito: ");
    scanf("%d",&producto.ubiI_columna);fflush(stdin);

    return producto;
      
}

estados_t f_dirFinalMaquina(depoGeneral_t depo, char *e,deposito_t *prod){
    sendUbiFinal(prod->nMaquina,prod->ubiF_estante, prod->ubiF_fila, prod->ubiF_columna);
    if(!InformeEstado(prod->nMaquina,e)){
        return Error;
    }
    printf("Producto Almacenado!\n");
    return IrUbicacionInicial;
    
}

int InformeEstado(uint8_t maquina,char *e){
    char opcion;
    printf("***SIMULACION MAQUINA***\nMAQUINA %d ENVIANDO INFORME DE ESTADO...\n", maquina);
    while(1){
        printf("c. Caida\nb. Bateria baja\nn.En viaje\nf. Llego el producto");
        scanf("%c", &opcion);fflush(stdin);
        switch(opcion){
            case 'c': e = 'c';
            return 0;
            case 'b': e = 'b';
            return 0;
            case 'f': return 1;
        }
    }

}

void sendUbiFinal(uint8_t maquina, int estante, int fila, int columna){
        printf("***SIMULACION MAQUINA***\nMAQUINA LLEVANDO PRODUCTO...\n");
        system("pause");
        printf("Maquina %d dirigiendose a:\n",maquina);
        printf("Entante: %d\n", estante);
        printf("Fila: %d\n", fila);
        printf("Columna: %d\n", columna);
        system("pause");
}