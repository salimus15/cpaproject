#ifndef __LIBRAIRIE_H__
#define __LIBRAIRIE_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MIHP_WRITE 1
#define MIHP_READ 0

void testFonction(int param, const char * str);

void mihp_newLoop(const char* functionName, const char* fileName, size_t functionLine, size_t loopLine);
void mihp_adress(void* addr, size_t nbBlock, char type);
void mihp_newIteration();
void mihp_endLoop();

#ifdef __cplusplus
}
#endif


#endif

