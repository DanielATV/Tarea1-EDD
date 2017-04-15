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
	int caux, caux2,caux3,i;
	caux3 = 0;
	
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
		
	}
	return;
}

int main(int argd,char **argv){
	actualizarSaldos (argv[1], argv[1]);
	return 0;
}
