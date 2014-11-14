

#ifndef __MIHP_VCHECK_H__
#define __MIHP_VCHECK_H__

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

#define MIHP_WRITE 1
#define MIHP_READ 0
/** \fn void mihp_newLoop(const char* functionName, const char* fileName, size_t loopLine)
*	\brief cree un nouvel objet Mihp_Loop
*	\param functionName Nom de la fonction a analyser
*	\param fileName Nom du fichier contenant la fonction a analyser
*	\param loopLine Numero de ligne de la boucle
*/
void mihp_newLoop(const char* functionName, const char* fileName, size_t loopLine);

/** \fn void mihp_adress(void* addr, size_t nbBlock, int type)
*	\brief fonction qui cree un objet Mihp_Adress 
*	\param addr adresse accedee
*	\param nbBlock nombre de blocks accedes represente la taille du type de la donnee accedee
*	\param type type de l'acces si c'est une ecriture ou une lecture
*/
void mihp_adress(void* addr, size_t nbBlock, int type);

/** \fn void mihp_newIteration() 
*	\brief fonction qui cree un objet Mihp_Iteration 
*	 
*/
void mihp_newIteration();

/** \fn void mihp_endLoop() 
*	\brief fonction lance l'analyse sur la boucle recuperee grace mihp_newLoop
*	
*/
void mihp_endLoop();

#ifdef __cplusplus
}
#endif


#endif

