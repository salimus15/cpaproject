#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <vec.h>
#include <list>
#include <string>
#include "tools.h"
#include "mihp_loop.h"


Mihp_Loop :: Mihp_Loop(){ 
	func_name = NULL; 
	file_name = NULL; 
	loop_nline = 0 ; 
	it = iters.begin(); 
}


void Mihp_Loop :: Mihp_add_iter(Mihp_Adress new_iter&){
	
	iters.push_back(new_iter);
}

Mihp_Iteration Mihp_Loop :: Mihp_get_next_iter(){
	if(it != iters.end()){
		it++;
		return it;
	}else return NULL;

}
