# TP_MaquinadeEstado-SistemaLastOrder
Un protocolo de comunicación entre maquinas y servidor, realizado con máquina de estado. Cada maquina puede enviar y recibir información, la cual compartirá con el servidor.
## Memoria Descriptiva
El sistema "Last Order", se encarga de la comunicación entre un servidor y varias
Máquinas ubicadas en un depósito. Para ello se implementa un protocolo de 
Comunicación unico del sistema.

El servidor recibe informes de estado de las maquinas y dependiendo de estos ejecuta "Almacenamiento" osea lleva la caja a su destino seteado para luego dirigirse a su ubicación inicial. 

Entonces, el servidor, esperará hasta que la máquina termine de llevar el producto hacia su sitio y luego repetirá el proceso con otra máquina.
En el transcurso de cualquier tarea, las maquinas envian cada 5 segundos, un informe de estado de la respectiva máquina. Este informe contiene "Caida" y "Bateria baja". Si envian una señal alta de alguno de estos estados, el proceso de "Almacenamiento " se detiene, para ser reanudado por algún Humano.

### Funciones
- **Inicio** : Las máquinas se dirigen en una posicion inicial cualquiera. El SET consiste en dar un orden del almacenamiento de las cajas segun su tipo, en los lugares correspondientes del depósito.  

- **Espera** : En dicha posición cada máquina scanea un código impreso en la caja y envia sus características al Servidor. Estas son *Tamaño* y *Tipo de producto*. En el caso de no recibir nada, el sistema sigue en fase de *Iddle*. Pero al recibir dichas características, enviará las instrucciones necesarias para que la máquina deposite la caja en su lugar correspondiente.
> Pueden agregarse más características, pero la idea es que hay cajas diferentes.
- **Almacenar** : La máquina se moverá hacia la *Ubicación final* para almacenar la caja. Una vez realizada la tarea, se la informa al Servidor.

- **Ir Ubicacion Inicial** : Consiste en la vuelta de la máquina hacia la zona de cajas donde realizará el mismo proceso ya dicho.

- **Reparo Humano** : Este sucede cuando alguna máquina sufrió algun tipo de accidente o desperfecto, como caída, baja bateria, etc. Errores los cuales debe revisar un técnico o encargado del depósito.

> Los errores aparecen en los informes de estado.

## Máquina de Estado
![./Recursos/maquinaestado.png](https://github.com/TobiasMoscoso/TP_MaquinadeEstado-ProtocoloLastOrder/blob/master/Recursos/maquinaestado.png)
