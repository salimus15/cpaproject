
#include <stdio.h>
#include <stdlib.h>

#include "mihp_vcheck.h"

///fonction de test pour la librairie C++
/**	@param tabFloat : tableau à modifier
 * 	@param size : taille du tableau
*/
void functionTestLoop(float* tabFloat, size_t size){
	if(tabFloat == NULL || size == 0) return;
	size_t i;
	//on dit que c'est la boucle de la ligne 15, de la fonction functionTestLoop définit à la ligne 11 du fichier main.C
	mihp_newLoop("functionTestLoop", "main.c", 15);
	for(i = 0; i < size; ++i){
		tabFloat[i] = 0.0;
		mihp_adress(&tabFloat[i], sizeof(tabFloat[i]), MIHP_WRITE);
		mihp_newIteration();
	}
	mihp_endLoop();
	i = 0;
	//on dit que c'est la boucle de la ligne 15, de la fonction functionTestLoop définit à la ligne 11 du fichier main.C
	mihp_newLoop("functionTestLoop", "main.c", 24);
	while(i < size){
		tabFloat[i] = (float)i;
		mihp_adress(&i, sizeof(i), MIHP_READ);
		mihp_adress(&tabFloat[i], sizeof(tabFloat[i]), MIHP_WRITE);
		++i;
// 		mihp_adress(&i, sizeof(i), MIHP_READ);  //je ne sais pas si le ++ est considéré comme un assignement par Gimple, il faudra faire des tests
// 		mihp_adress(&i, sizeof(i), MIHP_WRITE);
		mihp_newIteration();
	}
	mihp_endLoop();
}

int main(int argc, char** argv){
// 	testFonction(42, "chaîne de caractère");
	size_t size = 5;
	
	float* tabFloat = (float*)malloc(sizeof(float)*size);
	
	functionTestLoop(tabFloat, size);
	
	free(tabFloat);
	
	return 0;
}


