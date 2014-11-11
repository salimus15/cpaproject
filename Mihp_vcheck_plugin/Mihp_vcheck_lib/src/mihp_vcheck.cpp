
#include "mihp_vcheck.h"
#include <iostream>
#include <string>
#include "mihp_loop.h"
#include "mihp_iteration.h"
#include "mihp_adress.h"

Mihp_Adress adress_util = Mihp_Adress();
Mihp_Iteration iteration_util = Mihp_Iteration();
Mihp_Loop loop_util = Mihp_Loop();

#ifndef NDEBUG
#	define printMihpIO(X) std::cout << X << std::endl;
#	define printfMihp(X, ...) printf(X, ##__VA_ARGS__)
#else
#	define printMihpIO(X)
#	define printfMihp(X, ...)
#endif

using namespace std;

void fonctionEnCpp(const std::string & str){
	printMihpIO("fonctionEnCpp : str = " << str);
}


///fonction de test pour voir si on peut appeler du C++ à partir de C
/**	@param param : paramètre simple
*/
void testFonction(int param, const char * str){
	printMihpIO("testFonction : param = " << param);
	
	fonctionEnCpp(str);
	
}

///fonction qui permet de créer une nouvelle boucle
/**	@param functionName : nom de la fonction où se trouve la boucle à analyser
 * 	@param fileName : nom du fichier dans lequel est la fonction
 * 	@param loopLine : ligne du début de la boucle que l'on souhaite analyser
*/
void mihp_newLoop(const char* functionName, const char* fileName, size_t loopLine){
	
	printMihpIO("mihp_newLoop : In " << fileName << ": in Function '" << functionName << "' , Loop:" << loopLine);
	
	
	
}


///fonction qui permet de sauvegarder une lecture ou une écriture à une adresse
/**	@param addr : addresse à laquelle on écrit ou lit
 * 	@param nbBlock : nombre de blocks que l'on écrit ou que l'on lit
 * 	@param type : 1 si on écrit, 0 si on lit
*/
void mihp_adress(void* addr, size_t nbBlock, int type){
	if(addr == NULL) return;
	if(type == 1){
		printfMihp("\t\t\tmihp_adress %p Write %lu B\n", addr, nbBlock);
		
	}else{
		printfMihp("\t\t\tmihp_adress %p Read %lu B\n", addr, nbBlock);
		
	}
	adress_util = Mihp_Adress(addr, nbBlock, type);
	iteration_util.MihpAddAdr(adress_util);
}

///fonction qui créée une nouvelle iteration
void mihp_newIteration(){
	printMihpIO("\t\tmihp_newIteration");
	loop_util.Mihp_add_iter(iteration_util);
	iteration_util.MihpIterationClear();
}

///fonction qui permet de lancer l'analyse des écritures et des lectures des adresse mémoires
void mihp_endLoop(){
	printMihpIO("\tmihp_endLoop");
//	loop_util.MihpCheckRecouvement();
	loop_util.AfficherIterations();
}

