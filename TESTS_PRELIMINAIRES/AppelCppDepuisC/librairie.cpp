

#include "librairie.h"
#include <iostream>
#include <string>

using namespace std;

void fonctionEnCpp(const std::string & str){
	cout << "fonctionEnCpp : str = " << str << endl;
	
	
}


///fonction de test pour voir si on peut appeler du C++ à partir de C
/**	@param param : paramètre simple
*/
void testFonction(int param, const char * str){
	cout << "testFonction : param = " << param << endl;
	
	fonctionEnCpp(str);
	
}

///fonction qui permet de créer une nouvelle boucle
/**	@param functionName : nom de la fonction où se trouve la boucle à analyser
 * 	@param fileName : nom du fichier dans lequel est la fonction
 * 	@param functionLine : ligne de la fonction
 * 	@param loopLine : ligne du début de la boucle que l'on souhaite analyser
*/
void mihp_newLoop(const char* functionName, const char* fileName, size_t functionLine, size_t loopLine){
	
	cout << "mihp_newLoop : In " << fileName << ":" << functionLine << " in Function '" << functionName << "' , Loop:" << loopLine << endl;
	
	
	
}


///fonction qui permet de sauvegarder une lecture ou d'une écriture à une adresse
/**	@param addr : addresse à laquelle on écrit
 * 	@param nbBlock : nombre de blocks que l'on écrit ou que l'on lit
 * 	@param type : 1 si on écrit, 0 si on lit
*/
void mihp_adress(void* addr, size_t nbBlock, char type){
	if(addr == NULL) return;
	if(type == 1) printf("\t\t\tmihp_adress %p Write %lu B\n", addr, nbBlock);
	else printf("\t\t\tmihp_adress %p Read %lu B\n", addr, nbBlock);
}

///fonction qui créée une nouvelle iteration
void mihp_newIteration(){
	cout << "\t\tmihp_newIteration" << endl;
	
}

///fonction qui permet de lancer l'analyse des écritures et des lectures des adresse mémoires
void mihp_endLoop(){
	cout << "\tmihp_endLoop" << endl;
	
	
}

