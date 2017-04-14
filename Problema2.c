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
	int caux, caux2,caux3;

	fp = fopen(transacciones,"r");
	if (fp == NULL){
		printf("No se pudo abrir el archivo\n");
		exit(1);
	}
	while (!feof(fp)){
		fscanf(fp,"%c", &aux);
		if ( ( aux == '+') || ( aux == '-')){
			fscanf(fp,"%d %d",&caux,&caux2);
			printf("%d %d\n",caux,caux2);
		}
		else {
			fscanf(fp,"%d %d %d",&caux,&caux2,&caux3);
			printf("%d %d %d\n",caux,caux2,caux3);
		}

	}
	return;
}

int main(int argd,char **argv){
	actualizarSaldos (argv[1], argv[1]);
	return 0;
}
