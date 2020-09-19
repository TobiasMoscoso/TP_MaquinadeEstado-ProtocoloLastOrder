
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
        key = cadena;
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
        fgets(cadena,20,c);
    }
    printf("Archivo de config leido\n");
    printf("La entrada de maercaderia cuenta con: \n");
    printf("%d filas y %d columnas. \n",depo.filasI,depo.columnasI);
    
    printf("El deposito cuenta con: \n");
    printf("%d estantes, de %d filas y %d columnas. \n",depo.estantes,depo.filasF,depo.columnasF);
    printf("Cuenta con %d maquinas Robot\n",depo.maquinas);
    fclose(c);
    system("pause");
    return depo;
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
    
    if(productoIn.nMaquina > depo.maquinas){
        //Maquina desconocida
        *e = 'm';
        return Error;
    }

    if(productoIn.ubiI_columna > depo.columnasI && productoIn.ubiI_fila > depo.filasI){
        //Ubicacion del producto desconocida
        *e = 'u';
        return Error;
    }
    
    prod->nMaquina = productoIn.nMaquina;

    if(!(p = fopen("listado.dat","rb"))){
        printf("Error al abrir el archivo listado.dat\n");
    }

    fread(&productoList,sizeof(productoList),1,p);
    while(!feof(p)){
        //compara con listado.dat
        //Debe coincidir tipoCaja y tipoProd
        if(!strcmp(productoList.tipoProd, productoIn.tipoProd) && productoList.tipoCaja == productoIn.tipoCaja){
            //El producto existe, necesito su ubicacion Final... como la devuelvo?
                strcpy(prod->tipoProd,productoList.tipoProd);
                prod->tipoCaja = productoList.tipoCaja;
                prod->ubiF_fila = productoList.ubiF_fila;
                prod->ubiF_columna = productoList.ubiF_columna;
                prod->ubiF_estante = productoList.ubiF_estante;
                fclose(p);
                printf("Producto reconocido..\n");
                printf("Iniciando almacenaje..\n");
                system("pause");
                return Almacenar;
        }
        fread(&productoList,sizeof(productoList),1,p);
    }
    fclose(p);
    // Producto desconocido
    *e = 'p';
    return Error;
}

entrega_t SimulMaquina(){
    entrega_t producto;
    system("cls");
    printf("***SIMULACION MAQUINA***\nMAQUINA ANALIZANDO PRODUCTO...\n");
    system("pause");
    printf("Numero de Maquina: ");
    scanf("%d",&producto.nMaquina);fflush(stdin);
    printf("\nTipo de Producto: ");
    gets(producto.tipoProd);
    printf("\nTipo de Caja: ");
    scanf("%c",&producto.tipoCaja);fflush(stdin);
    printf("\nFila de Entrada Deposito: ");
    scanf("%d",&producto.ubiI_fila);fflush(stdin);
    printf("\nColumna de Entrada Deposito: ");
    scanf("%d",&producto.ubiI_columna);fflush(stdin);
    system("cls");
    return producto;
      
}

estados_t f_dirFinalMaquina(depoGeneral_t depo, char *e,deposito_t *prod){
    sendLocation(prod->nMaquina,1, prod->ubiF_fila, prod->ubiF_columna,prod->ubiF_estante);
    if(!InformeEstado(prod->nMaquina,e)){
        return Error;
    }
    printf("Producto Almacenado!\n");
    return IrUbicacionInicial;
    
}

int InformeEstado(uint8_t maquina,char *e){
    char opcion;
    while(1){
        system("cls");
        printf("***SIMULACION MAQUINA***\nMAQUINA %d ENVIANDO INFORME DE ESTADO...\n", maquina);
        printf("c. Caida\nb. Bateria baja\nn. En viaje\nf. Llego el producto");
        scanf("%c", &opcion);fflush(stdin);
        switch(tolower(opcion)){
            case 'c': 
                *e = 'c';
                return 0;
            case 'b': 
                *e = 'b';
                return 0;
            case 'f': 
                return 1;
        }
    }
}

void sendLocation(uint8_t maquina, int lugar, int fila, int columna,int estante){
        system("cls");
        switch(lugar){
            case 0://Entrada
            printf("***SIMULACION MAQUINA***\nMAQUINA VOLVIENDO...\n");
            system("pause");
            printf("Maquina %d dirigiendose a:\n",maquina);
            printf("Fila: %d\n", fila);
            printf("Columna: %d\n", columna);
            system("pause");break;
            case 1://Deposito
            printf("***SIMULACION MAQUINA***\nMAQUINA LLEVANDO PRODUCTO...\n");
            system("pause");
            printf("Maquina %d dirigiendose a:\n",maquina);
            printf("Estante: %d\n", estante);
            printf("Fila: %d\n", fila);
            printf("Columna: %d\n", columna);
            system("pause");break;
        }
        
}

estados_t f_dirInicialMaquina(depoGeneral_t depo, char *e , deposito_t* prod){
    int filaIn,columnaIn;
    printf("Seleccione lugar disponible en la Entrada:\n");
    printf("Fila: ");
    scanf("%d",&filaIn);fflush(stdin);
    printf("\nColumna: ");
    scanf("%d",&columnaIn);fflush(stdin);
    while((filaIn > depo.filasI) || (columnaIn > depo.columnasI)){
        system("cls");
        printf("Valores Incorrectos\n");
        printf("Seleccione lugar disponible en la Entrada:\n");
        printf("Fila: ");
        scanf("%d",&filaIn);fflush(stdin);
        printf("\nColumna: ");
        scanf("%d",&columnaIn);fflush(stdin);
    }
    sendLocation(depo.maquinas,0,filaIn,columnaIn,0);
    if(!InformeEstado(prod->nMaquina,e)){
        return Error;
    }
    printf("Maquina llego corectamente a la Entrada!\n");
    system("pause");
    return Espera;
}

estados_t f_error(depoGeneral_t depo, char *e, deposito_t *prod){
    char solucion = 'N';// '1'= problema solucionado
    while(!(solucion == 'Y')){
        system("cls");
        printf("*** Asistente de Errores ***\n");
        switch(*e){;
            case 'p':
                printf("Producto desconocido\n");
                solucion = reparoHumano(solucion);
                break;
            case 'm':
                printf("Maquina desconocida\n");
                solucion = reparoHumano(solucion);
                break;
            case 'u':
                printf("Ubicacion del producto desconocida\n");
                solucion = reparoHumano(solucion);
                break;
            case 'c':
                printf("Maquina %d ha sufrido una caida\n",prod->nMaquina);
                solucion = reparoHumano(solucion);
                break;
            case 'b':
                printf("Maquina %d tiene bateria baja\n",prod->nMaquina);
                solucion = reparoHumano(solucion);
                break;
        }
    }
    return Espera;
}

char reparoHumano(char solucion){
    printf("Se ha solucionado el problema? Y/N\n");
    scanf("%c",&solucion);fflush(stdin);
    return toupper(solucion);
}