#include "mihp_loop.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "tools.h"

using namespace std;

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
	int vectorSize = MAX_INT;
	int temp = 1;
	bool therIsDependance = false;
	std :: list<Mihp_Iteration> :: iterator otherIt;

	//printfMihp(" On entre da la fonction dAnalyse \n");
#ifndef NDEBUG
	cout << " Analyse de la boucle a la ligne"<< loop_nline <<" de la fonction" <<func_name<< "du fichier " <<  file_name << endl;

#endif	
	for (it = iters.begin(); it != iters.end(); ++it){
			
		otherIt = it;
		++otherIt;  /* on compare bien avec les iteration a partir de la suivante */		
	
		while(otherIt != iters.end()){	
			/* on teste si il y a une dependances bloquante */ 
			if(it->MihpCheckIterRecouvrement(*otherIt)){
				therIsDependance = true;
				if(temp < vectorSize) 	vectorSize = temp;
				if(vectorSize <= 1){
	
					cout << " la boucle a la ligne"<< loop_nline <<" de la fonction " << func_name<< " du fichier " << endl << file_name << " est non vectorisable"<<endl;
					return false;
	
				}else{
					break;
				}
			//return false;
			}else{
				temp++;
				++otherIt;	
			}
		}
	
		if(temp < vectorSize) 	vectorSize = temp;
		temp = 1;
	
	}
	if( therIsDependance == true){
		if( vectorSize > 1){
			cout << " La taille maximale du vecteur est de" << vectorSize << endl;
		
		}else{
			cout << " la boucle a la ligne"<< loop_nline <<" de la fonction " << func_name<< " du fichier " << endl << file_name << " est non vectorisable"<<endl;
			return false;
		}	
	} else{	
		cout <<" \033[37mBoucle Completement vectorisable\033[0m : Line  " << loop_nline << " function " << func_name << endl <<"\t file " << file_name<< endl;	
		printfMihp(" On sort da la fonction dAnalyse \n");
		return true;
	}
	return true;
}


void Mihp_Loop :: AfficherIterations(){
	int i = 1;
	for (it = iters.begin(); it != iters.end(); ++it){
		printf(" Iteration  %d : \n", i);
		it->AfficherAdresses();
		++i;
	}
}
