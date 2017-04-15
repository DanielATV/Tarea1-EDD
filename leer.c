#include <stdio.h>
typedef struct {
	int nroCuenta;
	int saldo;
	char nbre[51];
	char direccion[51];	
} clienteBanco;

int main(){
	FILE *fp;
	clienteBanco aux;
	fp = fopen("clientes.dat","r");
	while(1){

		if(fread(&aux,sizeof(clienteBanco),1,fp)!=1){
			break;
		}
		else printf("%d\n",aux.saldo);
	}
	fclose(fp);
	return (0);


}