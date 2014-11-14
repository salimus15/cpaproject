#include "mihp_iteration.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "tools.h"


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

void Mihp_Iteration :: MihpIterationClear(){adres_acc.clear();}
void Mihp_Iteration :: MihpAddAdr(const Mihp_Adress & new_adr){
	//printfMihp("+ on ajoute @ : %p de nb Block %lu \n", new_adr.Mihp_Adress_get_adr(), new_adr.Mihp_Adress_get_size());
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

/* cette fonction analyse une dependance entre deux iteration 
*  et renvoie 1 si c'est une dependance qui risque d'alterer la vectorisation 
*	et 0 si c'est une dependance qui est sans rique 
*/
bool Mihp_Iteration :: dependencesAnalysing(const Mihp_Adress & adress1, const Mihp_Adress & adress2){
	
//	printfMihp("++ adresse 1 : %p ;  adresse 2 : %p \n ", collision.first.Mihp_Adress_get_adr(), collision.second.Mihp_Adress_get_adr());
	if(adress1.Mihp_Adress_get_t() && !adress2.Mihp_Adress_get_t()){
		printfMihp("-- écriture suivie d'une lecture sur la meme adresse memoire \n");
	return true;
	}
	
	if(!adress1.Mihp_Adress_get_t() && adress2.Mihp_Adress_get_t()){
		printfMihp("-- lecture suivie d'une écriture sur la meme adresse memoire \n");
	return true;
	}
	
	if(!adress1.Mihp_Adress_get_t() && !adress2.Mihp_Adress_get_t()){
		printfMihp("-- deux lectures sur la meme adresse memoire \n");
	return false;
	}
		
	if(adress1.Mihp_Adress_get_t() && adress2.Mihp_Adress_get_t()){
		printfMihp("-- deux écritures sur la meme adresse memoire \n");
	return true;
	}
	return false;	
}


bool Mihp_Iteration :: MihpCheckAdressRecouvrement(const void * a_d1, const void *  a_f1, const void * a_d2, const void * a_f2 ){
printfMihp("adresse 1 de %p >>>  %p \t et \t adresse2 de  %p >>>  %p \n", a_d1, a_f1, a_d2, a_f2);
	return (((a_d1 >= a_d2)&&(a_d1 < a_f2)) || ((a_d2 >= a_d1)&&(a_d2 < a_f1)));
}

bool Mihp_Iteration :: MihpCheckIterRecouvrement(const Mihp_Iteration & other){
	//int i = 0;
	std :: list<Mihp_Adress> :: const_iterator it_other;
	
	bool thereIsRecouvrement = false;
	
	for(it = adres_acc.begin(); it != adres_acc.end(); ++it){
		
		for (it_other = other.adres_acc.begin(); it_other != other.adres_acc.end(); ++it_other){
			
			if(MihpCheckAdressRecouvrement(it->p_adr,  OFFSET(it->p_adr ,it->data_tsize), \
					it_other->p_adr ,  OFFSET(it_other->p_adr ,it_other->data_tsize))){
				
				if(dependencesAnalysing(*it, *it_other)){
						
					thereIsRecouvrement = true;			
					return thereIsRecouvrement;	
				}
			} 	
		
		}	
	}
	return thereIsRecouvrement;
}

void Mihp_Iteration :: AfficherAdresses(){
	int i = 1;
	for(it = adres_acc.begin(); it != adres_acc.end(); ++it){
		printfMihp("\t Adresse %d : %p \n ", i, it->Mihp_Adress_get_adr());
		++i;
	}
}

// Mihp_Iteration :: MihpCheckDependencies();
