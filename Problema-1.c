#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*Integrantes: 
Nombre: Fabián Ignacio Jiménez Olivares
Rol: 201673503-8,
Paralelo:200
Nombre Daniel Toro
Rol:
Paralelo: 200
Nomre: Sebastian Danilo Godinez San Martin
Rol: 201673520-8
Paralelo: 200*/

/* nombre funcion: void minuscula
  recibe: char *a:un puntero a la palabra
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

/* nombre funcion:int comparacion
  recibe: char *arreglo, char *palabra :dos arreglos (basicamente dos palabras)
  devuelve: int 1 o 0 dependiendo si son anagramas o no
  que hace: en dos arreglos de int temporales almacena la cantidad de caracteres que tiene cada palabra
  luego compara si los 2 arreglos son el mismo o no
*/

int comparacion(char *arreglo, char *palabra){
	/* los arreglos son 26 porque corresponde a la cantidad de letras en el abcedario
	y los llenamos de 0*/
   int first[26] = {0}, second[26] = {0}, i = 0;
 	
 	/* aca hace la cuenta para las 2 palabras*/
   for(i = 0; arreglo[i] != '\0'; i++) first[arreglo[i]-'a']++;

   for(i = 0; palabra[i] != '\0'; i++) second[palabra[i]-'a']++;

 	/*aca compara los 2 arreglos generados */
   for (i = 0; i < 26; i++) if (first[i] != second[i]) return 0; /* si no son iguales retorna 0*/

   return 1;
}


/* nombre funcion:int anagramas
  recibe:char** S :un arreglo de strings(el string es basicamente un arreglo de char), int n: un entero que dice lo grande que es
   el arreglo y char *str: la palabra para comparar
  devuelve: int total: cantidad de palabras que son anagramas con palabra
  que hace: llama a comparacion y va sumando al contador si son iguales
*/
int anagramas(char **S,int n, char *str)
{

	int total = 0;
	for (int i =0;i<n;i++) total += comparacion(S[i],str);

	return total;
}

/* nombre funcion: int main
  recibe: int argv:un entero(no se usa) y char **argc:un arreglo con palabras
  devuelve: int 0: por convenio
  que hace: lee el archivo, luego de pedir memoria para n elementos los guarda en un arreglo de arreglos
  luego lee m veces y compara con la funcion anagramas
*/


int main(int argv, char **argc){
	FILE *fp, *new;
	int n, m, i;
	char **N, aux1[200];

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
	N = (char **)calloc(n,sizeof(char*));
	if(N == NULL){
		printf("Error al pedir memoria\n");
		exit(1);
	}
	for(i = 0; i < n; i++){
		N[i] = (char *)calloc(200,sizeof(char));
		if(N[i] == NULL){
			printf("Error al pedir memoria\n");
			exit(1);
		}
	}
	
	/*Ahora los guardo */
	for(i = 0; i < n; i++ ){
		if(fscanf(fp,"%s",N[i])){
			printf("Error al leer el archivo\n");
			exit(1);
		}
		minuscula(N[i]);
	}

	/*Ahora mientras vemos cada linea, vemos si es anagrama*/
	if(fscanf(fp,"%d",&m) == 0){
		printf("Error al leer la linea\n");
		exit(1);
	}

	/* se crea el archivo resultante */
	new = fopen("salida-1.txt","w+");
	if(new == NULL){
		printf("Error al crear el archivo\n");
		exit(1);
	}

	for(i = 0; i < m; i++){

		if(fscanf(fp,"%s",aux1)){
			printf("Error al leer el archivo\n");
			exit(1);
		}

		minuscula(aux1);

		fprintf(new, "%d\n",anagramas(N,n,aux1)); 
	}

	fclose(fp);
	fclose(new);
	/*for(i = 0; i<n; i++) free(N[i]); lo comentamos porque tira error juntos o separados
	free(N); */
	printf("Listo!\n");

	return 0;

}

/* ACA ESTA EL DE 30 SEGUNDOS,OCUPA MUCHOS RECURSOS */

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
int anagramas(int **arreglo,int n, char *palabra)
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


int main(int argv, char **argc){
	FILE *fp, *new;
	int n, m, i;
	char **N, aux1[201];
	int **TEST;

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
	N = (char **)calloc(n,sizeof(char *));
	if(N == NULL){
		printf("Error al pedir memoria\n");
		exit(1);
	}
	for(i = 0; i < n; i++)N[i] = (char *)calloc(201,sizeof(char));

	TEST = (int **)malloc(sizeof(int *)*n);
	for(i = 0; i < n; i++)TEST[i] = (int *)malloc(26*sizeof(int));

	/*Ahora los guardo */
	for(i = 0; i < n; i++ ){
		fscanf(fp,"%s",N[i]);
		cantcara(N[i],TEST[i]);
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

	fclose(fp);
	fclose(new);

	printf("Listo!\n");

	return 0;

}
