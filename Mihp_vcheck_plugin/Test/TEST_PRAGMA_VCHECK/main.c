
#include <stdio.h>
#include <stdlib.h>

#include "mihp_vcheck.h"

// #pragma mihp vcheck functionTestLoop
#pragma mihp vcheck functionAddTab
// #pragma mihp vcheck (functionTestLoop,functionWithoutLoop)

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


///fonction de test pour la librairie C++
/**	@param tabFloat : tableau à modifier
 * 	@param size : taille du tableau
*/
void functionTestLoop(float* tabFloat, size_t size){
	if(tabFloat == NULL || size == 0) return;
	int i;
	//on dit que c'est la boucle de la ligne 18, de la fonction functionTestLoop du fichier main.C
	for(i = 0; i < size; ++i){
		tabFloat[i] = 0.0;
	}
	i = 0;
	//on dit que c'est la boucle de la ligne 23, de la fonction functionTestLoop du fichier main.C
	while(i < size){
		tabFloat[i] = (float)i;
		++i;
	}
}

///fonction sans boucle
void functionWithoutLoop(){
	printf("Empty\n");
}

int main(int argc, char** argv){
// 	testFonction(42, "chaîne de caractère");
	size_t size = 5;
	
	float* tabFloat = malloc(sizeof(float)*size);
	
	functionTestLoop(tabFloat, size);
	
	free(tabFloat);
	
	return 0;
}


