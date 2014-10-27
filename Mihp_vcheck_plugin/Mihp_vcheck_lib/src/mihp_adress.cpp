#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <vec.h>
#include <list>
#include <string>
#include "mihp_adress.h"
#include "tools.h"

Mihp_Adress :: Mihp_Adress(){ p_adr = NULL; acc_type = false; data_tsize = 0;}

Mihp_Adress :: ~Mihp_Adress(){ free(p_adr ) }

 bool Mihp_Adress :: Mihp_Adress_get_t(){
	return acc_type;
}

 size_t Mihp_Adress :: Mihp_Adress_get_size(){
	return data_tsize;
}
		
 void * Mihp_Adress :: Mihp_Adress_get_adr(){
	return p_adr;
}

void Mihp_Adress :: Mihp_Adress_set_t(bool rw ){
	acc_type = type;
}

void Mihp_Adress :: Mihp_Adress_set_size(size_t s ){
	data_tsize = s
}

void Mihp_Adress :: Mihp_Adress_set_adr(void * p_ad ){
	p_adr = p_ad;
}

bool Mihp_Adress :: Is_same_adress(Mihp_Adress adress1, Mihp_Adress adress2){
	return(adress1.Mihp_Adress_get_adr() == adress2.Mihp_Adress_get_adr());
		 
}

bool Mihp_Adress :: Is_writing_same_adress(Mihp_Adress adress1, Mihp_Adress adress2){
	return(Is_same_adress(adress1,adress2) && adress1.Mihp_Adress_get_t() && adress2.Mihp_Adress_get_t);
}
