#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
	int nroCuenta;
	int saldo;
	char nbre[51];
	char direccion[51];	
} clienteBanco;

void actualizarSaldos(char *clientes, char *transacciones){
	FILE *fp;
	char aux;
	int caux, caux2,caux3,i,cont;
	i = 1;
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
		
		temp = (clienteBanco *)realloc(temp,i*sizeof(clienteBanco));
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
	
	
	while (!feof(fp)){
		i = fscanf(fp,"%c %d %d %d", &aux,&caux,&caux2,&caux3);

		if( i == 3){
			printf("%c %d %d\n", aux,caux,caux2);
		}
		else if( i == 4){
			printf("%c %d %d %d\n", aux,caux,caux2,caux3);
		}
		else if( i == 0){
			printf("No se pudo leer linea\n");
			exit(1);
		}
		
	}
	fclose(fp);
	return;
	
}
int main(int argd,char **argv){
	actualizarSaldos (argv[1], argv[1]);
	return 0;
}
