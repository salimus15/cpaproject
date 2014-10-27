#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vec.h>
#include <list>
#include <string>

#ifndef TOOLS_H
#define TOOLS_H

typedef std::list<std::string> ListeString;

struct dependencies{
	Mihp_Adress adr1;
	Mihp_Adress adr2;
};

typedef dependencies dependence; 

#ifndef NDEBUG
#	define printMihpIO(X) std::cout << X << std::endl;
#	define printfMihp(X, ...) printf(X, ##__VA_ARGS__)
#else
#	define printMihpIO(X)
#	define printfMihp(X, ...)
#endif



#define print_mihp_err(X) std::cout << "!!! ERROR -->  " << X << endl;
#define print_mihp_war(X) std::cout << "!! WARNING --> " << X << endl;




#endif
