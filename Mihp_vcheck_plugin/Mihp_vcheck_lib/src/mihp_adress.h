#include <stdio.h>
#include <stdlib.h>
#include <iostream>
//#include <vec.h>
#include <list>
#include <string>



#ifndef MIHP_ADRESS_H
#define MIHP_ADRESS_H



class Mihp_Adress{
	
	private:
		/*

		std::string func_name;		// function name
		std::string file_name;		// source file name 
		unsigned int loop_nline;		// line number of the current loop in the file 'file_name'
		*/
		
		void * p_adr;
		bool acc_type;    // acc_type = 0 when reading & acc_type = 1 when writing.
		size_t data_tsize;  
		
		
		
		
	public:
		Mihp_Adress();
			
		~Mihp_Adress();
		
		 bool Mihp_Adress_get_t();
		 size_t Mihp_Adress_get_size();
		 void * Mihp_Adress_get_adr();

		void Mihp_Adress_set_t(bool rw );
		void Mihp_Adress_set_size(size_t s );
		void Mihp_Adress_set_adr(void * p_ad );
		
		bool Is_same_adress(Mihp_Adress adress1, Mihp_Adress adress2);
		bool Is_writing_same_adress(Mihp_Adress adress1, Mihp_Adress adress2);

};

#endif
