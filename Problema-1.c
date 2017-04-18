#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* nombre funcion: minuscula
  recibe: un puntero a la palabra
  devuelve: nada
  que hace: transforma a minuscula todas las letras que esten en mayuscula, usando el mismo
  arreglo, 
*/

void minuscula(char *a){
	int  j, i; /* j = cantidad del nuevo arreglo */
	
	/* Dentro del for: 
	recorro letra por letra de la palabra y segun condiciones paso la letra a minuscula */
	for (i = 0, j = 0; a[i] != '\0'; i++){
		if ((65 <= a[i]) && (a[i] <= 90)){ /* Pregunta si la letra esta en mayus*/
			a[j++] = a[i] + 32;
		}

		/* Aca estan las condiciones para el resto de letras raras */
		else if(a[i] == -61){ /* todas las letras raras empieza con -61 */
			if (a[i+1] == -95 || a[i+1] == -127){
				a[j++] = 'a';
			}
			else if (a[i+1] == -87 || a[i+1] == -119){
				a[j++] = 'e';
			}
			else if(a[i+1] == -83 || a[i+1] == -115){
				a[j++] = 'i';
			}
			else if(a[i+1] == -77 || a[i+1] == -109){
				a[j++] = 'o';
			}
			else if(a[i+1] == -70 || a[i+1] == -102){
				a[j++] = 'u';
			}
			++i;
		}
		else{
			a[j++] = a[i];
		}
	}

	a[j] = '\0';
	return;
}

void cantcara(char *palabra ,int *cantidad){
	int i;
	minuscula(palabra);

	for(i = 0; palabra[i] != '\0'; i++) cantidad[palabra[i]-'a']++;
	return;
}

int check_anagram(int *arreglo, int *palabra)
{
   int c;
 
   for (c = 0; c < 26; c++) if (arreglo[c] != palabra[c]) return 0;

   return 1;
}


/* nombre funcion: anagramas
  recibe: un arreglo de strings(arreglo de char), un entero que dice lo grande que es el arreglo
  y la palabra para comparar
  devuelve: cantidad de palabras que son anagramas con palabra
  que hace: llama a iguales el cual recorre ambos strings y ve si son iguales en codigo ascii
*/
int anagramas(void **arreglo,int n, char *palabra)
{
	int total = 0 , cantpalabra[26] = {0};

	cantcara(palabra, cantpalabra);
	for (int i =0;i<n;i++){
		if (check_anagram(arreglo[i],cantpalabra))
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


int main(int argv, char *argc[]){
	int n, m, i;
	char aux1[201];
	FILE *fp, *new;
	void **TEST;

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
	TEST = calloc(n,sizeof(int *));
	for(i = 0; i < n; i++)TEST[i] = (int *)calloc(26,sizeof(int));

	/*Ahora los guardo */
	for(i = 0; i < n; i++ ){
		fscanf(fp,"%s",aux1);
		cantcara(aux1,TEST[i]);
	}
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

		fscanf(fp,"%s",aux1);

		fprintf(new, "%d\n",anagramas(TEST,n,aux1)); 
	}

	
	for(i =  n-1; i > -1; i--) free((void *)TEST[i]);
	free(TEST);

	fclose(fp);
	fclose(new);
	printf("Listo!\n");

	return 0;

}
