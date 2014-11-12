#include "mihp_loop.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "tools.h"


Mihp_Loop :: Mihp_Loop(){ 
	func_name = ""; 
	file_name = ""; 
	loop_nline = 0 ; 
	it = iters.begin(); 
}

void Mihp_Loop :: CopieLoop(const Mihp_Loop & other){
		
	iters = other.iters;
	it = iters.begin();
}



Mihp_Loop :: Mihp_Loop(const Mihp_Loop & other){
	CopieLoop(other);
}



Mihp_Loop :: Mihp_Loop(const std::string & funname, const std::string & filname, const unsigned int & linnumb ){
	func_name = funname;
	file_name = filname;
	loop_nline = linnumb;

}

Mihp_Loop :: ~Mihp_Loop(){}
void Mihp_Loop :: Mihp_add_iter(const Mihp_Iteration & new_iter){
	
	
	iters.push_back(new_iter);
	
}

void Mihp_Loop :: MihpLoopClear(){
	for(it = iters.begin(); it != iters.end(); ++it){
		it->MihpIterationClear();
				
	}
	iters.clear();	
}
/*
Mihp_Iteration Mihp_Loop :: Mihp_get_next_iter(){
	if(it != iters.end()){
		it++;
		return it;
	}else return ;

}
*/

void Mihp_Loop :: Mihp_add_adr( const Mihp_Adress & new_adr){
	it = iters.end();
	it->MihpAddAdr(new_adr);
}


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




// Verifie si il ya des recouverements entre les iterations et verifie si ils empechent la vectorisation ou non.	 
bool Mihp_Loop :: MihpCheckRecouvement(){
	int vector_size = MAX_INT;
	int temp = 0;
	std :: list<Mihp_Iteration> :: iterator other_it;
	//list_dependences dependences = std::list< paire_adr>();
	printfMihp(" On entre da la fonction dAnalyse \n");
	for (it = iters.begin(); it != iters.end(); ++it){
			
		other_it = it;
		++other_it;
		
		while(other_it != iters.end()){
			if(it->MihpCheckIterRecouvrement(*other_it)){
			if(temp < vector_size) 	vector_size = temp;
				printfMihp(" La taille maximale du vecteur est de %d \n", vector_size);	
				printfMihp(" On sort da la fonction dAnalyse \n");
				return true;
			}else{
				temp++;
				++other_it;	
			}
		}
		if(temp < vector_size) 	vector_size = temp;
		temp = 0;
	}
		
		
	printfMihp(" \033[37mBoucle Completement vectorisable\033[0m  \n");	
	printfMihp(" On sort da la fonction dAnalyse \n");
	return false;
}


void Mihp_Loop :: AfficherIterations(){
	int i = 1;
	for (it = iters.begin(); it != iters.end(); ++it){
		printf(" Iteration  %d : \n", i);
		it->AfficherAdresses();
		++i;
	}
}
