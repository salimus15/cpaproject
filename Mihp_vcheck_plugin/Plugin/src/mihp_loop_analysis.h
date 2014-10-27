#ifndef __MIHP_LOOP_ANALISYS_H__
#define __MIHP_LOOP_ANALISYS_H__

#include "mihp_debug_plugin.h"

void createGimpleCallBeforeLoop(basic_block loopHeader, basic_block loopLatch, const char * functionName, const char * currentFunctionName, const char* fileName, size_t loopLine);

void createGimpleCallAfterLatchLoop(basic_block loopLatch, const char * functionName);

void addGimpleCallInInnerLoop(struct loop* boucle);
void addGimpleCallInLoop(struct loop* boucle);

int getLoopLine(struct loop* boucle);





#endif

