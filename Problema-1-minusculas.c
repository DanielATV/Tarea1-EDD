#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* nombre funcion: minuscula
  recibe: un puntero a la palabra
  devuelve: el mismo puntero
  que hace: transforma a minuscula todas las letras que esten en mayuscula
  observacion: inclui un main para probarlo y la idea esque en este mismo codigo quitemos los acentos
*/

char *minuscula(char *a){
	int long_palabra = strlen(a);
	char letra;
	/* Dentro del for: 
	recorro letra por letra de la palabra y segun condiciones paso la letra a minuscula */
	for (int i = 0; i < long_palabra; i++){
		letra = (int)a[i];
		if ((65 <= letra) && (letra <= 90)){ /* Pregunta si la letra esta en mayus*/
			letra += 32;
			a[i] = (char)letra;
		}
	}
	return a;
}

/* Para ver que funcione correctamente*/
int main(){
	char palabra[65];
	strcpy(palabra,"RePeTiDAmenTE");
	printf("%s\n",minuscula(palabra));
	return 0;
}
