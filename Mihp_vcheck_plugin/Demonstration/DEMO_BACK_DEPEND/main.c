
#include <stdio.h>
#include <stdlib.h>

#include "mihp_vcheck.h"

#pragma mihp vcheck (functionDependTest,functionDependTest1)

///fonction qui fait des calculs sur des tableaux avec une dépendance arrière, la boucle est non vectorisable
/**	@param a : tableau
 * 	@param d : tableau
 * 	@param b: tableau
 * 	@param c : tableau
 * 	@param e : tableau
 * 	@param size : taille des tableaux
*/
void functionDependTest(float* a, float* d, const float* b, const float* c, const float * e, size_t size){
	if(a == NULL || b == NULL || c == NULL || d == NULL || e == NULL || size == 0) return;
	int i;
	for( i = 1; i < size; ++i){
		d[i] = e[i] - a[i - 1];
		a[i] = b[i] + c[i];
	}
}


///fonction qui fait des calculs sur des tableaux avec une dépendance arrière, la boucle est vectorisable.
/**	@param a : tableau
 * 	@param d : tableau
 * 	@param b: tableau
 * 	@param c : tableau
 * 	@param e : tableau
 * 	@param size : taille des tableaux
*/
void functionDependTest1(float* a, float* d, const float* b, const float* c, const float * e, size_t size){
	if(a == NULL || b == NULL || c == NULL || d == NULL || e == NULL || size == 0) return;
	int i;
	for( i = 1; i < size; ++i){
		d[i] = e[i] - a[i];
		a[i] = b[i] + c[i];
	}
}

int main(int argc, char** argv){
	size_t size = 5;
	
	float* tabA = malloc(sizeof(float)*size);
	float* tabB = malloc(sizeof(float)*size);
	float* tabC = malloc(sizeof(float)*size);
	float* tabD = malloc(sizeof(float)*size);
	float* tabE = malloc(sizeof(float)*size);
	
	functionDependTest(tabA, tabD, tabB, tabC, tabE, size);
	functionDependTest1(tabA, tabD, tabB, tabC, tabE, size);
	free(tabA);
	free(tabB);
	free(tabC);
	free(tabD);
	free(tabE);
	
	return 0;
}

