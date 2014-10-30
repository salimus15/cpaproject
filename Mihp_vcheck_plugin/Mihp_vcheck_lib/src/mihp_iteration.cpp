#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>
#include "tools.h"
#include "mihp_iteration.h"

//#define OFFSET(X) (void *) ((char*)NULL + (X))
//#define OFFSET(X, Y) ((void *)((char*)X + ((char*)NULL + (Y))))


Mihp_Iteration :: Mihp_Iteration(){ 
	
	it = adres_acc.begin();
}
	



void Mihp_Iteration :: CopieIteration (const Mihp_Iteration & other){
	
	adres_acc = other.adres_acc;
	it = adres_acc.begin();
}

Mihp_Iteration :: Mihp_Iteration(const Mihp_Iteration & other){
	CopieIteration(other);
}

Mihp_Iteration :: ~Mihp_Iteration(){}


void Mihp_Iteration :: MihpAddAdr(const Mihp_Adress & new_adr){
	
	adres_acc.push_back(new_adr);	
}


/*
Mihp_Adress Mihp_Iteration :: Mihp_get_next_adr(){
	if(it != adres_acc.end()){
		++it;
		return it;
	}else return NULL;

}
*/
bool Mihp_Iteration :: MihpCheckAdressRecouvrement(const void * a_d1, const void *  a_f1, const void * a_d2, const void * a_f2 ){
	return (((a_d1 >= a_f2)&&(a_d1 <= a_d2)) || ((a_f1 >= a_d2)&&(a_f1 <= a_f2)));
}

bool Mihp_Iteration :: MihpCheckIterRecouvrement(const Mihp_Iteration & other){
	//int i = 0;
	std :: list<Mihp_Adress> ::const_iterator it_other;
	
	
	for(it = adres_acc.begin(); it != adres_acc.end(); ++it){
		
		for (it_other = other.adres_acc.begin(); it_other != other.adres_acc.end(); ++it_other){
			
			if(MihpCheckAdressRecouvrement(it->p_adr,  OFFSET(it->p_adr ,it->data_tsize), \
			it_other->p_adr ,  OFFSET(it_other->p_adr ,it_other->data_tsize))){
				
				return true;
			} 	
		
		}	
	}
	return false;
}
// Mihp_Iteration :: MihpCheckDependencies();
