#include <stdio.h>
#include <stdlib.h>
#include <string>

int main(){

	for (int i = 0; i < 5; ++i)
	{
		printf("i = %d\n", i);
	}

	int j = 0;

	while (j < 5 ){

		printf("j = %d\n", j);
		j++;
	}

	int h = 0;

	do{

		if (h == 2){
			printf(" H es 2 ");
		}

		switch(h){

			case 1:
				printf("H es 1 ");
				break;
		}

		printf(" h = %d\n", h);

		h++;

	}while(h < 5);
	

}