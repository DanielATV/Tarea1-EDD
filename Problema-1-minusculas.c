#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* nombre funcion: minuscula
  recibe: un puntero a la palabra
  devuelve: el mismo puntero
  que hace: transforma a minuscula todas las letras que esten en mayuscula
  observacion: inclui un main para probarlo y la idea esque en este mismo codigo quitemos los acentos
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
	strcpy(a,aux);
	free(aux);
	return;
}

/* Para ver que funcione correctamente*/
int main(){
	char palabra[65];
	strcpy(palabra,"Ñandú");
	minuscula(palabra);
	printf("%s\n",palabra);
	return 0;
}

