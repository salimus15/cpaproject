#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <vec.h>
#include <list>
#include <string>
#include "tools.h"
#include "mihp_iteration.h"

Mihp_Iteration :: Mihp_Iteration(){ func_name = NULL; 
	file_name = NULL; 
	loop_nline = 0; 
	adres = adres_acc.begin();
}
	

Mihp_Iteration :: Mihp_Iteration(std::string fun, std::string fin, unsigned int ln){
	func_name = fun;
	file_name = fin;
	loop_nline = ln;

}

Mihp_Iteration :: ~Mihp_Iteration()


void Mihp_add_adr(Mihp_Adress new_adr&){
	
	adres_acc.push_back(new_adr);
}


Mihp_Adress Mihp_get_next_adr(){
	if(it != adres_acc.end()){
		it++;
		return it;
	}else return NULL;

}
