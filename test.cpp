#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){

	char * caracteres = (char*) malloc(256*sizeof(char));

	unsigned int size = 1024;
	unsigned char * template_huella = (unsigned char *) malloc(size * sizeof (unsigned char) );

	memcpy(caracteres, (char*) "Caracteres", 256 * sizeof (char) );

	printf("%s\n", caracteres);
	
	free(caracteres);
	free(template_huella);

}