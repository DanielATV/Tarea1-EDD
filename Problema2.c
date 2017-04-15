#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct {
	int nroCuenta;
	int saldo;
	char nbre[51];
	char direccion[51];	
} clienteBanco;

void abonar(clienteBanco *clientes,int cuenta, int monto,int largo){
	int i,flag;
	flag = 1;

	for(i = 0; i<largo; i++){
		if(flag ==1 && clientes[i].nroCuenta == cuenta){
			clientes[i].saldo += monto;
			flag = 0;
		}
		else if (flag == 0)break;
	}
	if (flag == 1) printf("No existe el usuario %d\n",cuenta);
	return;
}

void restar(clienteBanco *clientes,int cuenta, int monto,int largo){
	int i,flag;
	flag = 1;
	for(i = 0; i<largo; i++){
		if(flag ==1 && clientes[i].nroCuenta == cuenta){
			clientes[i].saldo -= monto;
			flag = 0;			
		}
		else if (flag == 0)break;
	}
	if (flag == 1) printf("No existe el usuario %d\n",cuenta);	
	return;
}

void transferencia(clienteBanco *clientes,int cuenta,int cuenta2, int monto,int largo){
	int i,flag,flag2;
	flag = 1;
	flag2 = 1;
	for(i=0; i < largo; i++){
		if ( flag == 1 && clientes[i].nroCuenta == cuenta){
			clientes[i].saldo -= monto;
			flag = 0;
		}
		else if (flag2 == 1 && clientes[i].nroCuenta == cuenta2){
			clientes[i].saldo += monto;
			flag2 = 0;
		}
		else if( flag != 1 && flag2 != 1) break;
	}
	if (flag == 1) printf("No existe el usuario %d\n",cuenta);
	if (flag2 == 1) printf("No existe el usuario %d\n",cuenta2);		
	return;
}

void actualizarSaldos(char *clientes, char *transacciones){
	FILE *fp;
	char aux;
	int caux, caux2,caux3,i,j,cont;
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
	
	
	while (!feof(fp)){
		j = fscanf(fp,"%c %d %d %d", &aux,&caux,&caux2,&caux3);

		if( j == 3){
			if( aux == '+') abonar(temp,caux,caux2,i);
			else restar(temp,caux,caux2,i);
		}
		else if( j == 4){
			transferencia(temp,caux,caux2,caux3,i);
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
