#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <vec.h>
#include <list>
#include <string>

#include "mihp_adress.h"

#ifndef MIHP_ITERATION_H
#define MIHP_ITERATION_H

typedef Mihp_Adress Mihp_Adress;



class Mihp_Iteration{
	
	private:
		std::string func_name;		// function name
		std::string file_name;		// source file name 
		unsigned int loop_nline;		// line number of the current loop in the file 'file_name'
		
		std::list<Mihp_Adress> adres_acc; 		// list of the adress accessed on one iteration of the loop.
		std::list<Mihp_Adress>::iterator it;
	public:
	
		Mihp_Iteration();
		Mihp_Iteration(std::string fun, std::string fin, unsigned int ln);
				
		~Mihp_Iteration();
		
		/// ajout d'un élément a la liste des adresses
		void MihpAddAdr(Mihp_Adress new_adr);
		
		/// récupère l'élément suivant si il y en a sinon NULL
		Mihp_Adress MihpGetNext_adr();
		std::list<dependence>MihpCheckDependencies();
		
		
};

#endif
