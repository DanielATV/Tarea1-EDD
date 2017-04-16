#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
	int nroCuenta;
	int saldo;
	char nbre[51];
	char direccion[51];	
} clienteBanco;

/*****
* int buscar
******
* Busca el indice de la estructura desada en el arreglo con todas las estructuras del archivo clientes, mediante busqueda binaria.
******
* Input:
* clienteBanco *clientes : Puntero al arreglo de estructras de los clientes.
* int cuenta : Cuenta que hay que buscar en el arreglo.
* int largo : Largo del arreglo.
******
* Returns:
* int, retorna un valor entero del indice de la estructura en el arreglo, en el caso de no encontarlo retorna -1.
*****/

int buscar(clienteBanco *clientes,int cuenta,int largo){
	int index;
	int medio,limsup,liminf;
	index = -1;
	liminf = 0;
	limsup = largo - 1;
	while(liminf <= limsup){

		medio = liminf + ( limsup - liminf) / 2;
		if (clientes[medio].nroCuenta == cuenta){
			index = medio;
			break;
		}
		else{
			if(clientes[medio].nroCuenta < cuenta){
				liminf = medio + 1;
			}
			else{
				limsup = medio -1;
			}
		}
	}
	return index;

}

/*****
* void abonar
******
* Utiliza la funcion buscar para encontrar la cuenta en el arreglo de estructuras para luego sumarle el monto indicado a su saldo.
******
* Input:
* clienteBanco *clientes : Puntero al arreglo de estructras de los clientes.
* int cuenta : Cuenta que hay que buscar en el arreglo.
* int monto: Monto que hay que sumarle al saldo.
* int largo : Largo del arreglo.
******
* Returns:
* void, actualiza el saldo de la estructura del arreglo.
*****/

void abonar(clienteBanco *clientes,int cuenta, int monto,int largo){
	int i;
	i = buscar(clientes,cuenta,largo);
	if(i == -1) printf("No se enconto la cuenta %d\n",cuenta);
	clientes[i].saldo += monto;
	return;
}

/*****
* void restar
******
* Utiliza la funcion buscar para encontrar la cuenta en el arreglo de estructuras para luego restarle el monto indicado a su saldo.
******
* Input:
* clienteBanco *clientes : Puntero al arreglo de estructras de los clientes.
* int cuenta : Cuenta que hay que buscar en el arreglo.
* int monto: Monto que hay que restarle al saldo.
* int largo : Largo del arreglo.
******
* Returns:
* void, actualiza el saldo de la estructura del arreglo.
*****/

void restar(clienteBanco *clientes,int cuenta, int monto,int largo){
	int i;
	i = buscar(clientes,cuenta,largo);
	if(i == -1) printf("No se enconto la cuenta %d\n",cuenta);
	clientes[i].saldo -= monto;
	return;
}

/*****
* void transferencia
******
* Le resta un monto a una cuenta del arreglo de estructuras y le suma el mismo monto a otra cuenta del arreglo de estructuras.
******
* Input:
* clienteBanco *clientes : Puntero al arreglo de estructras de los clientes.
* int cuenta : Cuenta que se le resta el monto.
* int cuenta2 : Cuenta que se le suma el monto.
* int monto: Monto que hay que restarle al saldo.
* int largo : Largo del arreglo.
******
* Returns:
* void, actualiza los saldos de las estructuras del arreglo.
*****/

void transferencia(clienteBanco *clientes,int cuenta,int cuenta2, int monto,int largo){
	restar(clientes,cuenta,monto,largo);
	abonar(clientes,cuenta2,monto,largo);		
	return;
}

/*****
* void actualizarSaldos
******
* Primero lee todas las estructuras del archivo binario y las guarda en un arreglo que crece de manera dinamica,luego a medida que
* lee las operaciones del archivo transacciones las efectua sobre las estructuras del arreglo. Finalmente abre el archivo de clientes en
* w y escribe todas las estructuras del arreglo.
******
* Input:
* char *clientes: String que representa el nombre de un archivo binario, el cual contiene una cantidad arbitraria
* de structs de tipo clienteBanco. El archivo está ordenado de forma creciente por nroCuenta.
* char *transacciones: String que representa el nombre de un archivo con formato ASCII, el cual contiene transacciones
* hechas por los clientes. Cada transacción corresponde a una línea del archivo.
******
* Returns:
* void, actualiza el archivo de clientes al efectuarle todas las operaciones del archivo transacciones.
*****/

void actualizarSaldos(char *clientes, char *transacciones){
	FILE *fp;
	int caux, caux2,caux3,i,j,cont;
	char aux[100];
	char aux2;
	i = 0;
	cont = 0;
	clienteBanco *temp;
	
	fp = fopen(clientes,"r");
	if (fp == NULL){
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
	temp = (clienteBanco *)malloc(sizeof(clienteBanco));

	if (temp == NULL){
		printf("No se pudo asignar memoria\n");
		exit(1);
	}
	
	fread(temp,sizeof(clienteBanco),1,fp);
	
	while(!feof(fp)){
		i++;
		
		temp = (clienteBanco *)realloc(temp,(i+1)*sizeof(clienteBanco));
		if (temp == NULL){
			printf("No se pudo asignar memoria\n");
		}
		cont++;
		fread(&temp[cont],sizeof(clienteBanco),1,fp);
		
	}
	
	fclose(fp);

	fp = fopen(transacciones,"r");
	if (fp == NULL){
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
	
	while (fgets(aux,sizeof(aux),fp)){
		j = sscanf(aux,"%c %d %d %d", &aux2,&caux,&caux2,&caux3);

		if( j == 3){
			if( aux2 == '+')abonar(temp,caux,caux2,i);
			else restar(temp,caux,caux2,i); 
			
		}
		else if( j == 4){
			if( aux2 == '>') transferencia(temp,caux,caux2,caux3,i);
			
		}
		else if( j == 0){
			printf("No se pudo leer linea\n");
			exit(1);
		}
	}


	fclose(fp);
	fp = fopen(clientes,"w");

	for(j = 0; j<i;j++){
		fwrite(&temp[j],sizeof(clienteBanco),1,fp);
	}
	fclose(fp);
	free(temp);

	return;
	
}



int main(int argc,char **argv){


	actualizarSaldos(argv[1],argv[2]);
	return (0);
}
