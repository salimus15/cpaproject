#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <vec.h>
#include <list>
#include <string>

#include "mihp_iteration.h"

#ifndef MIHP_LOOP_H
#define MIHP_LOOP_H



class Mihp_Loop{
	
	private:
		std::string func_name;		// function name
		std::string file_name;		// source file name 
		unsigned int loop_nline;		// line number of the current loop in the file 'file_name'

		std::list<Mihp_Iteration> iters; 		// list of the iterations of the current loop  see mihp_iteration.h
		std::list<Mihp_Iteration>::iterator it;
	public:
		Mihp_Loop();
		
		~Mihp_Loop();
		
		/// ajout d'un élément a la liste des iterations
		void Mihp_add_iter(Mihp_Iteration new_iter);
		
		/// récupère l'élément suivant si il y en a sinon NULL
		Mihp_Iteration Mihp_get_next_iter();
		
};

#endif
