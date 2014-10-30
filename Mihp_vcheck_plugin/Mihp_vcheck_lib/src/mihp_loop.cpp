#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>
#include "tools.h"
#include "mihp_loop.h"


Mihp_Loop :: Mihp_Loop(){ 
	func_name = ""; 
	file_name = ""; 
	loop_nline = 0 ; 
	it = iters.begin(); 
}


void Mihp_Loop :: Mihp_add_iter(const Mihp_Iteration & new_iter){
	
	iters.push_back(new_iter);
}
/*
Mihp_Iteration Mihp_Loop :: Mihp_get_next_iter(){
	if(it != iters.end()){
		it++;
		return it;
	}else return ;

}
*/
void Mihp_Loop :: MihpSetFuncName(const std :: string & fname){
	func_name = fname;
}

void Mihp_Loop :: MihpSetFileName(const std :: string & filname){
	file_name = filname;
}

void Mihp_Loop :: MihpSetLineNum(size_t numline){
	loop_nline = numline;

}
/// Fonction qui vérifie si il y a des dépendances entre les itérations de la boucle
void Mihp_Loop :: MihpCheckIterDep(){
	std::list<Mihp_Iteration> :: iterator it_intern;
	
	for(it = iters.begin(); it != iters.end(); ++it){
		it_intern = it;
		//for(it_intern = )
	
	}
}


// Verifie si il ya des recouverements entre les iterations	 
bool Mihp_Loop :: MihpCheckRecouvement(){
return true;
}


