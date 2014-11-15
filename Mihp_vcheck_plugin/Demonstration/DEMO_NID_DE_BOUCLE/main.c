
#include <stdio.h>
#include <stdlib.h>

#include "mihp_vcheck.h"

#pragma mihp vcheck functionAddTab

///fonction qui fait une addititon de deux tableaux, et la renvoie dans un troisième
/**	@param result : résultat de l'addition
 * 	@param a : tableau
 * 	@param b: tableau
 * 	@param sizeLine : nombre de ligne des tableaux
 * 	@param sizeCol : nombre de colonnes des tableaux
*/
void functionAddTab(float * result, const float * a, const float * b, size_t sizeLine, size_t sizeCol){
	if(result == NULL || a == NULL || b == NULL || sizeLine == 0 || sizeCol == 0) return;
	int i,j;
	for(j = 0; j < sizeCol; ++j){
		for(i = 0; i < sizeLine; ++i){
			result[j*sizeLine + i] = a[j*sizeLine +i] + b[j*sizeLine +i]; //pose problème
// 			result[i] = a[i] + b[i];  //fonctionne parfaitement
		}
	}
}

int main(int argc, char** argv){
	size_t sizeLine = 5;
	size_t sizeCol = 3;
	size_t size = sizeLine*sizeCol;
	float * tabResult = malloc(sizeof(float )*size);
	float * tabA = malloc(sizeof(float )*size);
	float * tabB = malloc(sizeof(float )*size);
	
	functionAddTab(tabResult, tabA, tabB, sizeLine, sizeCol);
	
	free(tabResult);
	free(tabA);
	free(tabB);
	
	return 0;
}


