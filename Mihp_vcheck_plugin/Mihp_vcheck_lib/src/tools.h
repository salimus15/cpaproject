#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <list>
#include <string>
#include <limits>
//#include "mihp_adress.h"
#ifndef TOOLS_H
#define TOOLS_H

typedef std::list<std::string> ListeString;



#ifndef NDEBUG
#	define printMihpIO(X) std::cout << X << std::endl;
#	define printfMihp(X, ...) printf(X, ##__VA_ARGS__)
#else
#	define printMihpIO(X)
#	define printfMihp(X, ...)
#endif

#define OFFSET(X, Y) ((char*)(X) + (Y))

#define print_mihp_err(X) std::cout << "!!! ERROR -->  " << X << endl;
#define print_mihp_war(X) std::cout << "!! WARNING --> " << X << endl;

#define MAX_INT std :: numeric_limits<int> :: max(); 



#endif
