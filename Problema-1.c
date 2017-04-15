#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* nombre funcion: minuscula
  recibe: un puntero a la palabra
  devuelve: nada
  que hace: transforma a minuscula todas las letras que esten en mayuscula
*/

void minuscula(char *a){
	int long_palabra = strlen(a), j, i; /* j = cantidad del nuevo arreglo */
	char *aux;
	aux = (char *)malloc(sizeof(char)*long_palabra);

	/* Dentro del for: 
	recorro letra por letra de la palabra y segun condiciones paso la letra a minuscula */
	for (i = 0, j = 0; i < long_palabra; i++){
		if ((65 <= a[i]) && (a[i] <= 90)){ /* Pregunta si la letra esta en mayus*/
			a[i] += 32;
			aux[j++] = a[i];
		}
		/* Aca estan las condiciones para el resto de letras raras */
		else if(a[i] == -61){ /* todas las letras raras empieza con -61 */
			if (a[i+1] == -95 || a[i+1] == -127){
				aux[j++] = 'a';
			}
			else if (a[i+1] == -87 || a[i+1] == -119){
				aux[j++] = 'e';
			}
			else if(a[i+1] == -83 || a[i+1] == -115){
				aux[j++] = 'i';
			}
			else if(a[i+1] == -77 || a[i+1] == -109){
				aux[j++] = 'o';
			}
			else if(a[i+1] == -70 || a[i+1] == -102){
				aux[j++] = 'u';
			}
			else{ /* como no consideraremos ninguna letra mas, la ultima sera ñ */
				aux[j++] = '{';
			}
			++i;
		}
		else{
			aux[j++] = a[i];
		}
	}
	aux[j] = '\0';
	strcpy(a,aux);
	free(aux);
}

/* nombre funcion: ordenar palabra
  recibe: un puntero a una palabra
  devuelve: nada
  que hace: ordena las palabras en orden inverso al abcedario
*/

void ordenarpalabra(char *a){
	int n= strlen(a);
	int i,j,aux;

	for(i=0;i<=n-1;i++){
		for(j=0;j<n-1-i;j++){
			if(a[j]<a[j+1]){
				aux = a[j];
				a[j] = a[j+1];
				a[j+1] = aux;
			}
		}
	}
}

/* Las siguientes 3 funciones son para anagrama */

int iguallargo(char *pal1,char *pal2){
	if (strlen(pal1)==strlen(pal2))
		return 1;
	else	return 0;
}
int iguales(char *pal1,char *pal2){

	if (iguallargo(pal1,pal2) ==1){
		int n = strlen(pal1);
		for (int i=0;i<n;i++){
			if (pal1[i] != pal2[i])
				return 0;

		}
		return 1;
	}
	else	return 0;
}


int anagramas(char **S,int n, char *str)
{

	int total = 0;
	for (int i =0;i<n;i++){
		if (iguales(S[i],str))
			total +=1;

	}
	return total;
}

/* nombre funcion: ordenar arreglo de palabras
  recibe: un puntero a un arreglo
  devuelve: nada
  que hace: transforma a minuscula y ordena todas las palabras
  que estan en el arreglo
*/

void ordenarArregloS(char **A, int cant){
	int i;
	for(i = 0; i < cant; i++){
		minuscula(A[i]);
		ordenarpalabra(A[i]);
	}
}




int main(int argv, char **argc){
	FILE *fp, *new;
	int n, m, i;
	char **N, aux[200];

	/* Abre el archivo, si hay error termina
	el proceso*/
	fp = fopen(argc[1],"r");
	if(fp == NULL){
		printf("Error al abrir el archivo\n");
		exit(1);
	}

	/* Guardo el numero de la primera cantidad de numeros*/

	if(fscanf(fp,"%d",&n) == 0){
		printf("Error al leer la linea\n");
		exit(1);
	}

	/* Creo el arreglo para la primera cantidad de numeros*/
	N = (char **)malloc(sizeof(char*)*n);
	for(i = 0; i < n; i++) N[i] = (char *)malloc(sizeof(char)*200);

	/*Ahora los guardo */
	for(i = 0; i < n; i++ ){
		fscanf(fp,"%s",N[i]);
	}

	/* aplicamos los cambios al arreglo */
	ordenarArregloS(N,n);

	/*Ahora mientras vemos cada linea, vemos si es anagrama*/
	if(fscanf(fp,"%d",&m) == 0){
		printf("Error al leer la linea\n");
		exit(1);
	}

	/* creo el archivo resultante */
	new = fopen("salida-1.txt","w+");
	if(new == NULL){
		printf("Error al crear el archivo\n");
		exit(1);
	}
	for(i = 0; i < m; i++){
		fscanf(fp,"%s",aux);
		fprintf(new, "%d\n",anagramas(N,n,aux)); 
	}

	fclose(fp);
	fclose(new);
	free(N);
	return 0;

}