################
Para el Problema 1, lo hicimos en base a los primeros archivos enviados, es decir, para UTF-8, eso pos saludos.
################

Funciones extra no utilizadas:

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

/* nombre funcion: ordenar arreglo de palabras
  recibe: un puntero a un arreglo
  devuelve: nada
  que hace: transforma a minuscula y ordena todas las palabras
  que estan en el arreglo
*/
/
void ordenarArregloS(char *A, int cant){
	int i;
	for(i = 0, i < n, i++){
		minuscula(N[i]);
		ordenarpalabra(N[i]);
	}
}
/* nombre funcion: *convertir_int_palabra_ordenada
  recibe: un puntero int
  devuelve: puntero char
  que hace: al arreglo que conctiene el numero de letras lo escribe en orden ascendente
*/

char *convertir_int_palabra_ordenada(int *letras){
	//printf("asdasdas\n");
	int totletras=0;
	for (int i=0;i<26;i++){
		totletras += letras[i];
		
	}	
	char *palabra = (char *)malloc(sizeof(char)*totletras);
	int j=0;
	while (j < totletras){
		printf("%d\n",j);
	for (int i =0; i<26;i++)
	{	
		if (letras[i] !=0)
			for(int l =0;l<letras[i];l++)
			{
			palabra[j] = i+65;
			j+=1; 
			
			}

	}
	}
	
	return palabra;
}

/* nombre funcion: convertir_palabra_desordenada_int
  recibe: un puntero char
  devuelve: puntero int
  que hace: retorna el arreglo de tamano 26 que dice cuantas letras hay desde la 'a' a la 'z'
*/

int *convertir_palabra_desordenada_int(char *palabra){
	int largopal = strlen(palabra);
	int *final;
	final = (int *)malloc(sizeof(int)*26);

	for (int i=0;i<26;i++){
		final[i] = 0;
	}

	for(int i=0;i<largopal;i++){
		//printf("%d\n",(int)palabra[i]-97);
		final[(int)palabra[i]-97] +=1;
	}

	return final;

}
