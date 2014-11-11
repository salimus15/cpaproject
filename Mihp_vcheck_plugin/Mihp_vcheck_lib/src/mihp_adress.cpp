
#include "mihp_adress.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "tools.h"

void Mihp_Adress :: CopieMihpAdress( const Mihp_Adress & other){
	p_adr = other.p_adr;
	acc_type = other.acc_type;
	data_tsize = other.data_tsize;
	
}


Mihp_Adress :: Mihp_Adress(){ 
	p_adr = NULL; 
	acc_type = false; 
	data_tsize = 0;
}

Mihp_Adress :: ~Mihp_Adress(){}

Mihp_Adress :: Mihp_Adress( void * adr, const size_t & tsize, const bool & typeacc){
	p_adr = adr;
	data_tsize = tsize;
	acc_type = typeacc;

}


Mihp_Adress :: Mihp_Adress (const Mihp_Adress & other){
	CopieMihpAdress(other);
}


 Mihp_Adress & Mihp_Adress :: operator= (const Mihp_Adress & other){
    
 	CopieMihpAdress(other);
 	return *this;
 	
}


 bool Mihp_Adress :: Mihp_Adress_get_t() const{
	return acc_type;
}


 size_t Mihp_Adress :: Mihp_Adress_get_size() const{
	return data_tsize;
}
		
 void * Mihp_Adress :: Mihp_Adress_get_adr()const{
	return p_adr;
}

void Mihp_Adress :: Mihp_Adress_set_t(bool rw ){
	acc_type = rw;
}

void Mihp_Adress :: Mihp_Adress_set_size(size_t s ){
	data_tsize = s;
}

void Mihp_Adress :: Mihp_Adress_set_adr(void * p_ad ){
	p_adr = p_ad;
}

bool Mihp_Adress :: Is_same_adress(const Mihp_Adress & adress1, const Mihp_Adress & adress2) {
	return(adress1.Mihp_Adress_get_adr() == adress2.Mihp_Adress_get_adr());
		 
}

bool Mihp_Adress :: Is_writing_same_adress(const Mihp_Adress & adress1, const Mihp_Adress & adress2){
	return(Is_same_adress(adress1,adress2) && adress1.Mihp_Adress_get_t() && adress2.Mihp_Adress_get_t());
}
