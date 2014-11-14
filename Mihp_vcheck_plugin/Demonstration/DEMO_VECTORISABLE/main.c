
#include <stdio.h>
#include <stdlib.h>

#include "mihp_vcheck.h"

#pragma mihp vcheck functionAddTab

///fonction qui fait une addititon de deux tableaux, et la renvoie dans un troisième
/**	@param result : résultat de l'addition
 * 	@param a : tableau
 * 	@param b: tableau
 * 	@param size : taille des tableaux
*/
void functionAddTab(float* result, const float* a, const float* b, size_t size){
	if(result == NULL || a == NULL || b == NULL || size == 0) return;
	int i;
	for(i = 0; i < size; ++i){
		result[i] = a[i] + b[i];
	}
}

int main(int argc, char** argv){
	int size = 5;
	
	float* tabResult = malloc(sizeof(float)*size);
	float* tabA = malloc(sizeof(float)*size);
	float* tabB = malloc(sizeof(float)*size);
	
	functionAddTab(tabResult, tabA, tabB, size);
	
	free(tabResult);
	free(tabA);
	free(tabB);
	
	return 0;
}


